#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include <QRgb>
#include <QImage>

#include <string>

#define BYTE_SIZE 8
#define BM_WIDTH_INDEX 18
#define BM_HEIGHT_INDEX 22
#define BM_BITCOUNT_INDEX 28
#define BM_OFFBITS_INDEX 10

class Bmp_image {
public:
    virtual ~Bmp_image() {}

    // getters
    virtual int get_size() const       = 0;
    virtual int get_height() const     = 0;
    virtual int get_width() const      = 0;
    virtual short get_bitcount() const = 0;

    virtual uint8_t** get_raster() const     = 0; // return raster aka byte array
    virtual QRgb get_rgb(int x, int y) const = 0; // return color from pixel on position (row, column)
    virtual QImage get_qImage() const        = 0; // return QImage from raster image
    virtual void invert_color()              = 0; // invert whole image
    virtual void grayscale()                 = 0; // convert to grayscale image
};

#endif // BMP_IMAGE_H
