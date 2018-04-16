#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bmp.h"
#include "save_dialog.h"
#include "my_graphics_scene.h"
#include "crop_dialog.h"

#include <QMainWindow>
#include <QSettings>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QPixmap>
#include <QImage>
#include <QString>
#include <QCloseEvent>

namespace Ui { class MainWindow; }

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void read_settings();  // read config (size and position of window, path to last opened image)
    void write_settings(); // write this config
    void closeEvent(QCloseEvent* event);
    bool cancel_toggle();
    void grayscale_toggle();
    void invert_toggle();
    void mouseReleased();
    void crop_image(int vertical_crop, int horizontal_crop, Bmp::Crop_direction crop_direction);

    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actioncoordinates_gray_triggered();
    void on_actioncoordinates_invert_triggered();
    void on_actionGraysacle_triggered();
    void on_actionInvert_triggered();
    void on_actionQuit_triggered();
    void on_actionNew_triggered();
    void on_actionCrop_3_triggered();

private:
    Ui::MainWindow* ui;
    My_graphics_scene* scene;
    Bmp_image* bmp_image;
    QString open_file_path;

    // flags
    bool grayscale_clicked;
    bool invert_clicked;
    bool cancel_clicked;
    bool changed;
};

#endif // MAINWINDOW_H
