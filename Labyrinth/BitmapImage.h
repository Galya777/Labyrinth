//The picture is made with the help of:
//https://www.youtube.com/watch?v=vqT5j38bWGg
#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
struct Color {
	float red;
	float green;
	float blue;
};
class BitmapImage
{
public:
	BitmapImage(int heigh, int width);
	~BitmapImage();

	Color getColor(int x, int y) const;
	void SetColor(Color color, int x, int y);

	void Read(std::string path);
	void Export(std::string path);

private:
	int hight;
	int width;
	std::vector<Color> colors;
};

