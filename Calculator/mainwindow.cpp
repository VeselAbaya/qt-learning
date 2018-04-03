#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
                                         ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_plus, SIGNAL(clicked(bool)), this, SLOT(operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked(bool)), this, SLOT(operations()));
    connect(ui->pushButton_mod, SIGNAL(clicked(bool)), this, SLOT(operations()));
    connect(ui->pushButton_div, SIGNAL(clicked(bool)), this, SLOT(operations()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::digits_numbers() {
    QPushButton* button = (QPushButton*)sender();

    ui->label_result->setText(ui->label_result->text() + button->text());
}

void MainWindow::operations() {

}

void MainWindow::on_pushButton_dot_clicked() {
    if (!ui->label_result->text().contains('.')) {
        ui->label_result->setText(ui->label_result->text() + '.');
    }
}

void MainWindow::on_pushButton_sign_clicked() {
    ui->label_result->setText(QString::number((ui->label_result->text().toDouble() * (-1)), 'g', 30));
}

void MainWindow::on_pushButton_AC_clicked() {
    ui->label_result->setText("");
}
