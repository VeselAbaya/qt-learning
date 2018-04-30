#ifndef EXPANSE_DIALOG_H
#define EXPANSE_DIALOG_H

#include "resize_direction.h"

#include <QDialog>
#include <QColorDialog>
#include <QSettings>
#include <QColor>

namespace Ui {
    class Expanse_dialog;
}

/*! \class Expanse_dialog
 * \brief Class for implementation of image expanse
 */
class Expanse_dialog: public QDialog {
    Q_OBJECT

public:
    explicit Expanse_dialog(QWidget *parent = 0);
    ~Expanse_dialog();

signals:
    /*! Ok button emitting signal
     * \param vertical_crop Vertiacal crop size in pixels
     * \param horizontal_crop Horizontal crop size in pixels
     * \param direction Crop direction
     * \param color Fill color
     */
    void ok_button_clicked(int vertical_crop, int horizontal_crop, Bmp::Resize_direction direction, QColor color);

private slots:
    /*! Method to write position, values of vertical and horizontal crop size and crop direction */
    void write_settings();
    /*! Method to read and set position, values of vertical and horizontal crop size and crop direction */
    void read_settings();
    /*! Method to set color of color choose button */
    void set_background_color(QColor color);

    /*! Slot to handle cancel button clicked event */
    void on_cancel_button_clicked();
    /*! Slot to handle ok button clicked event */
    void on_ok_button_clicked();

    /*! Slot to handle color choose button clicked event */
    void on_color_button_clicked();

private:
    Ui::Expanse_dialog *ui;
    QColor color; /*!< Fill color */
};

#endif // EXPANSE_DIALOG_H
