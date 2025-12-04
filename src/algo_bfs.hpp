// src/algo_bfs.hpp
// Purpose: Interface for Breadth-First Search on the grid (unit-cost shortest path).

#ifndef ALGO_BFS_HPP
#define ALGO_BFS_HPP

#include "grid.hpp"
#include "algo_common.hpp"

#include <chrono>
#include <queue>
#include <algorithm>
#include <limits>

RunResult RunBFS(const Grid &grid)
{
    RunResult rr;
    /* data */
    bool found = false;
    std::vector<int> path_ids; // includes start and goal
    int explored_count = 0; // nodes popped
    int path_cost = 0;      // path length
    long long micros = 0;

    int H = grid.Height();
    int W = grid.Width();
    int N = H * W; // total number of cells

    rr.visited_mask.assign(N, 0);
    std::vector<int> parent(N, -1); // used to draw +

    int start = grid.StartId();
    int goal = grid.GoalId();

    // used to keep time
    using clock = std::chrono::steady_clock;
    auto time_start = clock::now();

    std::queue<int> q; // stores which nodes to explore next
    q.push(start);
    rr.visited_mask[start] = 1; // marks as visited

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        rr.explored_count++;

        if (u == goal)
        {
            rr.found = true;
            break;
        }

        int neighbors[4];
        int n = grid.GetNeighbors(u, neighbors);

        for (int i = 0; i < n; ++i)
        {
            int v = neighbors[i];
            if (!rr.visited_mask[v])
            {
                rr.visited_mask[v] = 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    auto t1 = clock::now();
    rr.micros = std::chrono::duration_cast<std::chrono::microseconds>(t1 - time_start).count();

    if (rr.found)
    {
        std::vector<int> path;
        int cur = goal;
        while (cur != -1)
        {
            path.push_back(cur);
            cur = parent[cur];
        }
        std::reverse(path.begin(), path.end());
        rr.path_ids = std::move(path);
        rr.path_cost = (int)rr.path_ids.size() - 1;
    }

    return rr;
}

#endif
