#ifndef CROP_DIALOG_H
#define CROP_DIALOG_H

#include "resize_direction.h"

#include <QDialog>
#include <QSettings>

namespace Ui {
    class Crop_dialog;
}

/*! \class Crop_dialog
 * \brief Class for implementation of image crop
 */
class Crop_dialog: public QDialog {
    Q_OBJECT

public:
    /*! Constructor
     * \param max_width Width of cropping image
     * \param max_height Height of cropping image
     */
    explicit Crop_dialog(int max_width, int max_height, QWidget *parent = 0);
    ~Crop_dialog();

signals:
    /*! Ok button emitting signal
     * \param vertical_crop Vertiacal crop size in pixels
     * \param horizontal_crop Horizontal crop size in pixels
     * \param direction Crop direction
     */
    void ok_button_clicked(int vertical_crop, int horizontal_crop, Bmp::Resize_direction direction);

private slots:
    /*! Method to write position, values of vertical and horizontal crop size and crop direction */
    void write_settings();
    /*! Method to read and set position, values of vertical and horizontal crop size and crop direction */
    void read_settings();

    /*! Slot to handle cancel button clicked event */
    void on_cancel_button_clicked();
    /*! Slot to handle ok button clicked event */
    void on_ok_button_clicked();

private:
    Ui::Crop_dialog *ui;
};

#endif // CROP_DIALOG_H
