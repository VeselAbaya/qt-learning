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

class Expanse_dialog: public QDialog {
    Q_OBJECT

public:
    explicit Expanse_dialog(int max_width, int max_height, QWidget *parent = 0);
    ~Expanse_dialog();

signals:
    void ok_button_clicked(int vertical_crop, int horizontal_crop, Bmp::Resize_direction direction, QColor color);

private slots:
    void write_settings();
    void read_settings();
    void set_background_color(QColor color);

    void on_cancel_button_clicked();
    void on_ok_button_clicked();

    void on_color_button_clicked();

private:
    Ui::Expanse_dialog *ui;
    QColor color;
};

#endif // EXPANSE_DIALOG_H
