#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
                                         ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOpen_triggered() {
    QString file_path = QFileDialog::getOpenFileName(this, "Open a file");
    if (!file_path.isEmpty()) {
        bmp_image = new Bmp_image(file_path.toStdString());
        ui->size->setText(QString::number(bmp_image->get_size()));
        ui->height->setText(QString::number(bmp_image->get_height()));
        ui->width->setText(QString::number(bmp_image->get_width()));
        ui->bitcount->setText(QString::number(bmp_image->get_bitcount()));

        int image_height = bmp_image->get_height();
        int image_width = bmp_image->get_width();
        QImage image(image_width, image_height, QImage::Format_RGB888);
        for (int i = 0; i != image_height; ++i) {
            for (int j = image_width-1; j >= 0; --j) {
                image.setPixelColor(j, i, QColor(bmp_image->get_rgb(i, j)));
            }
        }

        QGraphicsScene* scene = new QGraphicsScene();
        scene->addPixmap(QPixmap::fromImage(image));
        ui->graphics_view->setScene(scene);
    }
}
