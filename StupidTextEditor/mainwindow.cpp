#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
                                         ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
    ui->statusBar->showMessage("Ready to work");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionRead_triggered() {
    Dialog* window = new Dialog(this);
    window->show();

    connect(window, SIGNAL(filePath(QString)), this, SLOT(readFromFile(QString)));
}

void MainWindow::readFromFile(QString const& filePath) {
    QFile myFile(filePath);

    if (!myFile.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(this, "Error", "Path isn't correct");
        ui->statusBar->showMessage("Error");
        return;
    } else {
        QTextStream stream(&myFile);
        QString buffer = stream.readAll();

        ui->textEdit->setText(buffer);
        ui->statusBar->showMessage("The file has read: " + filePath);

        myFile.flush();
        myFile.close();
    }
}

void MainWindow::on_actionWrite_to_file_triggered() {
    QFile myFile("text.txt");

    if (!myFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::information(this, "Error", "Path isn't correct");
        return;
    } else {
        QTextStream stream(&myFile);
        stream << ui->textEdit->toPlainText();
        ui->statusBar->showMessage("The file has written");

        myFile.close();
    }
}

void MainWindow::on_actionPrint_directory_triggered() {
    Dialog* window = new Dialog(this);
    window->show();

    connect(window, SIGNAL(filePath(QString)), this, SLOT(printDir(QString)));
}

void MainWindow::printDir(QString const& dirPath) {
    QDir myDir(dirPath);
    QString buffer = "";

    for (QFileInfo fileInfo: myDir.entryInfoList()) {
        buffer += fileInfo.absoluteFilePath() + '\n';
    }

    ui->textEdit->setText(buffer);
    ui->statusBar->showMessage("All directory content have printed");
}
