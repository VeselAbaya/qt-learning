#include "help_dialog.h"
#include "ui_help_dialog.h"

Help_dialog::Help_dialog(QWidget *parent): QDialog(parent),
                                           ui(new Ui::Help_dialog) {
    ui->setupUi(this);
    setWindowTitle("Help");
    ui->grayscale_text->setText("To invert some area choose \"Grayscale\" tool and clicked once on start point, then just "
                                "released it on finish\n\n"
                                "To grayscale whole image - Image -> Grayscale (ctrl+G)");
    ui->invert_text->setText("To invert some area choose \"Invert color\" tool and clicked once on start point, then just "
                             "released it on finish\n\n"
                             "To invert whole image - Image -> Invert color (ctrl+I)");
    ui->crop_text->setText("To crop image choose \"Crop\" tool.\n"
                           "In opened dialog choose direction of crop and vertical and horizontal size (in pixels)");
    ui->expanse_text->setText("To expanse image choose \"Expanse\" tool.\n"
                           "In opened dialog choose direction of expansion, backgorund-fill color, vertical and horizontal size (in pixels)");
}

Help_dialog::~Help_dialog() {
    delete ui;
}
