#include "save_dialog.h"
#include "ui_save_dialog.h"

Save_dialog::Save_dialog(QWidget *parent): QDialog(parent),
                                           ui(new Ui::save_quit_dialog) {
    ui->setupUi(this);
    this->setModal(true);
}

Save_dialog::~Save_dialog() {
    delete ui;
}

void Save_dialog::on_save_button_clicked() {
    emit save_button_clicked();
    done(0);
}

void Save_dialog::on_cancel_button_clicked() {
    emit cancel_button_clicked(true);
    done(0);
}

void Save_dialog::on_no_button_clicked() {
    done(0);
}

void Save_dialog::closeEvent(QCloseEvent *event) {
    emit cancel_button_clicked(true);
    event->accept();
}
