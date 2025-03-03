//
// Created by galya777 on 03.03.25.
//
#include "BitmapImage.h"
#include "MazeSolver.h"

int main() {
    BitmapImage mazeImage;
    mazeImage.Read("maze.bmp");

    MazeSolver solver(mazeImage);
    solver.solve("solved_maze.bmp", "solution.txt");

    return 0;
}
