#include "algo_bfs.hpp"

#include <chrono>
#include <queue>
#include <algorithm>
#include <limits>

RunResult RunBFS(const Grid &grid)
{
    RunResult rr;

    int H = grid.Height();
    int W = grid.Width();
    int N = H * W; // total number of cells

    rr.visited_mask.assign(N, 0);
    std::vector<int> parent(N, -1); // used to draw +

    int start = grid.StartId();
    int goal = grid.GoalId();

    // used to keep time
    auto timer_start = std::chrono::high_resolution_clock::now();

    std::queue<int> q; // stores which nodes to explore next
    q.push(start);
    rr.visited_mask[start] = 1; // marks as visited

    // bfs main loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        // mark as explored
        rr.explored_count++;

        if (u == goal)
        {
            rr.found = true;
            break;
        }

        // explore all unvisited neighbors
        int neighbors[4];
        int n = grid.GetNeighbors(u, neighbors);

        // neighbors exploration
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

    // figure out time taken
    auto timer_end = std::chrono::high_resolution_clock::now();
    rr.micros = std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer_start).count();

    // reconstruct path if found
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