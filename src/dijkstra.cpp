// dependencies
#include "algo_dijkstra.hpp"
#include <queue>
#include <limits>
#include <chrono>
#include <algorithm>

RunResult RunDijkstra(const Grid &grid)
{
    RunResult rr;
    int H = grid.Height();
    int W = grid.Width();
    int N = H * W;

    // Initialize arrays
    rr.visited_mask.assign(N, 0);
    const int INF = std::numeric_limits<int>::max();
    const int start = grid.StartId();
    const int goal = grid.GoalId();

    std::vector<int> dist(N, INF);    // Shortest distance to each cell
    std::vector<int> parent(N, -1);   // For path reconstruction

    // Min-heap: pair<distance, node_id>
    std::priority_queue<std::pair<int, int>,
        std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>>
        pq;

    // Start with distance 0
    dist[start] = 0;
    pq.push(std::make_pair(0, start));

    auto timer_start = std::chrono::high_resolution_clock::now();

    while (!pq.empty())
    {
        int currentNode = pq.top().second;
        int currentDist = pq.top().first;
        pq.pop();

        // Skip if already found a better path
        if (currentDist > dist[currentNode]) continue;

        // Mark as visited (settled)
        rr.visited_mask[currentNode] = 1;
        rr.explored_count++;

        // Early exit if goal reached
        if (currentNode == goal)
        {
            rr.found = true;
            break;
        }

        // Explore all neighbors
        int neighbors[4];
        int neighborCount = grid.GetNeighbors(currentNode, neighbors);

        for (int i = 0; i < neighborCount; i++)
        {
            int neighbor = neighbors[i];
            int newDist = currentDist + 1;  // Unit edge cost

            // Relax edge if we found a shorter path
            if (newDist < dist[neighbor])
            {
                dist[neighbor] = newDist;
                parent[neighbor] = currentNode;
                pq.push(std::make_pair(newDist, neighbor));
            }
        }
    }
    
    auto timer_end = std::chrono::high_resolution_clock::now();
    rr.micros = std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer_start).count();

    // Reconstruct path if goal was reached
    if (dist[goal] != INF)
    {
        rr.found = true;
        rr.path_cost = dist[goal];

        // Backtrack from goal to start
        int cur = goal;
        while(cur != -1){
            rr.path_ids.push_back(cur);
            cur = parent[cur];
        }
        std::reverse(rr.path_ids.begin(), rr.path_ids.end());
    } 
    return rr;
}