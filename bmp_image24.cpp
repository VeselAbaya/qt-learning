#include "bmp_image24.h"
#include <QDebug>

Bmp_image24::Bmp_image24(std::string file_path) {
    if (file_path != "") {
        BitMapFileHeader bm_header;
        BitMapInfo       bm_info;

        std::ifstream file;
        file.open(file_path, std::ios::in | std::ios::binary);
        if (file.is_open()) {
            file.read(reinterpret_cast<char*>(&bm_header), sizeof(BitMapFileHeader));
            file.read(reinterpret_cast<char*>(&bm_info), sizeof(BitMapInfo));

            width    = bm_info.biWidth;
            height   = bm_info.biHeight;
            size     = bm_info.biSizeImage;
            bitcount = bm_info.biBitCount;

            // allocation memory for raster image
            raster = new uint8_t*[height];
            raster[0] = new uint8_t[size];
            for (int i = 1; i != height; ++i) {
                raster[i] = raster[i-1] + ((width*3) + ALIGNMENT24(width));
            }

            file.seekg(bm_header.bfOffBits); // here raster starts
            for (int i = 0; i != height; ++i) {
                for (int j = 0; j != width*3 + ALIGNMENT24(width); ++j) {
                    file.read(reinterpret_cast<char*>(&raster[i][j]), 1);
                }
            }
        }

        file.close();
    }
}

Bmp_image24::Bmp_image24(int width, int height): size(height * ((width*3) + ALIGNMENT24(width))), // 24 - bitcount
                                                 width(width),
                                                 height(height),
                                                 bitcount(24) {
    // allocation
    raster = new uint8_t*[height];
    raster[0] = new uint8_t[size];
    for (int i = 1; i != height; ++i) {
        raster[i] = raster[i-1] + ((width*3) + ALIGNMENT24(width));
    }

    for (int i = 0; i != height; ++i) {
        // null init for all bytes in new raster
        for (int j = 0; j != ((width*3) + ALIGNMENT24(width)); ++j) {
            raster[i][j] = 0;
        }
    }
}

Bmp_image24::Bmp_image24(int width, int height, uint8_t* raster): size(height * ((width*3) + ALIGNMENT24(width))), // 24 - bitcount
                                                                  width(width),
                                                                  height(height),
                                                                  bitcount(24) {
    this->raster = new uint8_t*[height];
    this->raster[0] = new uint8_t[size];

    for (int i = 1; i != height; ++i) {
        this->raster[i] = this->raster[i-1] + ((width*3) + ALIGNMENT24(width));
    }

    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != (width*3); ++j) {
            this->raster[i][j] = raster[i*(width*3) + j];
        }

        // alignment
        for (int j = width*3; j != (width*3) + ALIGNMENT24(width); ++j) {
            this->raster[i][j] = 0;
        }
    }
}

Bmp_image24::Bmp_image24(Bmp_image24 const& other) {
    size     = other.size;
    width    = other.width;
    height   = other.height;
    bitcount = other.bitcount;

    // allocation
    raster = new uint8_t*[height];
    raster[0] = new uint8_t[size];
    for (int i = 1; i != height; ++i) {
        raster[i] = raster[i-1] + ((width*3) + ALIGNMENT24(width));
    }

    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != (width*3) + ALIGNMENT24(width); ++j) {
            raster[i][j] = other.raster[i][j];
        }
    }
}


Bmp_image24& Bmp_image24::operator=(Bmp_image24 const& other) {
    delete [] raster;
    delete [] raster[0];

    size     = other.size;
    width    = other.width;
    height   = other.height;
    bitcount = other.bitcount;

    // allocation
    raster = new uint8_t*[other.get_height()];
    raster[0] = new uint8_t[other.get_size()];
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != (width*3) + ALIGNMENT24(width); ++j) {
            raster[i][j] = other.raster[i][j];
        }
    }

    return *this;
}

//-///////////////////////////////////////////////////////////
// displacement

Bmp_image24::Bmp_image24(Bmp_image24&& other): size(other.size),
                                               width(other.width),
                                               height(other.height),
                                               bitcount(other.bitcount) {
    other.size     = 0;
    other.width    = 0;
    other.height   = 0;
    other.bitcount = 0;

    // allocation
    raster = new uint8_t*[other.get_height()];
    raster[0] = new uint8_t[other.get_size()];
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != (width*3) + ALIGNMENT24(width); ++j) {
            raster[i][j] = other.raster[i][j];
        }
    }

    other.raster = nullptr;
}

