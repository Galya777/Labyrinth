#include "BitmapImage.h"

BitmapImage::BitmapImage(int heigh, int width)
{
	this->hight = heigh;
	this->width = width;
}

BitmapImage::~BitmapImage()
{
}

Color BitmapImage::getColor(int x, int y) const
{
	return colors[y*width+x];
}

void BitmapImage::SetColor(Color color, int x, int y)
{
	colors[y * width + x].red = color.red;
	colors[y * width + x].green = color.green;
	colors[y * width + x].blue = color.blue;
}

void BitmapImage::Read(std::string path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << path << std::endl;
        return;
    }

    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (fileHeader.fileType != 0x4D42) { // 'BM' in little-endian
        std::cerr << "Not a valid BMP file." << std::endl;
        return;
    }

    this->width = infoHeader.width;
    this->hight = abs(infoHeader.height);
    colors.resize(width * hight);

    file.seekg(fileHeader.dataOffset, std::ios::beg);

    int rowSize = ((width * 3 + 3) / 4) * 4;
    std::vector<uint8_t> rowBuffer(rowSize);

    for (int y = 0; y < hight; y++) {
        file.read(reinterpret_cast<char*>(rowBuffer.data()), rowSize);
        for (int x = 0; x < width; x++) {
            int index = (hight - 1 - y) * width + x;
            colors[index].blue = rowBuffer[x * 3];
            colors[index].green = rowBuffer[x * 3 + 1];
            colors[index].red = rowBuffer[x * 3 + 2];
        }
    }

    file.close();
}


void BitmapImage::Export(std::string path)
{
	std::ofstream f;
	f.open(path, std::ios::out);
	if (!f.is_open()) {
		std::cout << "Problem with the file!";
		return;
	}
	
}
