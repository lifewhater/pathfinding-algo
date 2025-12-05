// main.cpp
// Purpose: Entry point. Students will implement CLI parsing, map loading/generation,
// algorithm dispatch, and visualization calls. For now, this prints TODOs.
#include "cli.hpp"
#include "grid.hpp"
#include <iostream>
#include "render.hpp"

// algorithms
#include "algo_bfs.hpp"
#include "algo_dijkstra.hpp"

int main(int argc, char *argv[])
{
    config cfg;
    Grid g;
    parseArgs(argc, argv, cfg);

    std::cout << "\n\nPathfinding Visualizer Starting...";


    // std::cout << "TODO: Load or generate a grid map. Validate S/G on open cells.\n";
    //  GRID LOADING WITH FILE INPUT

    if (cfg.useMap)
    {
        if (!g.LoadFromFile(cfg.mapInput))
        {
            std::cerr << "Failed to load map: " << cfg.mapInput << "\n";
            return 1;
        }
    }

    // std::cout << "TODO: Implement CLI parsing (--algo, --map, --generate, etc.)\n";
    // PARSING STARTER CLI ARGUMENTS
    if (cfg.showHelp)
    {
        printHelp();
        return 0;
    }

    if (cfg.algo == algoChoice::BFS)
    {
        std::cout << "\n\nBFS Finding Path...\n";
        RunResult bfs_result = RunBFS(g);
        OverlayAndPrint(g, bfs_result, "BFS");
    }

    else if (cfg.algo == algoChoice::Dijkstra)
    {
        std::cout << "\n\nDijkstra Finding Path...\n";
        RunResult dijkstra_result = RunDijkstra(g);
        OverlayAndPrint(g, dijkstra_result, "Dijkstra");
    }
    
    else if (cfg.algo == algoChoice::AStar)
    {
        std::cout << "\n\nAStar Finding Path...\n";
    }
    else if (cfg.algo == algoChoice::All)
    {
        std::cout << "\n\nALL Finding Path...\n";
    }


    std::cout << "TODO: Run selected algorithm(s): Dijkstra, A*.\n";
    std::cout << "TODO: Render ASCII output with visited (+) and path (*), preserving S/G and walls.\n";
    return 0;
}