Bmp_image24& Bmp_image24::operator=(Bmp_image24&& other) {
    delete [] raster[0];
    delete [] raster;

    raster   = other.raster;
    size     = other.size;
    height   = other.height;
    width    = other.width;
    bitcount = other.bitcount;

    other.size     = 0;
    other.width    = 0;
    other.height   = 0;
    other.bitcount = 0;

    // allocation
    raster = new uint8_t*[other.get_height()];
    raster[0] = new uint8_t[other.get_size()];
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != (width*3) + ALIGNMENT24(width); ++j) {
            raster[i][j] = other.raster[i][j];
        }
    }

    other.raster = nullptr;
    return *this;
}

Bmp_image24::~Bmp_image24() {
    delete [] raster[0];
    delete [] raster;
    qDebug() << "here";
}

//-///////////////////////////////////////////////////////////

void Bmp_image24::set_color(int x, int y, QColor const& color) {
    raster[y][x]   = color.blue();
    raster[y][x+1] = color.green();
    raster[y][x+2] = color.red();
}

//-///////////////////////////////////////////////////////////

int Bmp_image24::get_size() const {
    return size;
}

int Bmp_image24::get_height() const {
    return height;
}

int Bmp_image24::get_width() const {
    return width;
}

short Bmp_image24::get_bitcount() const {
    return bitcount;
}

uint8_t* Bmp_image24::get_raster() const {
    uint8_t* copy;
    copy = new uint8_t[height * width*3];
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != width*3; ++j) {
            copy[i*(width*3) + j] = raster[i][j];
        }
    }

    return copy;
}

uint8_t Bmp_image24::get_raster(int i, int j) const {
    return raster[i][j];
}

QRgb Bmp_image24::get_rgb(int x, int y) const {
    return qRgb(raster[height-y-1][x*3 + 2], raster[height-y-1][x*3 + 1], raster[height-y-1][x*3]);
}

QImage Bmp_image24::get_qImage() const {
    QImage image(width, height, QImage::Format_RGB888); // this format for 24-bitcount (8,8,8)
    for (int i = 0; i != height; ++i) {
        for (int j = width-1; j >= 0; --j) {
            image.setPixelColor(j, i, QColor(this->get_rgb(j, i)));
        }
    }

    return image;
}

//-///////////////////////////////////////////////////////////

std::shared_ptr<Bmp_image> Bmp_image24::invert_color() {
    std::shared_ptr<Bmp_image> ret;

    uint8_t* invert_raster = new uint8_t[height*width*3];
    invert_raster = get_raster();
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != width*3; ++j) {
            invert_raster[i*(width*3) + j] = 255 - raster[i][j];
        }
    }

    ret = std::make_shared<Bmp_image>(new Bmp_image24(width, height, invert_raster));
    delete [] invert_raster;
    return ret;
}

void Bmp_image24::grayscale() {
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j < (width*3) + ALIGNMENT24(width); j+=3) {
            unsigned avg = (raster[i][j] + raster[i][j+1] + raster[i][j+2]) / 3;
            raster[i][j]   = static_cast<uint8_t>(avg);
            raster[i][j+1] = static_cast<uint8_t>(avg);
            raster[i][j+2] = static_cast<uint8_t>(avg);
        }
    }
}

void Bmp_image24::invert_color(int x1, int y1, int x2, int y2) {
    // find upper left and lower right corners coordinates
    int x_min = std::min(x1, x2);
    int y_min = std::min(y1, y2);
    int x_max = std::max(x1, x2);
    int y_max = std::max(y1, y2);

    for (int y = y_min; y != y_max; ++y) {
        for (int x = x_min; x != x_max; ++x) {
            this->set_color(x, y, QColor(255 - raster[y][x+2], 255 - raster[y][x+1], 255 - raster[y][x]));
        }
    }
}

void Bmp_image24::grayscale(int x1, int y1, int x2, int y2) {
    // find upper left and lower right corners coordinates
    int x_min = std::min(x1, x2);
    int y_min = std::min(y1, y2);
    int x_max = std::max(x1, x2);
    int y_max = std::max(y1, y2);

    for (int y = y_min; y != y_max; ++y) {
        for (int x = x_min; x < x_max; x+=3) {
            unsigned avg = (raster[y][x] + raster[y][x+1] + raster[y][x+2]) / 3;
            raster[y][x] = static_cast<uint8_t>(avg);
            raster[y][x+1] = static_cast<uint8_t>(avg);
            raster[y][x+2] = static_cast<uint8_t>(avg);
        }
    }
}
