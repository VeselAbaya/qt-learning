#include "help_dialog.h"
#include "ui_help_dialog.h"

Help_dialog::Help_dialog(QWidget *parent): QDialog(parent),
                                           ui(new Ui::Help_dialog) {
    ui->setupUi(this);
    setWindowTitle("Help");
}

Help_dialog::~Help_dialog() {
    delete ui;
}
