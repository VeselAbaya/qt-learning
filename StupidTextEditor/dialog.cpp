#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent): QDialog(parent),
                                 ui(new Ui::Dialog) {
    ui->setupUi(this);
    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(okClicked()));
    connect(ui->closeButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void Dialog::okClicked() {
    emit filePath(ui->lineEdit->text());
    close();
}

Dialog::~Dialog() {
    delete ui;
}
