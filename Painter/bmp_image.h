#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include "resize_direction.h"

#include <QColor>
#include <QImage>

/*! \def BYTE_SIZE
 * Byte size in bits */
#define BYTE_SIZE 8

/*! \def BM_BITCOUNT_INDEX
 * Order of bytes with information
 * about image bitcount */
#define BM_BITCOUNT_INDEX 28

/*! \struct BitMapFileHeader
 * \brief Struct for bmp file header */
#pragma pack(push, 1)
struct BitMapFileHeader {
    char           bfType1;     /*!< char for 'B' */
    char           bfType2;     /*!< char for 'M' */
    unsigned       bfSize;      /*!< size of a file */
    unsigned short bfReserved1; /*!< Reserved 2 bytes */
    unsigned short bfReserved2; /*!< Reserved 2 bytes */
    unsigned       bfOffBits;   /*!< Order of byte where raster begins */
};

/*! \struct BitMapInfo
 * \brief Struct for bmp information header */
struct BitMapInfo {
    unsigned       biSize;          /*!< This structure size */
    int            biWidth;         /*!< Image width in px */
    int            biHeight;        /*!< Image height in px */
    unsigned short biPlanes;        /*!< Always value: 1 */
    unsigned short biBitCount;      /*!< Image bitcount */
    unsigned       biCompression;   /*!< Compression flag */
    unsigned       biSizeImage;     /*!< Image size on bytes */
    int            biXPelsPerMeter; /*!< Pixel per meter on x-axis */
    int            biYPelsPerMeter; /*!< Pixel per meter on y-axis */
    unsigned       biClrUsed;       /*!< Palette size in cells */
    unsigned       biClrImportant;  /*!< Amount of cells form begin of palette to the last cell(including) */
};
#pragma pack(pop)

/*! \class Bmp_image
 * \brief Abstract base class for all Bmp_image classes with different bitcounts */
class Bmp_image {
public:
    /*! virtual distuctor */
    virtual ~Bmp_image() {}

    /*! \pure
     * \brief Method to set color in (x,y)
     * \param x x-axis pixel coordinate
     * \param y y-axis pixel coordinate
     * \param color Setting color */
    virtual void set_color(int x, int y, QColor const& color) = 0;

    /*! \pure
     * \brief Method to get image size
     * \return Image size in bytes */
    virtual int get_size() const       = 0;

    /*! \pure
     * \brief Method to get image height
     * \return Image height in pixels */
    virtual int get_height() const     = 0;

    /*! \pure
     * \brief Method to get image width
     * \return Image width in pixels */
    virtual int get_width() const      = 0;

    /*! \pure
     * \brief Method to get image bitcount
     * \return Image bitcount in bits/color */
    virtual short get_bitcount() const = 0;

    /*! \pure
     * \brief Method to get raster image
     * \return Image raster byte array like it implements in bmp file */
    virtual uint8_t* get_raster() const = 0;

    /*! \pure
     * \brief Method to get specific raster image byte
     * \return Value of byte on (x,y) image position
     * \param x x-axis byte coordinate
     * \param y y-axis byte coordinate */
    virtual uint8_t get_raster(int x, int y) const = 0;

    /*! \pure
     * \brief Method to get color of specific pixel
     * \return Color from pixel on position (row, column)
     * \param x x-axis byte coordinate
     * \param y y-axis byte coordinate */
    virtual QColor get_color(int x, int y) const = 0;

    /*! \pure
     * \brief Method to get QImage(image)
     * \return QImage image */
    virtual QImage get_qImage() const              = 0;

    /*! \pure
     * \brief Method to invert whole image */
    virtual void invert_color() {}

    /*! \pure
     * \brief Method to grayscale whole image */
    virtual void grayscale() {}

    /*! \pure
     * \brief Method to invert selected rectangle
     * \param x1 x-axis first ractangle point сoodrdinate
     * \param y1 y-axis first ractangle point сoodrdinate
     * \param x2 x-axis opposite ractangle point сoodrdinate
     * \param y2 y-axis opposite ractangle point сoodrdinate */
    virtual void invert_color(int x1, int y1, int x2, int y2) {}

    /*! \pure
     * \brief Method to grayscale selected rectangle
     * \param x1 x-axis first ractangle point сoodrdinate
     * \param y1 y-axis first ractangle point сoodrdinate
     * \param x2 x-axis opposite ractangle point сoodrdinate
     * \param y2 y-axis opposite ractangle point сoodrdinate */
    virtual void grayscale(int x1, int y1, int x2, int y2) {}

    /*! \pure
     * \brief Method to crop image
     * \param vertical_crop Vertical crop size in pixels
     * \param horizontal_crop Horizontal crop size in pixels
     * \param direction Crop direction */
    virtual void crop(int vertical_crop, int horizontal_crop, Bmp::Resize_direction direction) {}

    /*! \pure
     * \brief Method to expanse image with some color
     * \param vertical_exp Vertical expansion size in pixels
     * \param horizontal_exp Horizontal expansion size in pixels
     * \param direction Expanse direction
     * \param color Fill color */
    virtual void expanse(int vertical_exp, int horizontal_crop, Bmp::Resize_direction direction, QColor color) {}
};

#endif // BMP_IMAGE_H
