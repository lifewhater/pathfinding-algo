// src/grid.hpp (ADT Overview)
// Purpose: Grid model. Owns cells ('.' open, '#' wall), dimensions, and S/G positions.
// Provides neighbor queries and utility conversions between (row,col) and linear ids.
// Students implement: LoadFromFile, Generate, InBounds, IsBlocked, GetNeighbors, etc.

#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
#include <cctype>

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


// Load from file map done. Made a test map that is loaded.
bool Grid::LoadFromFile(const std::string& path){
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << path << "\n";
        return false;
    }

    auto trim = [](const std::string& s) -> std::string {
        size_t start = s.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) return "";
        size_t end = s.find_last_not_of(" \t\r\n");
        return s.substr(start, end - start + 1);
    };

    bool have_width = false;
    bool have_height = false;
    bool have_start = false;
    bool have_goal = false;
    int width = 0;
    int height = 0;
    Cell start{ -1, -1 };
    Cell goal{ -1, -1 };
    std::vector<std::string> rows;
    bool in_body = false;
    std::string line;

    while (std::getline(file, line)) {
        std::string working = line;

        if (!in_body) {
            std::string trimmed = trim(working);
            if (trimmed.empty()) continue;
            if (trimmed[0] == '#') continue; // header comment

            bool looks_like_grid = trimmed[0] == '.' || trimmed[0] == '#';
            if (looks_like_grid) {
                if (!(have_width && have_height && have_start && have_goal)) {
                    std::cerr << "Encountered grid body before all headers were read.\n";
                    return false;
                }
                in_body = true;
                working = trimmed;
            } else {
                std::istringstream iss(trimmed);
                std::string key;
                iss >> key;
                if (key.empty()) continue;
                std::string upper_key = key;
                std::transform(upper_key.begin(), upper_key.end(), upper_key.begin(),
                               [](unsigned char ch) { return static_cast<char>(std::toupper(ch)); });

                if (upper_key == "WIDTH") {
                    if (!(iss >> width) || width <= 0) {
                        std::cerr << "Invalid WIDTH value.\n";
                        return false;
                    }
                    have_width = true;
                } else if (upper_key == "HEIGHT") {
                    if (!(iss >> height) || height <= 0) {
                        std::cerr << "Invalid HEIGHT value.\n";
                        return false;
                    }
                    have_height = true;
                } else if (upper_key == "START") {
                    if (!(iss >> start.row >> start.col)) {
                        std::cerr << "Invalid START line.\n";
                        return false;
                    }
                    have_start = true;
                } else if (upper_key == "GOAL") {
                    if (!(iss >> goal.row >> goal.col)) {
                        std::cerr << "Invalid GOAL line.\n";
                        return false;
                    }
                    have_goal = true;
                } else {
                    std::cerr << "Unknown header line: " << key << "\n";
                    return false;
                }
                continue;
            }
        }

        if (in_body) {
            if (!have_width) {
                std::cerr << "Grid body encountered without WIDTH.\n";
                return false;
            }
            if (static_cast<int>(working.size()) != width) {
                std::cerr << "Grid row width mismatch.\n";
                return false;
            }
            for (char ch : working) {
                if (ch != '.' && ch != '#') {
                    std::cerr << "Invalid grid character: " << ch << "\n";
                    return false;
                }
            }
            rows.push_back(working);
        }
    }

    if (!(have_width && have_height && have_start && have_goal)) {
        std::cerr << "Missing required header fields.\n";
        return false;
    }
    if (static_cast<int>(rows.size()) != height) {
        std::cerr << "Expected " << height << " rows, got " << rows.size() << ".\n";
        return false;
    }
    if (start.row < 0 || start.row >= height || start.col < 0 || start.col >= width) {
        std::cerr << "START is out of bounds.\n";
        return false;
    }
    if (goal.row < 0 || goal.row >= height || goal.col < 0 || goal.col >= width) {
        std::cerr << "GOAL is out of bounds.\n";
        return false;
    }
    if (rows[start.row][start.col] != '.' || rows[goal.row][goal.col] != '.') {
        std::cerr << "START and GOAL must be on '.' cells.\n";
        return false;
    }

    height_ = height;
    width_ = width;
    cells_.assign(height_ * width_, '#');
    for (int r = 0; r < height_; ++r) {
        for (int c = 0; c < width_; ++c) {
            cells_[ToId(r, c)] = rows[r][c];
        }
    }
    start_id_ = ToId(start.row, start.col);
    goal_id_ = ToId(goal.row, goal.col);
    return true;
}

bool Grid::Generate(int height, int width, double density, unsigned int seed) {
    if (height <= 0 || width <= 0) {
        std::cerr << "Height and width must be positive for generation.\n";
        return false;
    }
    if (density < 0.0 || density > 1.0) {
        std::cerr << "Density must be between 0 and 1.\n";
        return false;
    }

    height_ = height;
    width_ = width;
    cells_.assign(height_ * width_, '.');

    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (int r = 0; r < height_; ++r) {
        for (int c = 0; c < width_; ++c) {
            if ((r == 0 && c == 0) || (r == height_ - 1 && c == width_ - 1)) {
                cells_[ToId(r, c)] = '.';
                continue;
            }
            cells_[ToId(r, c)] = (dist(rng) < density) ? '#' : '.';
        }
    }

    start_id_ = ToId(0, 0);
    goal_id_ = ToId(height_ - 1, width_ - 1);
    cells_[start_id_] = '.';
    cells_[goal_id_] = '.';
    return true;
}

bool Grid::InBounds(int r, int c) const {
    return r >= 0 && c >= 0 && r < height_ && c < width_;
}

bool Grid::IsBlocked(int r, int c) const {
    if (!InBounds(r, c)) return true;
    return cells_[ToId(r, c)] == '#';
}

int Grid::GetNeighbors(int id, int out[4]) const {
    if (id < 0 || id >= height_ * width_) return 0;
    Cell cell = FromId(id);
    static const int dr[4] = { -1, 0, 1, 0 };
    static const int dc[4] = { 0, 1, 0, -1 };
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        int nr = cell.row + dr[i];
        int nc = cell.col + dc[i];
        if (InBounds(nr, nc) && !IsBlocked(nr, nc)) {
            out[count++] = ToId(nr, nc);
        }
    }
    return count;
}

#endif
