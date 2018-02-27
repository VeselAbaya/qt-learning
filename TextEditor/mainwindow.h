#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QSettings>
#include <QCloseEvent>

namespace Ui {
    class MainWindow;
}

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void closeEvent(QCloseEvent* event);

    void writeSettings();
    void readSettings();
    bool fileOpen(QString const& filePath);

    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionPaste_triggered();
    void on_actionSave_triggered();
    void on_actionCut_triggered();
    void on_actionSave_As_triggered();
    void on_actionCopy_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

private:
    Ui::MainWindow *ui;
    QString fileName;
};

#endif // MAINWINDOW_H
