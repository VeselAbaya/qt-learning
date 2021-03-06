#include "bmp_image24.h"

Bmp_image24::Bmp_image24(std::string file_path) {
    if (file_path != "") {
        BitMapFileHeader bm_header;
        BitMapInfo       bm_info;

        std::ifstream file(file_path, std::ios::in | std::ios::binary);
        if (file.is_open()) {
            file.read(reinterpret_cast<char*>(&bm_header), sizeof(BitMapFileHeader));
            file.read(reinterpret_cast<char*>(&bm_info), sizeof(BitMapInfo));

            width    = bm_info.biWidth;
            height   = bm_info.biHeight;
            size     = bm_info.biSizeImage;
            bitcount = bm_info.biBitCount;

            // allocation memory for raster image
            raster = new uint8_t*[height];
            raster[0] = new uint8_t[size];
            for (int i = 1; i != height; ++i) {
                raster[i] = raster[i-1] + ((width*3) + ALIGNMENT24(width));
            }

            file.seekg(bm_header.bfOffBits); // here raster starts
            for (int i = 0; i != height; ++i) {
                for (int j = 0; j != width*3 + ALIGNMENT24(width); ++j) {
                    file.read(reinterpret_cast<char*>(&raster[i][j]), 1);
                }
            }

            file.close();
        }
    }
}

Bmp_image24::Bmp_image24(int width, int height, uint8_t* raster): size(height * ((width*3) + ALIGNMENT24(width))), // 24 - bitcount
                                                                  width(width),
                                                                  height(height),
                                                                  bitcount(24) {
    if (width < 0 || height < 0) {
        throw Bmp::Bad_size(width, height);
    }

    this->raster = new uint8_t*[height];
    this->raster[0] = new uint8_t[size]{};
    for (int i = 1; i != height; ++i) {
        this->raster[i] = this->raster[i-1] + ((width*3) + ALIGNMENT24(width));
    }

    if (raster) {
        for (int i = 0; i != height; ++i) {
            for (int j = 0; j != (width*3); ++j) {
                this->raster[i][j] = raster[i*(width*3) + j];
            }
        }
    } else {
        for (int i = 0; i != height; ++i) {
            // null init for all bytes in new raster
            for (int j = 0; j != ((width*3) + ALIGNMENT24(width)); ++j) {
                this->raster[i][j] = 255;
            }
        }
    }
}

Bmp_image24::Bmp_image24(Bmp_image24 const& other) {
    size     = other.size;
    width    = other.width;
    height   = other.height;
    bitcount = other.bitcount;

    // allocation
    raster = new uint8_t*[height];
    raster[0] = new uint8_t[size];
    for (int i = 1; i != height; ++i) {
        raster[i] = raster[i-1] + ((width*3) + ALIGNMENT24(width));
    }

    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != (width*3) + ALIGNMENT24(width); ++j) {
            raster[i][j] = other.raster[i][j];
        }
    }
}

Bmp_image24& Bmp_image24::operator=(Bmp_image24 const& other) {
    delete [] raster;
    delete [] raster[0];

    size     = other.size;
    width    = other.width;
    height   = other.height;
    bitcount = other.bitcount;

    // allocation
    raster = new uint8_t*[other.get_height()];
    raster[0] = new uint8_t[other.get_size()];
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != (width*3) + ALIGNMENT24(width); ++j) {
            raster[i][j] = other.raster[i][j];
        }
    }

    return *this;
}

//-///////////////////////////////////////////////////////////
// displacement

Bmp_image24::Bmp_image24(Bmp_image24&& other): size(other.size),
                                               width(other.width),
                                               height(other.height),
                                               bitcount(other.bitcount) {
    other.size     = 0;
    other.width    = 0;
    other.height   = 0;
    other.bitcount = 0;

    // allocation
    raster = new uint8_t*[other.get_height()];
    raster[0] = new uint8_t[other.get_size()];
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != (width*3) + ALIGNMENT24(width); ++j) {
            raster[i][j] = other.raster[i][j];
        }
    }

    other.raster = nullptr;
}

