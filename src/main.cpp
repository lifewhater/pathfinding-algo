// main.cpp
// Purpose: Entry point. Students will implement CLI parsing, map loading/generation,
// algorithm dispatch, and visualization calls. For now, this prints TODOs.
#include "cli.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Pathfinding Visualizer Starter\n";
    // std::cout << "TODO: Implement CLI parsing (--algo, --map, --generate, etc.)\n";
    config cfg;
    if(!parseArgs(argc, argv, cfg)){
        printHelp();
        return 1;
    }
    if(cfg.showHelp){
        printHelp();
        return 0;
    }
 
    std::cout << "TODO: Load or generate a grid map. Validate S/G on open cells.\n";
    std::cout << "TODO: Run selected algorithm(s): BFS, Dijkstra, A*.\n";
    std::cout << "TODO: Render ASCII output with visited (+) and path (*), preserving S/G and walls.\n";
    return 0;
}
 