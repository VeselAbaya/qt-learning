#include "bmp.h"

Bmp_image* bmp_init(std::string file_path) {
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
                switch(bitcount) {
                    case 24: bmp_image = new Bmp_image24(file_path); break;
                    default: bmp_image = nullptr;
                }

                return bmp_image;
            }
        }
    }

    return nullptr;
}
