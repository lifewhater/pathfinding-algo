cmake_minimum_required(VERSION 3.15)
project(PathfindingVisualizer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -O2)
endif()

add_executable(app
  src/main.cpp
  src/dijkstra.cpp
  src/bfs.cpp
  src/astar.cpp
)

target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
