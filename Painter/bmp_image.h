#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include <QRgb>
#include <fstream>
#include <string>

#define BM_SIZE_INDEX 2
#define BM_WIDTH_INDEX 18
#define BM_HEIGHT_INDEX 22
#define BM_BITCOUNT_INDEX 28
#define BM_OFFBITS_INDEX 10

class Bmp_image {
public:
    Bmp_image(std::string file_path);

    ~Bmp_image();

    int get_size();
    int get_height();
    int get_width();
    short get_bitcount();
    unsigned char** get_raster();
    QRgb get_rgb(int i, int j); // return color from pixel on position (row, column)

private:
    std::string file_path;
    int size;
    int height;
    int width;
    short bitcount; // bits on color
    unsigned char** raster;
};

#endif // BMP_IMAGE_H