Bmp_image24& Bmp_image24::operator=(Bmp_image24&& other) {
    delete [] raster[0];
    delete [] raster;

    size     = other.size;
    height   = other.height;
    width    = other.width;
    bitcount = other.bitcount;

    other.size     = 0;
    other.width    = 0;
    other.height   = 0;
    other.bitcount = 0;

    // allocation
    raster = new uint8_t*[other.get_height()];
    raster[0] = new uint8_t[other.get_size()];
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != (width*3) + ALIGNMENT24(width); ++j) {
            raster[i][j] = other.raster[i][j];
        }
    }

    other.raster = nullptr;
    return *this;
}

Bmp_image24::~Bmp_image24() {
    delete [] raster[0];
    delete [] raster;
}

//-///////////////////////////////////////////////////////////

void Bmp_image24::set_color(int x, int y, QColor const& color) {
    raster[height-y-1][x*3]   = color.blue(); // this magic because of invert order in bmp raster
    raster[height-y-1][x*3+1] = color.green();
    raster[height-y-1][x*3+2] = color.red();
}

//-///////////////////////////////////////////////////////////

int Bmp_image24::get_size() const {
    return size;
}

int Bmp_image24::get_height() const {
    return height;
}

int Bmp_image24::get_width() const {
    return width;
}

short Bmp_image24::get_bitcount() const {
    return bitcount;
}

uint8_t* Bmp_image24::get_raster() const {
    uint8_t* copy;
    copy = new uint8_t[height * width*3];
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != width*3; ++j) {
            copy[i*(width*3) + j] = raster[i][j];
        }
    }

    return copy;
}

uint8_t Bmp_image24::get_raster(int i, int j) const {
    return raster[i][j];
}

QColor Bmp_image24::get_color(int x, int y) const {
    return qRgb(raster[height-y-1][x*3 + 2], raster[height-y-1][x*3 + 1], raster[height-y-1][x*3]); // this magic because of invert order in bmp raster
}

QImage Bmp_image24::get_qImage() const {
    QImage image(width, height, QImage::Format_RGB888); // this format for 24-bitcount (8,8,8)
    for (int i = 0; i != height; ++i) {
        for (int j = width-1; j >= 0; --j) {
            image.setPixelColor(j, i, this->get_color(j, i));
        }
    }

    return image;
}

//-///////////////////////////////////////////////////////////

void Bmp_image24::invert_color() {
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != (width*3) + ALIGNMENT24(width); ++j) {
            raster[i][j] = 255 - raster[i][j];
        }
    }
}

void Bmp_image24::grayscale() {
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j < (width*3) + ALIGNMENT24(width) - 3; j+=3) {
            uint8_t luma = 0.2126*raster[i][j] + 0.7152*raster[i][j+1] + 0.0722*raster[i][j+2]; // https://habrahabr.ru/post/304210/﻿
            raster[i][j] = luma;
            raster[i][j+1] = luma;
            raster[i][j+2] = luma;
        }
    }
}

void Bmp_image24::invert_color(int x1, int y1, int x2, int y2) {
    // find upper left and lower right corners coordinates
    // in case of out of image
    if (x1 < 0) x1 = 0;
    if (y1 < 0) y1 = 0;
    if (x2 < 0) x2 = 0;
    if (y2 < 0) y2 = 0;

    int x_min = std::min(std::min(x1, x2), width);
    int y_min = std::min(std::min(y1, y2), height);
    int x_max = std::min(std::max(x1, x2), width);  // in case of std::max() out of image
    int y_max = std::min(std::max(y1, y2), height);

    for (int y = y_min; y != y_max; ++y) {
        for (int x = x_min; x != x_max; ++x) {
            this->set_color(x, y, QColor(255 - raster[height-y-1][x*3+2], // this magic because of invert order in bmp raster
                                         255 - raster[height-y-1][x*3+1],
                                         255 - raster[height-y-1][x*3]));
        }
    }
}

void Bmp_image24::grayscale(int x1, int y1, int x2, int y2) {
    // find upper left and lower right corners coordinates
    // in case of out of image
    if (x1 < 0) x1 = 0;
    if (y1 < 0) y1 = 0;
    if (x2 < 0) x2 = 0;
    if (y2 < 0) y2 = 0;

    int x_min = std::min(std::min(x1, x2), width);
    int y_min = std::min(std::min(y1, y2), height);
    int x_max = std::min(std::max(x1, x2), width);
    int y_max = std::min(std::max(y1, y2), height);

    for (int y = y_min; y != y_max; ++y) {
        for (int x = x_min; x != x_max; ++x) {
            QColor rgb = get_color(x, y);
            uint8_t luma = 0.2126*rgb.red() + 0.7152*rgb.green() + 0.0722*rgb.blue(); // https://habrahabr.ru/post/304210/﻿
            set_color(x, y, QColor(luma, luma, luma));
        }
    }
}

