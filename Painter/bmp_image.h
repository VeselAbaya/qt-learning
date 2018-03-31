#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include <QRgb>
#include <QColor>
#include <QImage>

#include <string>

#define BYTE_SIZE 8

#define BM_SIZE_INDEX 2
#define BM_RESERVED1_INDEX 6
#define BM_OFFBITS_INDEX 10
#define BM_WIDTH_INDEX 18
#define BM_HEIGHT_INDEX 22
#define BM_BITCOUNT_INDEX 28

class Bmp_image {
public:
    virtual ~Bmp_image() {}

    // setters
    virtual void set_color(int x, int y, QColor const& color) = 0;

    // getters
    virtual int get_size() const       = 0;
    virtual int get_height() const   = 0;
    virtual int get_width() const    = 0;
    virtual short get_bitcount() const = 0;

    virtual uint8_t* get_raster() const      = 0; // return raster aka byte array
    virtual uint8_t get_raster(int x, int y) const       = 0;
    virtual QRgb get_rgb(int x, int y) const = 0; // return color from pixel on position (row, column)
    virtual QImage get_qImage() const        = 0; // return QImage from raster image
    virtual void invert_color() {}                // invert whole image
    virtual void grayscale() {}                   // convert to grayscale image

    virtual void invert_color(int x1, int y1, int x2, int y2) {}
    virtual void grayscale(int x1, int y1, int x2, int y2) {}
};

#endif // BMP_IMAGE_H
