#ifndef BMP_H
#define BMP_H

#include "bmp_image24.h"
#include <QMessageBox>

#define MICROSOFT_PPM 3780 // Pixels per meter for Microsoft screen
                           // link: https://ru.wikipedia.org/wiki/BMP#%D0%A0%D0%B0%D0%B7%D1%80%D0%B5%D1%88%D0%B5%D0%BD%D0%B8%D0%B5_%D0%B8%D0%B7%D0%BE%D0%B1%D1%80%D0%B0%D0%B6%D0%B5%D0%BD%D0%B8%D1%8F
#define BI_SIZE 40

namespace Bmp {
    Bmp_image* bmp(std::string file_path);
    Bmp_image* copy(Bmp_image* image);
    Bmp_image* create(int width, int height); // Create new bmp "white" image in 24-bitcount

    void save(Bmp_image* image, std::string file_path="");
}

#endif // BMP_H
