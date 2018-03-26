#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include <QImage>
#include <QRgb>

#include <cstdint> // for uint8_t
#include <fstream>
#include <string>

#define BM_SIZE_INDEX 2
#define BM_WIDTH_INDEX 18
#define BM_HEIGHT_INDEX 22
#define BM_BITCOUNT_INDEX 28
#define BM_OFFBITS_INDEX 10

class Bmp_image {
public:
    Bmp_image(int height, int width, short bitcount); // TODO there must be better implementation of raster image (2d array isn't convinient)
    Bmp_image(std::string file_path);
    Bmp_image(Bmp_image const& other);
    Bmp_image& operator=(Bmp_image const& other);

    ~Bmp_image();

    int get_size();
    int get_height();
    int get_width();
    short get_bitcount();

    uint8_t** get_raster();
    QRgb get_rgb(int i, int j); // return color from pixel on position (row, column)
    QImage get_qImage(); // return QImage from raster image
    void invert_color(); //invert whole image

private:
    int size;
    int height;
    int width;
    short bitcount; // bits on color
    uint8_t** raster;
};

#endif // BMP_IMAGE_H
