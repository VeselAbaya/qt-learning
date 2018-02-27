#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
                                         ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
    setWindowTitle("Text editor");
    ui->statusBar->showMessage("App is ready");

    readSettings();
    if (fileOpen(fileName)) {
        ui->statusBar->showMessage("Yout last editing file(" + fileName + ") has been opened");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::writeSettings() {
    QSettings settings("My Soft", "TextEditor");

    settings.beginGroup("Size and position");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();

    settings.setValue("fileName", fileName);
}

void MainWindow::readSettings() {
    QSettings settings("My Soft", "TextEditor");

    settings.beginGroup("Size and position");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();

    fileName = settings.value("fileName", "").toString();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::on_actionNew_triggered() {
    fileName = "";
    ui->textEdit->setPlainText("");
    ui->statusBar->showMessage("New file");
    setWindowTitle("Text editor");
}

void MainWindow::on_actionOpen_triggered() {
    fileName = QFileDialog::getOpenFileName(this, "Open a file");

    fileOpen(fileName);
}

void MainWindow::on_actionSave_triggered() {
    if (!fileName.isEmpty()) {
        QFile file(fileName);

        if (file.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&file);

            out << ui->textEdit->toPlainText();

            file.flush();
            file.close();

            ui->statusBar->showMessage(fileName + " has been saved");
        }
    } else {
        on_actionSave_As_triggered();
    }

}

void MainWindow::on_actionSave_As_triggered() {
    fileName = QFileDialog::getSaveFileName();

    if (!fileName.isEmpty()) {
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionCopy_triggered() {
    ui->textEdit->copy();
    ui->statusBar->showMessage("Copied");
}

void MainWindow::on_actionCut_triggered() {
    ui->textEdit->cut();
    ui->statusBar->showMessage("Cutted");
}

void MainWindow::on_actionPaste_triggered() {
    ui->textEdit->paste();
    ui->statusBar->showMessage("Pasted");
}

void MainWindow::on_actionUndo_triggered() {
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered() {
    ui->textEdit->redo();
}

bool MainWindow::fileOpen(QString const& filePath) {
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream in(&file);
            QString buffer = in.readAll();

            ui->textEdit->setPlainText(buffer);

            file.flush();
            file.close();

            ui->statusBar->showMessage(fileName + " has been opened");
            setWindowTitle("Text editor: " + fileName);
            return true;
        }
    }

    return false;
}
