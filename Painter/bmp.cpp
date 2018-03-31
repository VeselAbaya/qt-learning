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
        // BITMAP FILE HEADER
        file.write("BM", 2);

        int width = image->get_width();
        int height = image->get_height();
        int size = image->get_size();
        int file_size = 14 + 40 + height * ((width*3) + (width*3)%4);
        file.write(reinterpret_cast<char*>(&file_size), sizeof(int));

        int reserved01 = 0;
        int reserved02 = 0;
        file.write(reinterpret_cast<char*>(&reserved01), sizeof(short)); // First two zeros it's reserved1, second - reserved2
        file.write(reinterpret_cast<char*>(&reserved02), sizeof(short));


        switch (image->get_bitcount()) {
            case 24:
                file.write("54", sizeof(int)); // BM_OFFBITS_INDEX
                file.seekp(BM_BITCOUNT_INDEX);
                file.write("24", sizeof(short)); // bitcount

                file.seekp(54);
                uint8_t** byte_array = new uint8_t*[height];
                byte_array[0] = new uint8_t[height * ((width*3) + (width*3)%4)];
                for (int i = 1; i != height; ++i) {
                    byte_array[i] = byte_array[i-1] + (width*3) + (width*3)%4;
                }

                for (int i = 0; i != height; ++i) {
                    for (int j = 0; j != width*3; ++j) {
                        byte_array[i][j] = image->get_raster(i, j);
                    }

                    for (int j = width*3; j != ((width*3) + (width*3)%4); ++j) {
                        byte_array[i][j] = 0;
                    }
                } file.write(reinterpret_cast<char*>(byte_array[0]), height * ((width*3) + (width*3)%4));

                file.seekp(BM_OFFBITS_INDEX + sizeof(int));
                break;
        }

        //BITMAP INFO HEADER
        file.write("40", sizeof(int)); // biSize
        file.write(reinterpret_cast<char*>(&width), sizeof(int)); // biWidth
        file.write(reinterpret_cast<char*>(&height), sizeof(int)); // biHeight
        file.write("1", sizeof(short)); // biPlanes
        file.seekp(BM_BITCOUNT_INDEX + sizeof(short)); // seek because of bitcount have been written earlier
        file.write("0", sizeof(int)); // biCompression
        file.write(reinterpret_cast<char*>(&size), sizeof(int)); // biSizeImage
        file.write("3780", sizeof(int)); // biXPelsPerMeter
        file.write("3780", sizeof(int)); // biYPelsPerMeter
        file.write("0", sizeof(int)); // biCrlUsed
        file.write("0", sizeof(int)); // biCrlImportant

        file.close();

        //testing
        char BM[3];
        BM[2] = '\0';
        int test_size;
        short reserved1, reserved2;
        unsigned offbits;
        std::ifstream file;
        file.open(file_path, std::ios::in | std::ios::binary);

        file.read(BM, 2);
        qDebug() << BM;

        file.read(reinterpret_cast<char*>(&test_size), sizeof(int));
        qDebug() << test_size;

        file.read(reinterpret_cast<char*>(&reserved1), sizeof(short));
        file.read(reinterpret_cast<char*>(&reserved2), sizeof(short));
        qDebug() << reserved1 << reserved2;

        file.seekg(BM_OFFBITS_INDEX);
        file.read(reinterpret_cast<char*>(&offbits), sizeof(int));
        qDebug() << offbits;
    }
}
