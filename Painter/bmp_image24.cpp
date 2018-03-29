#include "bmp_image24.h"

Bmp_image24::Bmp_image24(std::string file_path) {
    if (file_path != "") {
        std::ifstream file;
        file.open(file_path, std::ios::in | std::ios::binary);
        if (file.is_open()) {
            char check[3];
            file.read(check, 2);
            check[2] = '\0';

            if (std::string(check) == "BM") {
                file.seekg(BM_WIDTH_INDEX);
                file.read(reinterpret_cast<char*>(&width), sizeof(int));

                file.seekg(BM_HEIGHT_INDEX);
                file.read(reinterpret_cast<char*>(&height), sizeof(int));

                file.seekg(BM_BITCOUNT_INDEX);
                file.read(reinterpret_cast<char*>(&bitcount), sizeof(short));

                size = width * height * bitcount/BYTE_SIZE;

                if (bitcount == 24) {
                    raster = new uint8_t*[height];
                    raster[0] = new uint8_t[height * width*3];
                    for (int i = 1; i != height; ++i) {
                        raster[i] = raster[i-1] + width*3;
                    }

                    int BM_IMAGE_INDEX;
                    file.seekg(BM_OFFBITS_INDEX);
                    file.read(reinterpret_cast<char*>(&BM_IMAGE_INDEX), sizeof(int));
                    file.seekg(BM_IMAGE_INDEX);
                    for (int i = 0; i != height; ++i) {
                        for (int j = 0; j != width*3 + (width*3)%4; ++j) {
                            file.read(reinterpret_cast<char*>(&raster[i][j]), 1);
                        }
                    }
                } else {
                    // TODO there must be dialog with exception (ISN'T BMP FORMAT!!!)
                }
            }
        }

        file.close();
    }
}

Bmp_image24::Bmp_image24(Bmp_image24 const& other) {
    size     = other.size;
    width    = other.width;
    height   = other.height;
    bitcount = other.bitcount;

    raster = new uint8_t*[height];
    for (int i = 0; i != height; ++i) {
        raster[i] = new uint8_t[width*3];
        for (int j = 0; j != width; ++j) {
            raster[i][j] = other.raster[i][j];
        }
    }
}

Bmp_image24::Bmp_image24(int width, int height): size(width * height * bitcount/BYTE_SIZE),
                                                             height(height),
                                                             width(width) {
    raster = new uint8_t*[height];
    raster[0] = new uint8_t[height * width*3];
    for (int i = 1; i != height; ++i) {
        raster[i] = raster[i-1] + width*3;
    }
}

Bmp_image24& Bmp_image24::operator=(Bmp_image24 const& other) {
    size     = other.size;
    width    = other.width;
    height   = other.height;
    bitcount = other.bitcount;

    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != (width*3) + (width*3)%4; ++j) {
            raster[i][j] = other.raster[i][j];
        }
    }

    return *this;
}

Bmp_image24::Bmp_image24(Bmp_image24&& other): size(other.size),
                                         height(other.height),
                                         width(other.width),
                                         bitcount(other.bitcount),
                                         raster(other.raster) {
    other.size     = 0;
    other.width    = 0;
    other.height   = 0;
    other.bitcount = 0;
    other.raster   = nullptr;
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
    other.raster   = nullptr;

    return *this;
}

Bmp_image24::~Bmp_image24() {
    delete [] raster[0];
    delete [] raster;
}

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

uint8_t** Bmp_image24::get_raster() const {
    uint8_t** copy = new uint8_t*[height];
    copy[0] = new uint8_t[height * width*3];
    for (int i = 1; i != height; ++i) {
        copy[i] = copy[i-1] + width*3;
    }

    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != (width*3) + (width*3)%4; ++j) {
            copy[i][j] = raster[i][j];
        }
    }

    return copy;
}

QRgb Bmp_image24::get_rgb(int x, int y) const {
    return qRgb(raster[height-y-1][x*3 + 2], raster[height-y-1][x*3 + 1], raster[height-y-1][x*3]);
}

QImage Bmp_image24::get_qImage() const {
    QImage image(width, height, QImage::Format_RGB888);
    for (int i = 0; i != height; ++i) {
        for (int j = width-1; j >= 0; --j) {
            image.setPixelColor(j, i, QColor(this->get_rgb(j, i)));
        }
    }

    return image;
}

void Bmp_image24::invert_color() {
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != (width*3) + (width*3)%4; ++j) {
            raster[i][j] = 255 - raster[i][j];
        }
    }
}

void Bmp_image24::grayscale() {
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j < (width*3) + (width*3)%4; j+=3) {
            int avg = (raster[i][j] + raster[i][j+1] + raster[i][j+2]) / 3;
            raster[i][j] = static_cast<uint8_t>(avg);
            raster[i][j+1] = static_cast<uint8_t>(avg);
            raster[i][j+2] = static_cast<uint8_t>(avg);
        }
    }
}
