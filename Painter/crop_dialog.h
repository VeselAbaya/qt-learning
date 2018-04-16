#ifndef CROP_DIALOG_H
#define CROP_DIALOG_H

#include "crop_direction.h"

#include <QDialog>
#include <QSettings>

namespace Ui {
    class Crop_dialog;
}

class Crop_dialog: public QDialog {
    Q_OBJECT

public:
    explicit Crop_dialog(int max_widht, int max_height, QWidget *parent = 0);
    ~Crop_dialog();

signals:
    void ok_button_clicked(int vertical_crop, int horizontal_crop, Bmp::Crop_direction direction);

private slots:
    void write_settings();
    void read_settings();

    void on_cancel_button_clicked();
    void on_ok_button_clicked();

private:
    Ui::Crop_dialog *ui;
};

#endif // CROP_DIALOG_H
