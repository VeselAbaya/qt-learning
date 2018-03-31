#include "bmp.h"
#include <QDebug>
Bmp_image* Bmp::bmp(std::string file_path) {
    if (file_path != "") {
        std::ifstream file;
        file.open(file_path, std::ios::in | std::ios::binary);
        if (file.is_open()) {
            char check[3];
            file.read(check, 2);
            check[2] = '\0';

            if (std::string(check) == "BM") {
                short bitcount;
                file.seekg(BM_BITCOUNT_INDEX);
                file.read(reinterpret_cast<char*>(&bitcount), sizeof(short));

                Bmp_image* bmp_image;
                file.close();
                switch(static_cast<int>(bitcount)) {
                    case 24: bmp_image = new Bmp_image24(file_path); break; // There 2 files are reading from two functions (need to fix!)
                    default: qDebug() << "zhopa"; bmp_image = nullptr;
                }

                return bmp_image;
            }
        }
    }

    return nullptr;
}

Bmp_image* Bmp::copy(Bmp_image *image) { // TODO maybe need to think about some exceptions
    Bmp_image* copy;
    switch(image->get_bitcount()) {
        case 24: copy = new Bmp_image24(*static_cast<Bmp_image24*>(image)); break;
    }

    return copy;
}

void Bmp::save(Bmp_image *image, std::string file_path) {
    std::ofstream file;
    file.open(file_path, std::ios::out | std::ios::binary);

    if (file.is_open()) {
        BitMapFileHeader bm_header;
        BitMapInfo       bm_info;

        bm_header.bfType1     = 'B';
        bm_header.bfType2     = 'M';
        bm_header.bfSize      = sizeof(BitMapFileHeader) + sizeof(BitMapInfo) + image->get_size();
        bm_header.bfReserved1 = bm_header.bfReserved2 = 0;

        bm_info.biSize          = 40;
        bm_info.biWidth         = image->get_width();
        bm_info.biHeight        = image->get_height();
        bm_info.biPlanes        = 1;
        bm_info.biCompression   = 0;
        bm_info.biSizeImage     = image->get_size();
        bm_info.biXPelsPerMeter = MICROSOFT_PPM;
        bm_info.biYPelsPerMeter = MICROSOFT_PPM;

        switch (image->get_bitcount()) {
            case 24:
                bm_header.bfOffBits    = 54;
                bm_info.biBitCount     = 24;
                bm_info.biClrUsed      = 0;
                bm_info.biClrImportant = 0;

                file.write(reinterpret_cast<char*>(&bm_header), sizeof(BitMapFileHeader));
                file.write(reinterpret_cast<char*>(&bm_info), sizeof(BitMapInfo));

                uint8_t** byte_array = new uint8_t*[bm_info.biHeight];
                byte_array[0] = new uint8_t[bm_info.biHeight * ((bm_info.biWidth*3) + (bm_info.biWidth*3)%4)];
                for (int i = 1; i != bm_info.biHeight; ++i) {
                    byte_array[i] = byte_array[i-1] + (bm_info.biWidth*3) + (bm_info.biWidth*3)%4;
                }

                for (int i = 0; i != bm_info.biHeight; ++i) {
                    for (int j = 0; j != bm_info.biWidth*3; ++j) {
                        byte_array[i][j] = image->get_raster(i, j);
                    }

                    for (int j = bm_info.biWidth*3; j != ((bm_info.biWidth*3) + (bm_info.biWidth*3)%4); ++j) {
                        byte_array[i][j] = 0;
                    }
                }

                file.write(reinterpret_cast<char*>(byte_array[0]), bm_info.biHeight * ((bm_info.biWidth*3) + (bm_info.biWidth*3)%4));
            break;
        }
    }
}
