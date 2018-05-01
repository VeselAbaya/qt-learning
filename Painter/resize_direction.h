#ifndef RESIZE_DIRECTION_H
#define RESIZE_DIRECTION_H

namespace Bmp {
    /*! \enum Resize_direction
     * \brief This is enumerate of constants to crop and expanse functions */
    enum class Resize_direction {center,      /*!< Center direction */
                                 upper_left,  /*!< Upper left corner direction */
                                 upper_right, /*!< Upper right corner direction */
                                 lower_right, /*!< Lower right corner direction */
                                 lower_left   /*!< Lower left corner direction */
                                };
}

#endif // RESIZE_DIRECTION_H
