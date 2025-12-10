 ### CSCI 115 FINAL PROJECT: PATHFINDING VISUALIZER
## Purpose:
Build a CLI-based visualizer that runs BFS/Dijkstra/A* on a user generated map and renders a deterministic ASCII visualization of exploration and the final path. 
## Core Parts:
1. Grid representation and map loading
2. CLI Reference
3. BFS and Visualization
4. Dijkstra's Algorithm
5. A* Search
## How to run the visualization
- Build the `main.cpp` using CMake
- Run the command `cd build` in terminal 
- Type `./app --help` for a short summary on the commands
- Type `./app --algo <algo> --map <map destination>`
	Sample maps can be accessed through `maps` folder
	If a default map is chosen, input `../maps/name-of-map.txt`
- Includes optional animation.
	- Add `--animate` flag to see it visually find the path.
- EXAMPLE 
`./app --algo bfs --map ../maps/sample_small.txt --animate`

## Symbols and Path Rules
#### Symbols
	# wall
	. open
	S Start (always on '.')
	G Goal (always on '.')
	+ Visited (not final path)
	* Final path
#### Paths Rules
 - 4-neighbor moves only (N,E,S,W)
 -  If found, include start and goal in path
 - PathLen = nodes - 1; Cost = PathLen on unit grids
 - If not found, no '*', path_ids empty

### Limitations and Improvements
- The code can be written more clearly
- Animation implementation when all algorithms are selected
- CLI arguments to run can be well written
- FURTHER IMPROVEMENTS TO BE 
- Look at github for more information and timeline of the project
	https://github.com/lifewhater/pathfinding-algo