// src/algo_astar.hpp
// Purpose: Interface for A* search with an admissible heuristic (e.g., Manhattan).

#ifndef ALGO_ASTAR_HPP
#define ALGO_ASTAR_HPP

#include "grid.hpp"
#include "algo_common.hpp"

RunResult RunAStar(const Grid& grid);

#endif
