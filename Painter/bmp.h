#ifndef BMP_H
#define BMP_H

#include "bmp_image24.h"

#include <fstream>
#include <string>
#include <cstdint>

Bmp_image* bmp_init(std::string file_path);

#endif // BMP_H
