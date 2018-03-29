#ifndef BMP_H
#define BMP_H

#include "bmp_image24.h"

#include <fstream>
#include <string>
#include <cstdint>

namespace Bmp {
    Bmp_image* read(std::string file_path);
    Bmp_image* copy(Bmp_image* image);
}

#endif // BMP_H
