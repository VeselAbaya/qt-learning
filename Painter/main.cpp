#include "mainwindow.h"
#include <QApplication>

/*! \mainpage This is LULPainter
 * \section Functionality
 * \subsection Grayscale
 * To invert some area choose Grayscale tool and clicked once on start point, then just released it on finish.
 * To grayscale whole image - Image -> Grayscale (ctrl+G)
 *
 * \subsection Invert color
 * To invert some area choose Invert color tool and clicked once on start point, then just released it on finish.
 * To invert whole image - Image -> Invert colot (ctrl+I)
 *
 * \subsection Crop
 * To crop image choose Crop tool.
 * In opened dialog choose direction of crop and vertical and horizontal size (in pixels)
 *
 * \subsection Expanse
 * To expanse image choose Expanse tool.
 * In opened dialog choose direction of expansion, backgorund-fill color, vertical and horizontal size (in pixels)
 */

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow main_window;
    main_window.show();

    return app.exec();
}
