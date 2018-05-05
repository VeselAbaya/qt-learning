#include "bmp_exceptions.h"

Bmp::Bad_bitcount::Bad_bitcount(int bitcount): std::exception{},
                                               bitcount(bitcount) {}

const char* Bmp::Bad_bitcount::what() const throw() {
    return "This version supports only 24 bitcount";
}

int Bmp::Bad_bitcount::err_bitcount() const {
    return bitcount;
}

Bmp::Bad_size::Bad_size(int width, int height): std::exception{},
                                                width(width), height(height) {}

const char* Bmp::Bad_size::what() const throw() {
    return "Incorrect image's raster size";
}

int Bmp::Bad_size::err_width() const {
    return width;
}

int Bmp::Bad_size::err_height() const {
    return height;
}

Bmp::Bad_resize::Bad_resize(int vertical, int horizontal): std::exception{},
                                                  vertical(vertical), horizontal(horizontal) {}

const char* Bmp::Bad_resize::what() const throw() {
    return "Incorrect resize parameters";
}

int Bmp::Bad_resize::err_vertical() const {
    return vertical;
}

int Bmp::Bad_resize::err_horizontal() const {
    return horizontal;
}
