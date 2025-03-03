//
// Created by galya777 on 03.03.25.
//

#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "BitmapImage.h"
#include <vector>
#include <queue>
#include <map>

struct Node {
    int x, y, cost;
    bool operator>(const Node& other) const {
        return cost > other.cost;  // За приоритетна опашка (минимален път)
    }
};

class MazeSolver {
private:
    BitmapImage& maze;
    std::pair<int, int> start;
    std::vector<std::pair<int, int>> exits;
    std::map<Color, bool> keysCollected;

    bool isWalkable(Color color);
    bool hasKey(Color color);
    std::vector<std::pair<int, int>> findPath();

public:
    MazeSolver(BitmapImage& image);
    void solve(std::string outputImagePath, std::string outputPath);
};

#endif
