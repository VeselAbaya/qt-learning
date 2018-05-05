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
        /*! Method to get bicount
         * \return Incorrect bitcount */
        int err_bitcount() const;

    private:
        int bitcount;
    };

    /*! \exception Bad_size
     * \brief Exception
     * \details Exception throws in case of negative width or height
     * \remark Of course one of width or height can be positive */
    class Bad_size: public std::exception {
    public:
        Bad_size(int width, int height);
        const char* what() const throw();
        /*! Method to get width
         * \return Incorrect width */
        int err_width() const;
        /*! Method to get height
         * \return Incorrect height */
        int err_height() const;

    private:
        int width;  /*!< Creating image's width */
        int height; /*!< Creating image's height */
    };

    /*! \exception Bad_resize
     * \brief Exception
     * \details Exception throws in case of negative vertical_[exp, crop] or horzintal_[exp, crop]
     * \remark Of course one of vertical or horizontal can be positive */
    class Bad_resize: public std::exception {
    public:
        Bad_resize(int vertical, int horizontal);
        const char* what() const throw();
        /*! Method to get vertical resize
         * \return Incorrect vertical resize */
        int err_vertical() const;
        /*! Method to get horizontal resize
         * \return Incorrect horizontal resize */
        int err_horizontal() const;

    private:
        int vertical;   /*!< vertical resize */
        int horizontal; /*!< horizontal resize */
    };
}

#endif // BMP_EXCEPTIONS_H
