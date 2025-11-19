#include "cli.hpp"
#include <iostream>
using namespace std;

void printHelp(){
    cout << "Usage: Runs selected algorithm(s) on a loaded or generated grid, then prints a deterministic ASCII visualization and metrics." << endl;
    cout << "\tOPTIONS:" << endl;
    cout << "\t\t--algo {bfs|dijkstra|astar|all} : Select algorithms to run." << endl;
    cout << "\t\t--map <path>                    : Load map from file." << endl;
    cout << "\t\t--generate                      : Generate a random map" << endl;
    cout << "\t\t--width <int>                   : Columns for generated map" << endl;
    cout << "\t\t--height <int>                  : Rows for generated map." << endl;
    cout << "\t\t--density <float 0..1>          : Fraction of walls;" << endl;
    cout << "\t\t--seed <int>                    : Random seed for reproducibility." << endl;
    cout << "\tEXAMPLE:" << endl;
    cout << "\t\tapp --algo bfs --width 40 --height 20 --density 0.28 --seed 42" << endl;
}

bool parseArgs(int argc, char * argv[], config& cfg){
    for(int i = 1; i < argc; i++){
        string arg = argv[i];

        if(arg == "--help"){
            cfg.showHelp = true;
            return true;
        }

        else if(arg == "--algo"){
            string which = argv[++i];
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
                cout << "Uknown algorithm: " << which << endl;
                return false;
            }
        }
    }
    return true;  
}
