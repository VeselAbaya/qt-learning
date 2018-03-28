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

                switch(bitcount) {
                    case 24:
                        Bmp_image* bmp_image24 = new Bmp_image24(file_path);
                        return bmp_image24;
                        break;

                    default:
                        break; // TODO there must be dialog with exception
                }
            }
        }
    }
}
