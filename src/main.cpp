/*
Prabhjot Singh CSCI115 Final Project
Pathfinding Visualizer
Please see README.md for additional details.
    - Explains how to build and run.
    - Lists any known issues or limitations or shortcomings.
    - Describes any optional/bonus features implemented.
*/
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
#include "algo_astar.hpp"

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
    // if (cfg.showHelp)
    // {
    //     printHelp();
    //     return 0;
    // }

    // if (cfg.algo == algoChoice::BFS)
    // {
    //     std::cout << "\n\nBFS Finding Path...\n";
    //     RunResult bfs_result = RunBFS(g);
    //     AnimatePath(g, bfs_result, "BFS");
    // } else{
    //     OverlayAndPrint(g, RunResult(), "BFS");
    // }

    // if (cfg.algo == algoChoice::Dijkstra)
    // {
    //     std::cout << "\n\nDijkstra Finding Path...\n";
    //     RunResult dijkstra_result = RunDijkstra(g);
    //     AnimatePath(g, dijkstra_result, "Dijkstra");
    // } else{
    //     OverlayAndPrint(g, RunResult(), "Dijkstra");
    // }
    
    // if (cfg.algo == algoChoice::AStar)
    // {
    //     std::cout << "\n\nAStar Finding Path...\n";
    //     RunResult astar_result = RunAStar(g);
    //     AnimatePath(g, astar_result, "A*");
    // } else {
    //     OverlayAndPrint(g, RunResult(), "A*");
    // }


    // if (cfg.algo == algoChoice::All)
    // {
    //     std::cout << "\n\nALL Finding Path...\n";
        
    //     // BFS
    //     std::cout << "\n\nBFS Finding Path...\n";
    //     RunResult bfs_result = RunBFS(g);
    //     AnimatePath(g, bfs_result, "BFS");

    //     // Dijkstra
    //     std::cout << "\n\nDijkstra Finding Path...\n";
    //     RunResult dijkstra_result = RunDijkstra(g);
    //     AnimatePath(g, dijkstra_result, "Dijkstra");

    //     // AStar
    //     std::cout << "\n\nAStar Finding Path...\n";
    //     RunResult astar_result = RunAStar(g);
    //     AnimatePath(g, astar_result, "AStar");
    // }
    // else {
    //     OverlayAndPrint(g, RunResult(), "ALL");
    // }

    switch (cfg.algo)
    {
    case algoChoice::BFS:
        /* code */
        std::cout << "\n\nBFS Finding Path...\n";
        {
            RunResult bfs_algo = RunBFS(g);
            if(cfg.animate){
                AnimatePath(g, bfs_algo, "BFS");
            } else{
                OverlayAndPrint(g, bfs_algo, "BFS");
            }
        }
        break;
    case algoChoice::Dijkstra:
        std::cout << "\n\nDijkstra Finding Path...\n";
        {
            RunResult dijkstra_algo = RunDijkstra(g);
            if(cfg.animate){
                AnimatePath(g, dijkstra_algo, "Dijkstra");
            } else{
                OverlayAndPrint(g, dijkstra_algo, "Dijkstra");
            }
        }
        break;
    case algoChoice::AStar:
        std::cout << "\n\nAStar Finding Path...\n";
        {
            RunResult astar_algo = RunAStar(g);
            if(cfg.animate){
                AnimatePath(g, astar_algo, "A*");
            } else{
                OverlayAndPrint(g, astar_algo, "A*");
            }
        }
        break;
    case algoChoice::All:
        std::cout << "\n\nALL Finding Path...\n";
        {
            // BFS
            std::cout << "\n\nBFS Finding Path...\n";
            RunResult bfs_algo = RunBFS(g);
            OverlayAndPrint(g, bfs_algo, "BFS");

            // Dijkstra
            std::cout << "\n\nDijkstra Finding Path...\n";
            RunResult dijkstra_algo = RunDijkstra(g);
            OverlayAndPrint(g, dijkstra_algo, "Dijkstra");

            // AStar
            std::cout << "\n\nAStar Finding Path...\n";
            RunResult astar_algo = RunAStar(g);
            OverlayAndPrint(g, astar_algo, "A*");
        }
        break;
    default:
        std::cerr << "Unknown algorithm choice.\n";
        break;
    }


    return 0;
}
