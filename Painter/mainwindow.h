#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QPixmap>
#include <QImage>
#include <QString>
#include "bmp_image.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_invert_button_clicked(bool checked);

    void on_invert_button_clicked();

    void on_grayscale_button_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    Bmp_image* bmp_image;
};

#endif // MAINWINDOW_H
