// main.cpp
// Purpose: Entry point. Students will implement CLI parsing, map loading/generation,
// algorithm dispatch, and visualization calls. For now, this prints TODOs.
#include "cli.hpp"
#include "grid.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    config cfg;
    parseArgs(argc, argv, cfg);
    
    std::cout << "\n\nPathfinding Visualizer Starting...\n";

    // std::cout << "TODO: Implement CLI parsing (--algo, --map, --generate, etc.)\n";
    // PARSING STARTER CLI ARGUMENTS
    if(cfg.showHelp){
        printHelp();
        return 0;
    } 

    if(cfg.algo == algoChoice::BFS){
        std::cout << "BFS PRINTING\n";
    } else if(cfg.algo == algoChoice::Dijkstra){
        std::cout << "\n\nDijkstra PRINTING\n";
    }else if(cfg.algo == algoChoice::AStar){
        std::cout << "AStar PRINTING\n";
    }else if(cfg.algo == algoChoice::All){
        std::cout << "ALL PRINTING\n";
    }
    
    //std::cout << "TODO: Load or generate a grid map. Validate S/G on open cells.\n";
    // GRID LOADING WITH FILE INPUT
    Grid g;
    if(cfg.useMap){
        g.LoadFromFile(cfg.mapInput);
    }

    std::cout << "TODO: Run selected algorithm(s): BFS, Dijkstra, A*.\n";
    std::cout << "TODO: Render ASCII output with visited (+) and path (*), preserving S/G and walls.\n";
    return 0;
}
 