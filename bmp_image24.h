#ifndef BMP_IMAGE24_H
#define BMP_IMAGE24_H

#include "bmp_image.h"

#define ALIGNMENT24(width) ((width)*3)%4

#include <cstdint>   // for uint8_t
#include <algorithm> // for max, min
#include <fstream>
#include <string>

class Bmp_image24: public Bmp_image {
public:
    Bmp_image24(std::string file_path);     // deprecated, better use: Bmp::bmp() from bmp.h
    Bmp_image24(int width, int height);
    Bmp_image24(int width, int height, uint8_t* raster); // raster - just a byte array (work without alignment)
    Bmp_image24(Bmp_image24 const& other);
    Bmp_image24& operator=(Bmp_image24 const& other);
    Bmp_image24(Bmp_image24&& other);
    Bmp_image24& operator=(Bmp_image24&& other);

    ~Bmp_image24();

    // setters
    void set_color(int x, int y, QColor const& color);

    // getters
    int get_size() const;                   // return size in bytes
    int get_width() const;                  // return width in pixels
    int get_height() const;                 // return height in pixels
    short get_bitcount() const;
    uint8_t* get_raster() const;            // return raster like byte array
    uint8_t get_raster(int i, int j) const; // return raster byte on i-row and j-column

    QRgb get_rgb(int x, int y) const;       // return color from pixel on position (row, column)
    QImage get_qImage() const;              // return QImage from raster image
    std::shared_ptr<Bmp_image> invert_color();                    // invert whole image
    void grayscale();                       // convert to grayscale image

    void invert_color(int x1, int y1, int x2, int y2); // invert only rectangle
    void grayscale(int x1, int y1, int x2, int y2);    // grayscale only rectangle
private:

    int size;         // size in bytes
    int width;        // width in pixels
    int height;       // height in pixels
    short bitcount;   // bits on color
    uint8_t** raster; // raster image in bytes
};

#endif // BMP_IMAGE24_H
