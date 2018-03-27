#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
                                         ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->graphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphics_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene();
    bmp_image = nullptr;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOpen_triggered() {
    QString file_path = QFileDialog::getOpenFileName(this, "Open a file");
    if (!file_path.isEmpty()) {
        if (bmp_image) {
            scene->clear();
            delete bmp_image;
        }

        bmp_image = new Bmp_image(file_path.toStdString());
        ui->size->setText(QString::number(bmp_image->get_size()));
        ui->height->setText(QString::number(bmp_image->get_height()));
        ui->width->setText(QString::number(bmp_image->get_width()));
        ui->bitcount->setText(QString::number(bmp_image->get_bitcount()));

        QImage image = bmp_image->get_qImage();
        scene->addPixmap(QPixmap::fromImage(image));

        ui->graphics_view->resize(bmp_image->get_width(), bmp_image->get_height());
        ui->graphics_view->setScene(scene);
    }
}



void MainWindow::on_invert_button_clicked() {
    bmp_image->invert_color();
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(bmp_image->get_qImage()));
    ui->graphics_view->setScene(scene);
}



void MainWindow::on_grayscale_button_clicked() {
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(bmp_image->grayscale().get_qImage()));
    ui->graphics_view->setScene(scene);
}
