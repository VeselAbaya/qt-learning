#include "bmp_image.h"
#include <QDebug>
Bmp_image::Bmp_image(std::string file_path): file_path(file_path) {
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
                    raster = new unsigned char*[height];
                    for (int i = 0; i != height; ++i) {
                        raster[i] = new unsigned char[width*3];
                    }

                    int bm_image_index;
                    file.seekg(BM_OFFBITS_INDEX);
                    file.read(reinterpret_cast<char*>(&bm_image_index), sizeof(int));
                    file.seekg(bm_image_index);
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
