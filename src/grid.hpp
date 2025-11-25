// src/grid.hpp (ADT Overview)
// Purpose: Grid model. Owns cells ('.' open, '#' wall), dimensions, and S/G positions.
// Provides neighbor queries and utility conversions between (row,col) and linear ids.
// Students implement: LoadFromFile, Generate, InBounds, IsBlocked, GetNeighbors, etc.

#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>

//libraries that I added
#include <fstream>
#include <iostream>
#include "cli.hpp"

struct Cell { int row; int col; };

class Grid {
public:
    Grid() : height_(0), width_(0), start_id_(-1), goal_id_(-1) {}
    bool LoadFromFile(const std::string& path);                // parse headers+grid; require S/G on '.'
    bool Generate(int height, int width, double density, unsigned int seed); // optional/bonus

    int Height() const { return height_; }
    int Width()  const { return width_;  }
    bool InBounds(int r, int c) const;
    bool IsBlocked(int r, int c) const;
    int  ToId(int r, int c) const { return r * width_ + c; }
    Cell FromId(int id) const { return Cell{ id / width_, id % width_ }; }

    int  StartId() const { return start_id_; }
    int  GoalId()  const { return goal_id_; }
    Cell Start()   const { return FromId(start_id_); }
    Cell Goal()    const { return FromId(goal_id_);  }
    char At(int r, int c) const { return cells_[ToId(r,c)]; }

    // 4-neighbor (N,E,S,W); fill neighbors into out[4]; return count
    int GetNeighbors(int id, int out[4]) const;

private:
    int height_, width_;
    std::vector<char> cells_;
    int start_id_, goal_id_;
};

// Checks in-bounds
inline bool Grid::InBounds(int r, int c) const {
    return r >= 0 && c >= 0 && r < height_ && c < width_;
}

// Checks if blocked
inline bool Grid::IsBlocked(int r, int c) const {
    if(!InBounds(r, c)){
        return true;
    }
    int id  = ToId(r, c);
    return cells_[id] == '#';
}




// Load from file map done
inline bool Grid::LoadFromFile(const std::string& path){
        std::ifstream file(path);

    if(!file.is_open()){
        std::cout << "Map failed to open!\n";
        return false;
    }

    std::string str;
    std::string file_content;

    /*
    WIDTH  10
    HEIGHT 6
    START  0 0
    GOAL   5 5
    */
   

    while(std::getline(file, str)){
        file_content += str;
        file_content.push_back('\n');
    }
    std::cout << file_content;

return true;
}



#endif