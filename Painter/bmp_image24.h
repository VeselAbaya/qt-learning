#ifndef BMP_IMAGE24_H
#define BMP_IMAGE24_H

#include "bmp_image.h"

#include <QImage>
#include <QRgb>

#include <cstdint> // for uint8_t
#include <fstream>
#include <string>

class Bmp_image24: public Bmp_image {
public:
    Bmp_image24(std::string file_path); // Deprecated, better use: bmp_init() from bmp.h
    Bmp_image24(int width, int height); // TODO there must be better implementation of raster image (2d array isn't convinient)
    Bmp_image24(Bmp_image24 const& other);
    Bmp_image24& operator=(Bmp_image24 const& other);
    Bmp_image24(Bmp_image24&& other);
    Bmp_image24& operator=(Bmp_image24&& other);

    ~Bmp_image24();

    // getters
    int get_size() const;
    int get_height() const;
    int get_width() const;
    short get_bitcount() const;

    uint8_t* get_raster() const;      // return raster aka byte array
    QRgb get_rgb(int x, int y) const; // return color from pixel on position (row, column)
    QImage get_qImage() const;        // return QImage from raster image
    void invert_color();              // invert whole image
    void grayscale();                 // convert to grayscale image

private:

    int size;
    int height;
    int width;
    short bitcount; // bits on color
    uint8_t** raster;
};

#endif // BMP_IMAGE24_H
