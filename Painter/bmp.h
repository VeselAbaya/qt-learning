#ifndef BMP_H
#define BMP_H

#include "bmp_image24.h"
#include <QMessageBox>
#include <QErrorMessage>

/*! \def BI_SIZE
 * BitMapInfo struct size */
#define BI_SIZE 40

/*! \namespace Bmp
 * \brief Namespace for functions to work with bmp */
namespace Bmp {
    /*! \fn Bmp_image* bmp(std::string file_path)
     *  \brief To open a bmp file
     *  \details this is "constuctor" for all bitcounts
     * Open 24-bitcount bmp file (other bitcounts doesn't support yet)
     *  \return Pointer on base class of Bmp_iamge24: Bmp_image
     * nullptr if bitcount isn't standart
     *  \param file_path path to bmp file */
    Bmp_image* bmp(std::string file_path); // open bmp-file

    /*! \fn Bmp_image* copy(Bmp_image* image)
     *  \brief To copy a bmp file
     * "copy constructor" for all bitcounts
     *  \details Copy 24-bitcount bmp file (other bitcounts doesn't support yet)
     *  \return Pointer on base class of Bmp_iamge24: Bmp_image
     *  \param image Pointer on copying image */
    Bmp_image* copy(Bmp_image* image);

    /*! \fn Bmp_image* create(int width, int height)
     *  \brief To create new bmp image
     *  \details create new white 24-bitcount bmp image (other bitcounts doesn't support yet)
     *  \return Pointer on base class of Bmp_iamge24: Bmp_image
     *  \param width New image width
     *  \param height New image height */
    Bmp_image* create(int width, int height);

    /*! \fn void save(Bmp_image* image, std::string file_path="")
     *  \brief To save bmp file
     *  \param image Pointer on image
     *  \param file_path Path to save the image */
    void save(Bmp_image* image, std::string file_path="");
}

#endif // BMP_H
