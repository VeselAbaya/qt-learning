#include "crop_dialog.h"
#include "ui_crop_dialog.h"

Crop_dialog::Crop_dialog(int max_width, int max_height, QWidget *parent): QDialog(parent),
                                           ui(new Ui::Crop_dialog) {
    ui->setupUi(this);
    ui->vertical_crop->setMaximum(max_height-1);
    ui->horizontal_crop->setMaximum(max_width-1);
    setWindowTitle("Crop");

    read_settings();
}

Crop_dialog::~Crop_dialog() {
    delete ui;
}


void Crop_dialog::on_cancel_button_clicked() {
    write_settings();
    close();
}



void Crop_dialog::on_ok_button_clicked() {
    Bmp::Resize_direction crop_direction;
    switch(ui->crop_direction->currentIndex()) {
        case 0: crop_direction = Bmp::Resize_direction::center; break;
        case 1: crop_direction = Bmp::Resize_direction::upper_left; break;
        case 2: crop_direction = Bmp::Resize_direction::upper_right; break;
        case 3: crop_direction = Bmp::Resize_direction::lower_right; break;
        case 4: crop_direction = Bmp::Resize_direction::lower_left; break;
    }

    emit ok_button_clicked(ui->vertical_crop->value(),
                           ui->horizontal_crop->value(),
                           crop_direction);

    write_settings();
    close();
}

void Crop_dialog::write_settings() {
    QSettings settings("My Soft", "LULpainter");

    settings.beginGroup("Crop dialog");
    settings.setValue("vertical_crop", ui->vertical_crop->value());
    settings.setValue("horizontal_crop", ui->horizontal_crop->value());
    settings.setValue("crop_direction", ui->crop_direction->currentIndex());
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

void Crop_dialog::read_settings() {
    QSettings settings("My Soft", "LULpainter");

    settings.beginGroup("Crop dialog");
    ui->vertical_crop->setValue(settings.value("vertical_crop", 0).toInt());
    ui->horizontal_crop->setValue(settings.value("horizontal_crop", 0).toInt());
    ui->crop_direction->setCurrentIndex(settings.value("crop_direction", 0).toInt());
    resize(settings.value("size", QSize(403, 211)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}
