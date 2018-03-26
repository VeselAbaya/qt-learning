#include "bmp_image.h"

Bmp_image::Bmp_image(std::string file_path) {
    if (file_path != "") {
        std::ifstream file;
        file.open(file_path, std::ios::in | std::ios::binary);
        if (file.is_open()) {
            char check[3];
            file.read(check, 2);
            check[2] = '\0';

            if (std::string(check) == "BM") {
                file.seekg(BM_SIZE_INDEX);
                file.read(reinterpret_cast<char*>(&size), sizeof(int));

                file.seekg(BM_WIDTH_INDEX);
                file.read(reinterpret_cast<char*>(&width), sizeof(int));

                file.seekg(BM_HEIGHT_INDEX);
                file.read(reinterpret_cast<char*>(&height), sizeof(int));

                file.seekg(BM_BITCOUNT_INDEX);
                file.read(reinterpret_cast<char*>(&bitcount), sizeof(short));
                if (bitcount == 24) {
                    raster = new uint8_t*[height];
                    for (int i = 0; i != height; ++i) {
                        raster[i] = new uint8_t[width*3];
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
                    // TODO there must be dialog with exception
                }
            }
        }
    }
}

Bmp_image::Bmp_image(Bmp_image const& other) {
    size = other.size;
    width = other.width;
    height = other.height;
    bitcount = other.bitcount;

    raster = new uint8_t*[height];
    for (int i = 0; i != height; ++i) {
        raster[i] = new uint8_t[width*3];
        for (int j = 0; j != width; ++j) {
            raster[i][j] = other.raster[i][j];
        }
    }
}

Bmp_image::Bmp_image(int height, int width, short bitcount): height(height),
                                                             width(width),
                                                             bitcount(bitcount) {
    raster = new uint8_t*[height];
    for (int i = 0; i != height; ++i) {
        raster[i] = new uint8_t[width*3];
    }
}

Bmp_image& Bmp_image::operator=(Bmp_image const& other) {
    size = other.size;
    width = other.width;
    height = other.height;
    bitcount = other.bitcount;

    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != width*3; ++j) {
            raster[i][j] = other.raster[i][j];
        }
    }

    return *this;
}

Bmp_image::~Bmp_image() {
    for (int i = 0; i != height; ++i) {
        delete raster[i];
    }

    delete raster;
}

int Bmp_image::get_size() {
    return size;
}

int Bmp_image::get_height() {
    return height;
}

int Bmp_image::get_width() {
    return width;
}

short Bmp_image::get_bitcount() {
    return bitcount;
}

unsigned char** Bmp_image::get_raster() {
    return raster;
}

QRgb Bmp_image::get_rgb(int i, int j) {
    return qRgb(raster[height-i-1][j*3 + 2], raster[height-i-1][j*3 + 1], raster[height-i-1][j*3]);
}

QImage Bmp_image::get_qImage() {
    QImage image(width, height, QImage::Format_RGB888);
    for (int i = 0; i != height; ++i) {
        for (int j = width-1; j >= 0; --j) {
            image.setPixelColor(j, i, QColor(this->get_rgb(i, j)));
        }
    }

    return image;
}

void Bmp_image::invert_color() {
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != width*3 + (width*3)%4; ++j) {
            raster[i][j] = 255 - raster[i][j];
        }
    }
}