void Bmp_image24::crop(int vertical_crop, int horizontal_crop, Bmp::Resize_direction direction) {
    if (vertical_crop < 0 || horizontal_crop < 0) {
        throw Bmp::Bad_resize{vertical_crop, horizontal_crop};
    }

    height -= vertical_crop;
    width -= horizontal_crop;
    size = height * (width*3 + ALIGNMENT24(width));

    uint8_t** cropped_raster = new uint8_t*[height];
    cropped_raster[0] = new uint8_t[size]{};
    for (int i = 1; i != height; ++i) {
        cropped_raster[i] = cropped_raster[i-1] + ((width*3) + ALIGNMENT24(width));
    }

    switch (direction) {
        case Bmp::Resize_direction::center:
            vertical_crop /= 2;
            horizontal_crop /= 2;
            for (int i = 0; i != height; ++i) {
                for (int j = 0; j != width*3 + ALIGNMENT24(width); ++j) {
                    cropped_raster[i][j] = raster[i+vertical_crop][j+horizontal_crop * 3];
                }
            } break;

        case Bmp::Resize_direction::upper_left:
            for (int i = 0; i != height; ++i) {
                for (int j = 0; j != width*3 + ALIGNMENT24(width); ++j) {
                    cropped_raster[i][j] = raster[i][j+horizontal_crop*3];
                }
            } break;

        case Bmp::Resize_direction::upper_right:
            for (int i = 0; i != height; ++i) {
                for (int j = 0; j != width*3 + ALIGNMENT24(width); ++j) {
                    cropped_raster[i][j] = raster[i][j];
                }
            } break;

        case Bmp::Resize_direction::lower_right:
            for (int i = 0; i != height; ++i) {
                for (int j = 0; j != width*3 + ALIGNMENT24(width); ++j) {
                    cropped_raster[i][j] = raster[i+vertical_crop][j];
                }
            } break;

        case Bmp::Resize_direction::lower_left:
            for (int i = 0; i != height; ++i) {
                for (int j = 0; j != width*3 + ALIGNMENT24(width); ++j) {
                    cropped_raster[i][j] = raster[i+vertical_crop][j+horizontal_crop*3];
                }
            } break;
    }

    delete [] raster[0];
    delete [] raster;

    raster = cropped_raster;
    raster[0] = cropped_raster[0];
}

