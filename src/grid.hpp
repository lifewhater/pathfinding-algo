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
#include <sstream>
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

    // whether header is done
    bool header_done = false;
    // variables 
    std::string str;
    std::string file_content;
    int w = -1;
    int h = -1;
    int start_r = -1, start_c = -1;
    int goal_r = -1, goal_c = -1;
    std::vector<std::string> grid_lines;

    // incorporates load from file. 
    while(std::getline(file,str)){
        if(!str.empty() && str[0] == '#' && !header_done) continue; // skip comments

        // if the header is not done, it reads the headers and inputs the variables.
        if(!header_done){
            std::istringstream input(str);
            std::string header;
            input >> header;

            // reads height, width, start r c, goal r c
            if(header == "HEIGHT"){
                input >> h;
            }
            else if(header == "WIDTH"){
                input >> w;
            }
            else if(header == "START"){
                input >> start_r >> start_c; 
            }
            else if(header == "GOAL"){
                input >> goal_r >> goal_c;
            }
            else{
                // checks if the input is valid
                bool looks_like_grid = (w > 0 && h > 0 && str.size() == static_cast<size_t>(w));
                if(looks_like_grid){
                    for(char ch : str) {
                        if(ch != '.' && ch != '#'){
                            looks_like_grid = false;
                            break;
                        }
                    }
                }
                // some error handling. 
                if(looks_like_grid){
                    header_done = true;
                    grid_lines.push_back(str);
                } else {
                    std::cerr << "NOT VALID INPUT\n";
                    return false;
                }
            }
        }
        else {
            grid_lines.push_back(str);
        }
    }

    // updates width and height vars
    width_ = w;
    height_ = h;
    cells_.assign(width_ * height_, '.'); // assigns every position with '.'
    
    for(int r = 0; r < height_; ++r){
        const std::string& row = grid_lines[r];
        if(static_cast<int>(row.size()) != width_){
            std::cerr << "Row length wrong \n";
            return false;
        }

        for(int c = 0; c < width_; ++c){
            char  ch = row[c];
            int id = ToId(r, c);
            cells_[id] = ch;
        }
    }
    start_id_ = ToId(start_r, start_c);
    goal_id_ = ToId(goal_r, goal_c);

    if(cells_[start_id_]!= '.' || cells_[goal_id_] != '.'){
        std::cerr << "START or GOAL not on open cell\n";
        return false;
    }

return true;
}

//Getting the neighbors
inline int Grid::GetNeighbors(int id, int out[4]) const{
    Cell here = FromId(id);
    int r = here.row;
    int c = here.col;
    int count = 0;

                 // N, E, S, W
    int drow[4] = {-1, 0, 1, 0};
    int dcol[4] = {0, 1, 0, -1};

    for(int k = 0; k< 4; ++k){
        int new_row = r + drow[k];
        int new_col = c + dcol[k];

        // skip if it is out of bounds
        if(!InBounds(new_row, new_col)) continue;

        // skip if blocked
        if(IsBlocked(new_row, new_col)) continue;

        int new_id = ToId(new_row, new_col);
        out[count] = new_id;
        ++count;
    }
    return count;
}


#endif