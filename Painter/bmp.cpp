#include "bmp.h"

// this is "constuctor" for all bitcounts
// return nullptr if bitcount isn't standart
Bmp_image* Bmp::bmp(std::string file_path) {
    if (file_path != "") {
        std::ifstream file(file_path, std::ios::in | std::ios::binary);
        if (file.is_open()) {
            char check[3]{};
            file.read(check, 2);

            if (std::string(check) == "BM") {
                // bitcount reading
                short bitcount;
                file.seekg(BM_BITCOUNT_INDEX);
                file.read(reinterpret_cast<char*>(&bitcount), sizeof(short));
                file.close();

                Bmp_image* bmp_image = nullptr;
                switch(static_cast<int>(bitcount)) {
                    case 24:
                        try {
                            bmp_image = new Bmp_image24(file_path); // There 2 files are reading from two functions (need to fix!)
                        } catch (std::bad_alloc& e) {
                            QErrorMessage err_msg;
                            err_msg.setWindowTitle("Bad allocation");
                            err_msg.showMessage(QString("Not enough memory to do this operation"));
                            err_msg.exec();

                            bmp_image = nullptr;
                        } break;
                    default:
                        QErrorMessage msg_box;
                        msg_box.setWindowTitle("Unsupported bitcount");
                        msg_box.showMessage("This version supports only 24 bitcount\n"
                                        "Uploading image's bitcount: " + QString::number(bitcount));
                        msg_box.setMaximumSize(480, 170);
                        msg_box.setMinimumSize(480, 170);
                        msg_box.setStyleSheet("QPushButton {"
                                              "    color: white;"
                                              "    background-color: rgb(75, 75, 75);"
                                              "}");
                        msg_box.exec();

                        bmp_image = nullptr;
                }

                return bmp_image;
            }
        }
    }

    return nullptr;
}

// "copy constructor" for all bitcounts
Bmp_image* Bmp::copy(Bmp_image *image) { // TODO maybe need to think about some exceptions
    Bmp_image* copy;
    switch(image->get_bitcount()) {
        case 24: copy = new Bmp_image24(*static_cast<Bmp_image24*>(image)); break; // Bmp_image24's copy const
        /* there is no default case because all Bmp_image classes support the invariant
         (here can't be incorrect bitcount) */
    }

    return copy;
}

Bmp_image* Bmp::create(int width, int height) {
    Bmp_image* image = new Bmp_image24(width, height);
    return image;
}

void Bmp::save(Bmp_image *image, std::string file_path) {
    std::ofstream file(file_path, std::ios::out | std::ios::binary);

    if (file.is_open()) {
        BitMapFileHeader bm_header;
        BitMapInfo       bm_info;

        bm_header.bfType1     = 'B';
        bm_header.bfType2     = 'M';
        bm_header.bfSize      = sizeof(BitMapFileHeader) +
                                sizeof(BitMapInfo) +
                                image->get_size(); // whole image size (headers + raster)
        bm_header.bfReserved1 = bm_header.bfReserved2 = 0;

        bm_info.biSize          = BI_SIZE;
        bm_info.biWidth         = image->get_width();
        bm_info.biHeight        = image->get_height();
        bm_info.biPlanes        = 1;
        bm_info.biCompression   = 0;
        bm_info.biSizeImage     = image->get_size();
        bm_info.biXPelsPerMeter = 0;
        bm_info.biYPelsPerMeter = 0;

        switch (image->get_bitcount()) {
            case 24: // 3 - bytes on color; alignment - (width*3)%4
                bm_header.bfOffBits    = 54; // sizeof(BitMapFileHeader) + sizeof(BitMapInfo)
                bm_info.biBitCount     = 24;
                bm_info.biClrUsed      = 0;
                bm_info.biClrImportant = 0;

                file.write(reinterpret_cast<char*>(&bm_header), sizeof(BitMapFileHeader));
                file.write(reinterpret_cast<char*>(&bm_info), sizeof(BitMapInfo));

                // allocation memory for new image
                uint8_t** saving_raster = new uint8_t*[bm_info.biHeight];
                saving_raster[0] = new uint8_t[bm_info.biSizeImage]{};
                for (int i = 1; i != bm_info.biHeight; ++i) {
                    saving_raster[i] = saving_raster[i-1] + (bm_info.biWidth*3) + ALIGNMENT24(bm_info.biWidth);
                }

                for (int i = 0; i != bm_info.biHeight; ++i) {
                    for (int j = 0; j != bm_info.biWidth*3; ++j) {
                        saving_raster[i][j] = image->get_raster(i, j);
                    }
                }

                file.write(reinterpret_cast<char*>(saving_raster[0]),
                                                   bm_info.biHeight * ((bm_info.biWidth*3) + ALIGNMENT24(bm_info.biWidth)));
                file.close();

                delete [] saving_raster[0];
                delete [] saving_raster;
            break;
            /* there is no default case because all Bmp_image classes support the invariant
               (here can't be incorrect bitcount) */
        }
    } else {
        QErrorMessage err_msg;
        err_msg.setWindowTitle("Saving file error");
        err_msg.showMessage("Can't save this file on some reason.");
        err_msg.setStyleSheet("QPushButton {"
                              "    color: white;"
                              "    background-color: rgb(75, 75, 75);"
                              "}");
        err_msg.exec();
    }
}
