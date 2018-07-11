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
    connect(ui->pushButton_mul, SIGNAL(clicked(bool)), this, SLOT(operations()));


    connect(ui->pushButton_eq, SIGNAL(clicked(bool)), this, SLOT(equals()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::digits_numbers() {
    QPushButton* button = static_cast<QPushButton*>(sender());
    if (ui->label_result->text() != "0")
        ui->label_result->setText(ui->label_result->text() + button->text());
    else
        ui->label_result->setText(button->text());
}

void MainWindow::operations() {
    QPushButton* button = static_cast<QPushButton*>(sender());
    left = ui->label_result->text().toDouble();
    if (left) {
        op = button->text().toStdString()[0];
        if (op == '%' && ceil(left) != floor(left)) {
            QErrorMessage msg;
            msg.showMessage("Operands must be integral");
            msg.exec();
        } else {
            ui->label_result->setText("");
        }

    }
}

void MainWindow::equals() {
    if (left) {
        double right = ui->label_result->text().toDouble();
        switch(op) {
            case '+': ui->label_result->setText(QString::number(left + right)); break;
            case '-': ui->label_result->setText(QString::number(left - right)); break;
            case 'x': ui->label_result->setText(QString::number(left * right)); break;
            case '/': ui->label_result->setText(QString::number(left / right)); break;
            case '%':
                if (ceil(right) == floor(right)) {
                    ui->label_result->setText(QString::number(
                        static_cast<int>(left) % static_cast<int>(right) + static_cast<int>(right)
                    ));
                } else {
                    QErrorMessage msg;
                    msg.showMessage("Operands must be integral");
                    msg.exec();
                }
            break;
        }
    }
}



void MainWindow::on_pushButton_dot_clicked() {
    if (!ui->label_result->text().contains('.')) {
        ui->label_result->setText(ui->label_result->text() + '.');
    }
}

void MainWindow::on_pushButton_sign_clicked() {
    ui->label_result->setText(QString::number(ui->label_result->text().toDouble() * (-1)));
}

void MainWindow::on_pushButton_AC_clicked() {
    ui->label_result->setText("");
}
