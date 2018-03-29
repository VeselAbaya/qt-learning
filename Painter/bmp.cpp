#include "bmp.h"

Bmp_image* Bmp::read(std::string file_path) {
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

Bmp_image* Bmp::copy(Bmp_image *image) { // TODO maybe need to think about some exceptions
    Bmp_image* copy;
    switch(image->get_bitcount()) {
        case 24: copy = new Bmp_image24(*static_cast<Bmp_image24*>(image)); break;
    }

    return copy;
}

void Bmp::save(Bmp_image *image, std::string file_path) {
    std::ofstream file;
    file.open(file_path);

    if (file.is_open()) {
        file.write("BM", 2);

        file.seekp(BM_RESERVED1_INDEX);
        file.write("0000", 2*sizeof(short)); // First two zeros it's reserved1, second - reserved2

        switch (image->get_bitcount()) {
            case 24: file.write("24", sizeof(int)); break;
        }

        file.write("12", sizeof(int));
        file.write(reinterpret_cast<char*>(image->get_width()), sizeof(short));
        file.write(reinterpret_cast<char*>(image->get_height()), sizeof(short));
        file.write("1", 1);

    }
}
