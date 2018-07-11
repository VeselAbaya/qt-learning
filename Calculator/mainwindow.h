#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cmath>

#include <utility>

#include <QMainWindow>
#include <QErrorMessage>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    double left;
    char op;
    Ui::MainWindow *ui;


private slots:
    void digits_numbers();
    void operations();
    void equals();

    void on_pushButton_dot_clicked();
    void on_pushButton_sign_clicked();
    void on_pushButton_AC_clicked();
};

#endif // MAINWINDOW_H
