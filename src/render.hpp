// src/render.hpp
// Purpose: ASCII rendering of exploration and final path with strict precedence:
// base map (.,#) -> visited (+) -> path (*) -> preserve S/G at the end.

#ifndef RENDER_HPP
#define RENDER_HPP

// dependencies
#include <string>
#include "grid.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

// algorithms
#include "algo_common.hpp"


/*
MY OUTCOME I'M AIMING FOR
HEADER: ====== <ALGO> ======
HEIGHT lines of WIDTH chars
SUMMARY- FOUND: YES|NO || VISITED: N || PATHLEN: L || COST: C || TIME: T

base map contains ('.', '#') -> visited '+' -> path '*' -> Start 'S' -> Goal 'G'
*/

void OverlayAndPrint(const Grid& grid, const RunResult &rr, const std::string &algo_name)
{
    int H = grid.Height();
    int W = grid.Width();
    int N = H * W;
    // header
    std::cout << "\n=== " << algo_name << " ===\n\n";

    // rendering grid
    std::vector<char> buffer(N);
    for(int r = 0; r < H; ++r){
        for(int c = 0; c < W; ++c){
            int id = grid.ToId(r,c);
            buffer[id] = grid.At(r,c); // '.' or '#'
        }
    }
            //overlay visited cells
            if(static_cast<int>(rr.visited_mask.size())==N){
                for(int id = 0; id < N; ++id){
                    if(rr.visited_mask[id]){
                        if(buffer[id] == '.'){
                            buffer[id] = '+';
                        }
                    }
                }
                
            }
        
        for(int id : rr.path_ids){
                    if(id >= 0 && id < N){
                        if(buffer[id] != '#'){
                            buffer[id] = '*';
                        }
                    }
                }
        const int start_id = grid.StartId();
        const int goal_id = grid.GoalId();
        if(start_id >= 0 && start_id < N){
            buffer[start_id] = 'S';
        }
        if(goal_id >= 0 && goal_id < N){
            buffer[goal_id] = 'G';
        }

        //Print height x width
        for(int r = 0; r < H; ++r){
            for(int c = 0; c < W; ++c){
                int id = r * W + c;
                std::cout << buffer[id];
            }
            std::cout << "\n";
       }
           // SUMMARY- FOUND: YES|NO || VISITED: N || PATHLEN: L || COST: C || TIME: T
    std::cout << "FOUND: " << (rr.found ? "YES" : "NO")
              << " || VISITED: " << rr.explored_count
              << " || PATHLEN: " << rr.path_ids.size()
              << " || COST: " << rr.path_cost
              << " || TIME: " << rr.micros << " micros\n";
    }



#endif
