//
// Created by galya777 on 03.03.25.
//

#include "MazeSolver.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <set>

MazeSolver::MazeSolver(BitmapImage& image) : maze(image) {
    int width = maze.getWidth();
    int height = maze.getHeight();

    // Сканиране на изображението за намиране на старт и изходи
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Color color = maze.getColor(x, y);

            if (color == Color(195, 195, 196)) {  // Начална точка
                start = {x, y};
            } else if (color == Color(126, 127, 127)) {  // Изходна зона
                exits.push_back({x, y});
            }
        }
    }
}

bool MazeSolver::isWalkable(Color color) {
    return (color.red == color.green && color.green == color.blue);  // Всички сиви тонове
}

bool MazeSolver::hasKey(Color color) {
    return keysCollected[color];
}

std::vector<std::pair<int, int>> MazeSolver::findPath() {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    std::map<std::pair<int, int>, std::pair<int, int>> prev;
    std::map<std::pair<int, int>, int> minCost;

    pq.push({start.first, start.second, 0});
    minCost[start] = 0;

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        if (std::find(exits.begin(), exits.end(), std::make_pair(node.x, node.y)) != exits.end()) {
            std::vector<std::pair<int, int>> path;
            std::pair<int, int> step = {node.x, node.y};
            while (prev.count(step)) {
                path.push_back(step);
                step = prev[step];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        // Посоки на движение
        std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (auto [dx, dy] : directions) {
            int nx = node.x + dx, ny = node.y + dy;
            if (nx < 0 || ny < 0 || nx >= maze.getWidth() || ny >= maze.getHeight()) continue;

            Color nextColor = maze.getColor(nx, ny);
            if (!isWalkable(nextColor) && !hasKey(nextColor)) continue;

            int stepCost = (nextColor.red == nextColor.green && nextColor.blue == nextColor.red) ? nextColor.red : 1;
            int newCost = node.cost + stepCost;

            if (minCost.find({nx, ny}) == minCost.end() || newCost < minCost[{nx, ny}]) {
                minCost[{nx, ny}] = newCost;
                prev[{nx, ny}] = {node.x, node.y};
                pq.push({nx, ny, newCost});
            }
        }
    }
    return {};  // Няма път до изход
}

void MazeSolver::solve(std::string outputImagePath, std::string outputPath) {
    std::vector<std::pair<int, int>> path = findPath();

    if (path.empty()) {
        std::ofstream outFile(outputPath);
        outFile << "NO SOLUTION" << std::endl;
        outFile.close();
        return;
    }

    std::ofstream outFile(outputPath);
    for (auto [x, y] : path) {
        outFile << x << " " << y << std::endl;
        maze.SetColor(Color(255, 0, 0), x, y);  // Червен път
    }
    outFile.close();

    maze.Export(outputImagePath);
}
