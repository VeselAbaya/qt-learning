#ifndef BMP_EXCEPTIONS_H
#define BMP_EXCEPTIONS_H

#include <exception>

namespace Bmp {
    /*! \exception Bad_bicount
     * \brief Exception
     * \details Exception throws in case of incorrect or unsupported bitcount */
    class Bad_bitcount: public std::exception {
    public:
        Bad_bitcount(int bitcount);
        const char* what() const throw();
        int err_bitcount() const;

    private:
        int bitcount;
    };

    /*! \exception Bad_size
     * \brief Exception
     * \details Exception throws in case of negative width or height */
    class Bad_size: public std::exception {
    public:
        Bad_size(int width, int height);
        const char* what() const throw();
        /*! Method to get width
         * \return incorrect width */
        int err_width() const;
        /*! Method to get height
         * \return incorrect height */
        int err_height() const;

    private:
        int width;  /*!< Creating image's width */
        int height; /*!< Creating image's height */
    };

    class Bad_resize: public std::exception {
    public:
        Bad_resize(int vertical, int horizontal);
        const char* what() const throw();
        /*! Method to get vertical resize
         * \return incorrect vertical resize */
        int err_vertical() const;
        /*! Method to get horizontal resize
         * \return incorrect horizontal resize */
        int err_horizontal() const;

    private:
        int vertical;   /*!< vertical resize */
        int horizontal; /*!< horizontal resize */
    };
}

#endif // BMP_EXCEPTIONS_H
