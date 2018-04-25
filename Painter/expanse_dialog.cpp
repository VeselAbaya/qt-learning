#include "expanse_dialog.h"
#include "ui_expanse_dialog.h"

Expanse_dialog::Expanse_dialog(QWidget *parent): QDialog(parent),
                                                 ui(new Ui::Expanse_dialog) {
    ui->setupUi(this);
    setWindowTitle("Expanse");

    read_settings();
    set_background_color(color);
}

Expanse_dialog::~Expanse_dialog() {
    delete ui;
}

void Expanse_dialog::on_cancel_button_clicked() {
    write_settings();
    close();
}

void Expanse_dialog::on_ok_button_clicked() {
    Bmp::Resize_direction expanse_direction;
    switch(ui->crop_direction->currentIndex()) {
        case 0: expanse_direction = Bmp::Resize_direction::center; break;
        case 1: expanse_direction = Bmp::Resize_direction::upper_left; break;
        case 2: expanse_direction = Bmp::Resize_direction::upper_right; break;
        case 3: expanse_direction = Bmp::Resize_direction::lower_right; break;
        case 4: expanse_direction = Bmp::Resize_direction::lower_left; break;
    }

    emit ok_button_clicked(ui->vertical_crop->value(),
                           ui->horizontal_crop->value(),
                           expanse_direction, color);

    write_settings();
    close();
}

void Expanse_dialog::write_settings() {
    QSettings settings("My Soft", "LULpainter");

    settings.beginGroup("Expanse dialog");
    settings.setValue("red", color.red());
    settings.setValue("green", color.green());
    settings.setValue("blue", color.blue());
    settings.setValue("vertical_crop", ui->vertical_crop->value());
    settings.setValue("horizontal_crop", ui->horizontal_crop->value());
    settings.setValue("expanse_direction", ui->crop_direction->currentIndex());
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

void Expanse_dialog::read_settings() {
    QSettings settings("My Soft", "LULpainter");

    settings.beginGroup("Expanse dialog");
    color.setRgb(qRgb(settings.value("red", 0).toInt(),
                      settings.value("green", 0).toInt(),
                      settings.value("blue", 0).toInt()));
    ui->vertical_crop->setValue(settings.value("vertical_crop", 0).toInt());
    ui->horizontal_crop->setValue(settings.value("horizontal_crop", 0).toInt());
    ui->crop_direction->setCurrentIndex(settings.value("expanse_direction", 0).toInt());
    resize(settings.value("size", QSize(403, 211)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}

void Expanse_dialog::on_color_button_clicked() {
    color = QColorDialog::getColor();
    set_background_color(color);
}

void Expanse_dialog::set_background_color(QColor color) {
    ui->color_button->setStyleSheet(QString("background: rgb(") + QString::number(color.red()) + QString(", ")
                                                                + QString::number(color.green()) + QString(", ")
                                                                + QString::number(color.blue()) + QString(");"));
}
