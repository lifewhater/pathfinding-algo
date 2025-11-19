#pragma once
#include "grid.hpp"
#include <string>
#include <iostream>

enum class algoChoice {
    BFS, Dijkstra, AStar, All
};

struct config {
    algoChoice algo;
    bool useMap = false;
    bool useGenerate = false;
    std::string mapInput = "";
    int width = 0;
    int height = 0;
    int seed = 0;
    double density = 0.0;
    bool showHelp = false;
};

inline void printHelp(){
    std::cout << "Usage: Runs selected algorithm(s) on a loaded or generated grid, then prints a deterministic ASCII visualization and metrics." << std::endl;
    std::cout << "\tOPTIONS:" << std::endl;
    std::cout << "\t\t--algo {bfs|dijkstra|astar|all} : Select algorithms to run." << std::endl;
    std::cout << "\t\t--map <path>                    : Load map from file." << std::endl;
    std::cout << "\t\t--generate                      : Generate a random map" << std::endl;
    std::cout << "\t\t--width <int>                   : Columns for generated map" << std::endl;
    std::cout << "\t\t--height <int>                  : Rows for generated map." << std::endl;
    std::cout << "\t\t--density <float 0..1>          : Fraction of walls;" << std::endl;
    std::cout << "\t\t--seed <int>                    : Random seed for reproducibility." << std::endl;
    std::cout << "\tEXAMPLE:" << std::endl;
    std::cout << "\t\tapp --algo bfs --width 40 --height 20 --density 0.28 --seed 42" << std::endl;
}

inline bool parseArgs(int argc, char * argv[], config& cfg){
    for(int i = 1; i < argc; i++){

        std::string arg = argv[i];
        if(arg == "--help"){
            cfg.showHelp = true;
            return true;
        }

        // --algo implementation
        else if(arg == "--algo"){
            if(i + 1 >= argc) {
                std::cerr << "Missing value for --algo. \n";
                return false;
            }
            std::string which = argv[++i];
            if(which == "bfs"){
                cfg.algo = algoChoice::BFS;
            }
            else if(which == "dijkstra"){
                cfg.algo = algoChoice::Dijkstra;
            }
            else if(which == "astar"){
                cfg.algo = algoChoice::AStar;
            }
            else if(which == "all"){
                cfg.algo = algoChoice::All;
            }
            else{
                std::cout << "Unknown algorithm: " << which << std::endl;
                return false;
            }
        }
        
        // --map implementation
        if(arg == "--map" && i+1 < argc){
            cfg.mapInput = argv[++i];
            cfg.useMap = true;
        }
    }
    return true;
}
