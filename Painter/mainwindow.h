#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bmp.h"
#include "save_quit_dialog.h"

#include <QMainWindow>
#include <QSettings>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QPixmap>
#include <QImage>
#include <QString>
#include <QCloseEvent>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void read_settings();  // read config (size and position of window, path to last opened image)
    void write_settings(); // write this config
    void closeEvent(QCloseEvent* event);
    bool cancel_toggle();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actioncoordinates_gray_triggered();

    void on_actioncoordinates_invert_triggered();

    void on_actionGraysacle_triggered();

    void on_actionInvert_triggered();

    void on_actionQuit_triggered();

    void on_actionNew_triggered();

private:
    Ui::MainWindow* ui;
    QGraphicsScene* scene;
    Bmp_image* bmp_image;
    QString open_file_path;

    bool cancel_clicked;
};

#endif // MAINWINDOW_H
