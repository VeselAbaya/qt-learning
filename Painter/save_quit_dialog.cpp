#include "save_quit_dialog.h"
#include "ui_save_quit_dialog.h"

Save_quit_dialog::Save_quit_dialog(QWidget *parent): QDialog(parent),
                                                     ui(new Ui::Save_quit_dialog) {
    ui->setupUi(this);
}

Save_quit_dialog::~Save_quit_dialog() {
    delete ui;
}

void Save_quit_dialog::on_save_button_clicked() {
    emit save_button_clicked();
    done(0);
}

void Save_quit_dialog::on_cancel_button_clicked() {
    emit cancel_button_clicked(true);
    done(0);
}

void Save_quit_dialog::on_no_button_clicked() {
    done(0);
}

void Save_quit_dialog::closeEvent(QCloseEvent *event) {
    emit cancel_button_clicked(true);
    event->accept();
}
