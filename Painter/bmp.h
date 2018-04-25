#ifndef BMP_H
#define BMP_H

#include "bmp_image24.h"
#include <QMessageBox>
#include <QErrorMessage>

#define BI_SIZE 40

namespace Bmp {
    Bmp_image* bmp(std::string file_path); // open bmp-file
    Bmp_image* copy(Bmp_image* image);
    Bmp_image* create(int width, int height); // Create new bmp "white" image in 24-bitcount

    void save(Bmp_image* image, std::string file_path="");
}

#endif // BMP_H
