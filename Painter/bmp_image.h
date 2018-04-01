#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include <QRgb>
#include <QColor>
#include <QImage>

#define BYTE_SIZE 8

#define BM_BITCOUNT_INDEX 28

#pragma pack(push, 1)
struct BitMapFileHeader {
    char           bfType1; // 'B'
    char           bfType2; // 'M'
    unsigned       bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned       bfOffBits;
};

struct BitMapInfo {
    unsigned       biSize;
    int            biWidth;
    int            biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned       biCompression;
    unsigned       biSizeImage;
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned       biClrUsed;
    unsigned       biClrImportant;
};
#pragma pack(pop)

class Bmp_image {
public:
    virtual ~Bmp_image() {}

    // setters
    virtual void set_color(int x, int y, QColor const& color) = 0;

    // getters
    virtual int get_size() const       = 0;
    virtual int get_height() const     = 0;
    virtual int get_width() const      = 0;
    virtual short get_bitcount() const = 0;

    virtual uint8_t* get_raster() const            = 0; // return raster aka byte array
    virtual uint8_t get_raster(int x, int y) const = 0;
    virtual QRgb get_rgb(int x, int y) const       = 0; // return color from pixel on position (row, column)
    virtual QImage get_qImage() const              = 0; // return QImage from raster image
    virtual void invert_color() {}                      // invert whole image
    virtual void grayscale() {}                         // convert to grayscale image

    virtual void invert_color(int x1, int y1, int x2, int y2) {}
    virtual void grayscale(int x1, int y1, int x2, int y2) {}
};

#endif // BMP_IMAGE_H
