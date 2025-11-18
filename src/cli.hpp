// This is a cli header file for the project
#pragma once
#include <string>
#include <ostream>

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

bool parseArgs(int argc, char * argv[], config);
void printHelp();

