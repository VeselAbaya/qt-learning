#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bmp.h"
#include "save_dialog.h"
#include "my_graphics_scene.h"
#include "crop_dialog.h"
#include "expanse_dialog.h"
#include "help_dialog.h"

#include <QMainWindow>
#include <QSettings>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QPixmap>
#include <QImage>
#include <QString>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QInputDialog>

#include <algorithm>

namespace Ui { class MainWindow; }

/*! \class MainWindow
 * \brief Class for work with desktop user interface
 */
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
    void crop_image(int vertical_crop, int horizontal_crop, Bmp::Resize_direction crop_direction);
    void expanse_image(int vertical_exp, int horizontal_exp, Bmp::Resize_direction expanse_direction, QColor color);
    void save_as(QWidget* parent=nullptr);

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
    void on_actionExpanse_triggered();
    void on_actionImage_info_triggered();
    void on_actionHelp_triggered();

private:
    Ui::MainWindow* ui;
    My_graphics_scene* scene; /*!< Scene with opened image */
    Bmp_image* bmp_image;     /*!< Pointer on image */

    QString open_file_path;   /*!< Opened image file path */
    QString prev_file_path;   /*!< Pevious image file path */
    // flags
    bool grayscale_clicked;   /*!< Grayscale tool choosen */
    bool invert_clicked;      /*!< Invert colot tool choosen */
    bool cancel_clicked;      /*!< Cancel button in save dialog clicked */
    bool changed;             /*!< Image has been changed */
};

#endif // MAINWINDOW_H
