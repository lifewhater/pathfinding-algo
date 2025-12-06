//dependencies
#include "algo_astar.hpp"
#include <queue>
#include <limits>
#include <algorithm>
#include <chrono>

RunResult RunAStar(const Grid &grid){
    RunResult rr;
    int H = grid.Height();
    int W = grid.Width();
    int N = H * W;
    
    rr.visited_mask.assign(N, 0);

    int start = grid.StartId();
    int goal = grid.GoalId();


    auto timer_start = std::chrono::high_resolution_clock::now();

    /*
    A* implementation here
    ...
    ...
    ...
    */

    //time taken
    auto timer_end = std::chrono::high_resolution_clock::now();
    rr.micros = std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer_start).count();

    return rr;
}