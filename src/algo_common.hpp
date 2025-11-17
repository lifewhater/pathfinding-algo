// src/algo_common.hpp
// Purpose: Shared result type for all algorithms and any common utilities needed.

#ifndef ALGO_COMMON_HPP
#define ALGO_COMMON_HPP

#include <vector>

struct RunResult {
    bool found = false;
    std::vector<int> path_ids;     // includes start and goal when found
    std::vector<char> visited_mask; // size = H*W; 1 when popped/settled
    int explored_count = 0;         // number of nodes actually popped/settled
    int path_cost = 0;              // equals path length on unit grid
    long long micros = 0;           // timing in microseconds
};

#endif
