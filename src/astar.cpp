//dependencies
#include "algo_astar.hpp"
#include <queue>
#include <limits>
#include <algorithm>
#include <chrono>
#include <cstdlib>

RunResult RunAStar(const Grid &grid){
    RunResult rr;
    int H = grid.Height();
    int W = grid.Width();
    int N = H * W;
    
    rr.visited_mask.assign(N, 0);

    int start = grid.StartId();
    int goal = grid.GoalId();

    
    // A* algorithm implementation
    const int INF = std::numeric_limits<int>::max();
    std::vector<int> g_score(N, INF);
    std::vector<int> parent(N, -1);

    // Implementing heuristic: (x_2 - x_1) + (y_2 - y_1)
    auto heuristic = [W, goal](int node) {
        int goal_r = goal / W;
        int goal_c = goal % W;
        int r = node / W;
        int c = node % W;
        return std::abs(goal_r - r) + std::abs(goal_c - c);
    };

    std::priority_queue<std::pair<int, int>,
    std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> open_set;

    g_score[start] = 0;
    int f_start = heuristic(start);
    open_set.push(std::make_pair(f_start, start));

// NEED TO START LATER RIGHT BEFORE ACTUAL ALGO
    auto timer_start = std::chrono::high_resolution_clock::now();

    while(!open_set.empty()){
        int currentNode = open_set.top().second;
        open_set.pop();

        // If we reached the goal
        if(rr.visited_mask[currentNode]) continue;
        rr.visited_mask[currentNode] = 1;
        rr.explored_count++;

        if(currentNode == goal){
            rr.found = true;
            break;
        }
        int neighbors[4];
        int neighborCount = grid.GetNeighbors(currentNode, neighbors);

        for(int i = 0; i < neighborCount; i++){
            int nieghbor = neighbors[i];

            int tentative_g = g_score[currentNode] + 1; // all edges have weight 1

            if(tentative_g < g_score[nieghbor]){
                g_score[nieghbor] = tentative_g;
                parent[nieghbor] = currentNode;
                int f_neighbor = tentative_g + heuristic(nieghbor);
                open_set.push(std::make_pair(f_neighbor, nieghbor));
            }
        }
    }

    //time taken
    auto timer_end = std::chrono::high_resolution_clock::now();
    rr.micros = std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer_start).count();

    // Reconstruct path if found
    if(g_score[goal] != INF){
        rr.found = true;
        rr.path_cost = g_score[goal];

        int current = goal;
        while(current != -1){
            rr.path_ids.push_back(current);
            current = parent[current];
        }
        std::reverse(rr.path_ids.begin(), rr.path_ids.end());   
    }

    return rr;
}