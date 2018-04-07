#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
                                         ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->graphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphics_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCentralWidget(ui->graphics_view);

    scene = new My_graphics_scene();
    connect(scene, SIGNAL(mouseReleased()), this, SLOT(mouseReleased()));

    bmp_image = nullptr;
    grayscale_clicked = false;
    invert_clicked = false;
    cancel_clicked = false;


    read_settings();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mouseReleased() {
    int x1 = scene->get_first().x();
    int y1 = scene->get_first().y();
    int y2 = scene->get_last().y();
    int x2 = scene->get_last().x();

    if (grayscale_clicked) {
        bmp_image->grayscale(x1, y1, x2, y2);
    } else if (invert_clicked) {
        bmp_image->invert_color(x1, y1, x2, y2);
    }

    scene->clear();
    scene->addPixmap(QPixmap::fromImage(bmp_image->get_qImage()));
    ui->graphics_view->setScene(scene);
}

void MainWindow::on_actionOpen_triggered() {
    open_file_path = QFileDialog::getOpenFileName(this, "Open a file");
    if (!open_file_path.isEmpty()) {
        if (bmp_image) { // need to delete prev image from scene before uploading next
            scene->clear();

            // some crutch to align center new image :(
            delete scene; //                         :(
            scene = new My_graphics_scene; //        :(
            // some crutch to align center new image :(

            delete bmp_image;
        }

        bmp_image = Bmp::bmp(open_file_path.toStdString());

        scene->addPixmap(QPixmap::fromImage(bmp_image->get_qImage()));
        ui->graphics_view->setScene(scene);
    }
}

void MainWindow::on_actionSave_triggered() {
    Bmp::save(bmp_image, open_file_path.toStdString());
}

void MainWindow::on_actionSave_As_triggered() {
    QString file_path = QFileDialog::getSaveFileName(this, "Save a file");
    if (file_path != "") {
        Bmp::save(bmp_image, file_path.toStdString());
    }
}

void MainWindow::on_actioncoordinates_gray_triggered() {

    grayscale_toggle();
}

void MainWindow::on_actioncoordinates_invert_triggered() {
    invert_toggle();
}

void MainWindow::on_actionGraysacle_triggered() {
    bmp_image->grayscale(185, 398, 775, 245);
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(bmp_image->get_qImage()));
    ui->graphics_view->setScene(scene);
}

void MainWindow::on_actionInvert_triggered() {
    bmp_image->invert_color();
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(bmp_image->get_qImage()));
    ui->graphics_view->setScene(scene);
}

void MainWindow::on_actionQuit_triggered() {
    close();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    Save_quit_dialog* dialog = new Save_quit_dialog(this);
    connect(dialog, SIGNAL(save_button_clicked()), this, SLOT(on_actionSave_triggered()));
    connect(dialog, SIGNAL(cancel_button_clicked(bool)), this, SLOT(cancel_toggle()));
    dialog->exec();
    delete dialog;

    if (cancel_clicked) {
        event->ignore();
        cancel_clicked = false;
    } else {
        write_settings();
        event->accept();
    }
}

bool MainWindow::cancel_toggle() {
    return cancel_clicked = true;
}

void MainWindow::on_actionNew_triggered() {
    // TODO need to add some dialog: do u want to save "open_file_name"?
    if (bmp_image) { // need to delete prev image from scene before uploading next
        scene->clear();
        delete bmp_image;
    }

    open_file_path = ""; // this is for config
    bmp_image = Bmp::create(640, 480);

    scene->addPixmap(QPixmap::fromImage(bmp_image->get_qImage()));
    ui->graphics_view->setScene(scene);
}

void MainWindow::write_settings() {
    QSettings settings("My Soft", "LULpainter");

    settings.beginGroup("Size and position");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();

    settings.setValue("file_path", open_file_path);
}

void MainWindow::read_settings() {
    QSettings settings("My Soft", "LULpainter");

    settings.beginGroup("Size and position");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();

    open_file_path = QString(settings.value("file_path", "").toString());
    if (open_file_path != "") {
        bmp_image = Bmp::bmp(open_file_path.toStdString());

        scene->addPixmap(QPixmap::fromImage(bmp_image->get_qImage()));
        ui->graphics_view->setScene(scene);
    }
}

void MainWindow::grayscale_toggle() {
    ui->mainToolBar->widgetForAction(ui->actioncoordinates_gray)->setStyleSheet("width: 115px;"
                                                                                "background: rgb(150, 150, 150);");
    ui->mainToolBar->widgetForAction(ui->actioncoordinates_invert)->setStyleSheet("width: 115px;"
                                                                                "background: rgb(75, 75, 75);");

    grayscale_clicked = true;
    invert_clicked = false;
}

void MainWindow::invert_toggle() {
    ui->mainToolBar->widgetForAction(ui->actioncoordinates_invert)->setStyleSheet("width: 115px;"
                                                                                "background: rgb(150, 150, 150);");
    ui->mainToolBar->widgetForAction(ui->actioncoordinates_gray)->setStyleSheet("width: 115px;"
                                                                                "background: rgb(75, 75, 75);");

    invert_clicked = true;
    grayscale_clicked = false;
}