void Bmp_image24::expanse(int vertical_exp, int horizontal_exp, Bmp::Resize_direction direction, QColor color) {
    if (vertical_exp < 0 || horizontal_exp < 0) {
        throw Bmp::Bad_resize{vertical_exp, horizontal_exp};
    }

    int old_width = width;
    int old_height = height;

    height += vertical_exp;
    width += horizontal_exp;
    size = height * (width*3 + ALIGNMENT24(width));

    uint8_t** expansed_raster = new uint8_t*[height];
    expansed_raster[0] = new uint8_t[size]{};
    for (int i = 1; i != height; ++i) {
        expansed_raster[i] = expansed_raster[i-1] + ((width*3) + ALIGNMENT24(width));
    }

    switch(direction) {
        case Bmp::Resize_direction::center:
            vertical_exp /= 2;
            horizontal_exp /= 2;
            for (int i = 0; i != vertical_exp; ++i) {
               for (int j = 0; j < (width*3) - 2; j += 3) {
                   expansed_raster[i][j] = color.blue();
                   expansed_raster[i][j+1] = color.green();
                   expansed_raster[i][j+2] = color.red();
                }
            }


            for (int i = vertical_exp; i != old_height + vertical_exp; ++i) {
                for (int j = 0; j < horizontal_exp*3 - 2; j += 3) {
                    expansed_raster[i][j] = color.blue();
                    expansed_raster[i][j+1] = color.green();
                    expansed_raster[i][j+2] = color.red();
                }

                for (int j = horizontal_exp*3; j != old_width*3 + horizontal_exp*3; ++j) {
                    expansed_raster[i][j] = raster[i-vertical_exp][j-horizontal_exp*3];
                }

                for (int j = old_width*3 + horizontal_exp*3; j < width*3 - 2; j += 3) {
                    expansed_raster[i][j] = color.blue();
                    expansed_raster[i][j+1] = color.green();
                    expansed_raster[i][j+2] = color.red();
                }
            }

            for (int i = old_height + vertical_exp; i != height; ++i) {
                for (int j = 0; j < (width*3) - 2; j += 3) {
                    expansed_raster[i][j] = color.blue();
                    expansed_raster[i][j+1] = color.green();
                    expansed_raster[i][j+2] = color.red();
                }
            } break;

        case Bmp::Resize_direction::upper_left:
            for (int i = 0; i != old_height; ++i) {
                for (int j = 0; j < horizontal_exp*3 - 2; j += 3) {
                    expansed_raster[i][j] = color.blue();
                    expansed_raster[i][j+1] = color.green();
                    expansed_raster[i][j+2] = color.red();
                }

                for (int j = horizontal_exp*3; j != (width*3) + ALIGNMENT24(width); ++j) {
                    expansed_raster[i][j] = raster[i][j-horizontal_exp*3]; // TODO some COLOR instead 0
                }
            }
            for (int i = old_height; i != height; ++i) {
                for (int j = 0; j < width*3 - 2; j += 3) {
                    expansed_raster[i][j] = color.blue();
                    expansed_raster[i][j+1] = color.green();
                    expansed_raster[i][j+2] = color.red();
                }
            } break;

        case Bmp::Resize_direction::upper_right:
            for (int i = 0; i != old_height; ++i) {
                for (int j = 0; j != (old_width)*3; ++j) {
                    expansed_raster[i][j] = raster[i][j];
                }

                for (int j = old_width*3; j < width*3 - 2; j += 3) {
                    expansed_raster[i][j] = color.blue();
                    expansed_raster[i][j+1] = color.green();
                    expansed_raster[i][j+2] = color.red();
                }
            }

            for (int i = old_height; i != height; ++i) {
                for (int j = 0; j < width*3 - 2; j += 3) {
                    expansed_raster[i][j] = color.blue();
                    expansed_raster[i][j+1] = color.green();
                    expansed_raster[i][j+2] = color.red();
                }
            } break;

        case Bmp::Resize_direction::lower_right:
            for (int i = 0; i != height - old_height; ++i) {
                for (int j = 0; j < width*3 - 2; j += 3) {
                    expansed_raster[i][j] = color.blue();
                    expansed_raster[i][j+1] = color.green();
                    expansed_raster[i][j+2] = color.red();
                }
            }

            for (int i = height - old_height; i != height; ++i) {
                for (int j = 0; j != old_width*3; ++j) {
                    expansed_raster[i][j] = raster[i-vertical_exp][j];
                }

                for (int j = old_width*3; j < width*3 - 2; j += 3) {
                    expansed_raster[i][j] = color.blue();
                    expansed_raster[i][j+1] = color.green();
                    expansed_raster[i][j+2] = color.red();
                }
            } break;

        case Bmp::Resize_direction::lower_left:
            for (int i = 0; i != height - old_height; ++i) {
                for (int j = 0; j < (width*3) - 2; j += 3) {
                    expansed_raster[i][j] = color.blue();
                    expansed_raster[i][j+1] = color.green();
                    expansed_raster[i][j+2] = color.red();
                }
            }

            for (int i = height - old_height; i != height; ++i) {
                for (int j = 0; j < horizontal_exp*3 - 2; j += 3) {
                    expansed_raster[i][j] = color.blue();
                    expansed_raster[i][j+1] = color.green();
                    expansed_raster[i][j+2] = color.red();
                }

                for (int j = horizontal_exp*3; j != (width*3) + ALIGNMENT24(width); ++j) {
                    expansed_raster[i][j] = raster[i-vertical_exp][j - horizontal_exp*3];
                }
            } break;
    }

    delete [] raster[0];
    delete [] raster;

    raster = expansed_raster;
    raster[0] = expansed_raster[0];
}
