#include <gdiplus.h>  // Include GDI+ for image handling
#include "BitmapImage.h"
#include "MazeSolver.h"
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

BitmapImage mazeImage;
bool hasSolution = false;
std::wstring solvedImagePath = L"solved_maze.bmp";  // Path to output image

// Initialize GDI+
void InitGDIPlus() {
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
}

// Load and process the labyrinth
void LoadAndSolveMaze() {
    mazeImage.Read("maze.bmp");
    MazeSolver solver(mazeImage);
    solver.solve("solved_maze.bmp", "solution.txt");

    // Check if the solution file contains "NO SOLUTION"
    std::ifstream file("solution.txt");
    std::string firstLine;
    std::getline(file, firstLine);
    file.close();

    hasSolution = (firstLine != "NO SOLUTION");
}

// Updated Window Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
switch (message)
{
case WM_CREATE:
InitGDIPlus();
LoadAndSolveMaze();
break;

case WM_PAINT:
{
PAINTSTRUCT ps;
HDC hdc = BeginPaint(hWnd, &ps);
Graphics graphics(hdc);

if (hasSolution) {
// Load and display the solved image
Image solvedImage(solvedImagePath.c_str());
graphics.DrawImage(&solvedImage, 0, 0, solvedImage.GetWidth(), solvedImage.GetHeight());
} else {
// Display "No Path" message
std::wstring message = L"No Path Found!";
RECT rect;
GetClientRect(hWnd, &rect);
SetTextColor(hdc, RGB(255, 0, 0));
SetBkMode(hdc, TRANSPARENT);
DrawText(hdc, message.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

EndPaint(hWnd, &ps);
}
break;

case WM_DESTROY:
PostQuitMessage(0);
break;

default:
return DefWindowProc(hWnd, message, wParam, lParam);
}
return 0;
}
