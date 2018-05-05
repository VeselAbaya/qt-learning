#ifndef BMP_IMAGE24_H
#define BMP_IMAGE24_H

#include "bmp_image.h"

/*! \def ALIGNMENT24(width)
 * Macros which return amount of needed alignment in bytes
 * It's accept width of raster image in bytes */
#define ALIGNMENT24(width) (4*(((width)*3)%4 ? 1 : 0) - ((width)*3)%4)

#include <QErrorMessage>

#include <cstdint>   // for uint8_t
#include <algorithm> // for max, min
#include <fstream>
#include <string>

/*! \class Bmp_image24
 * \brief Bmp_image implementation for 24-bitcount images */
class Bmp_image24: public Bmp_image {
public:
    /*! Constructor
     * \param file_path Image file path
     * \remark better use: Bmp::bmp() from bmp.h */
    Bmp_image24(std::string file_path);

    /*! Constructor
     * \param width Image width in pixels
     * \param height Image height in pixels
     * \param raster Image raster
     * \throws Bmp::Bad_size
     * \remark in case of nullptr white image will be created */
    Bmp_image24(int width, int height, uint8_t* raster=nullptr);

    /*! Copy constructor */
    Bmp_image24(Bmp_image24 const& other);

    /*! Assignment operator */
    Bmp_image24& operator=(Bmp_image24 const& other);

    /*! Relocating сopy constructor */
    Bmp_image24(Bmp_image24&& other);

    /*! Relocating asiignment operator */
    Bmp_image24& operator=(Bmp_image24&& other);

    ~Bmp_image24();

    // setters
    void set_color(int x, int y, QColor const& color);

    // getters
    int get_size() const;                      // return size in bytes
    int get_width() const;
    int get_height() const;
    short get_bitcount() const;
    uint8_t* get_raster() const; // return raster like byte array
    uint8_t get_raster(int i, int j) const;    // return raster byte on i-row and j-column

    QColor get_color(int x, int y) const;       // return color from pixel on position (row, column)
    QImage get_qImage() const;                  // return QImage from raster image
    void invert_color();                        // invert whole image
    void grayscale();                           // convert to grayscale image

    virtual void invert_color(int x1, int y1, int x2, int y2); // invert only rectangle
    virtual void grayscale(int x1, int y1, int x2, int y2);    // grayscale only rectangle

    virtual void crop(int vertical_crop, int horizontal_crop, Bmp::Resize_direction direction);
    virtual void expanse(int vertical_exp, int horizontal_crop, Bmp::Resize_direction direction, QColor color);
private:

    int size;         /*!< Image size in bytes */
    int width;        /*!< Image width in px */
    int height;       /*!< Image height in px */
    short bitcount;   /*!< Image bitcount in bits/color */
    uint8_t** raster; /*!< Raster image */
};

#endif // BMP_IMAGE24_H
