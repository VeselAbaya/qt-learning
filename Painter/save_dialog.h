#ifndef SAVE_DIALOG_H
#define SAVE_DIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QLabel>
#include <QString>

namespace Ui {
    class save_quit_dialog;
}

class Save_dialog: public QDialog {
    Q_OBJECT

public:
    explicit Save_dialog(QWidget *parent = 0);
    ~Save_dialog();

signals:
    void save_button_clicked();
    void cancel_button_clicked(bool);

private slots:
    void closeEvent(QCloseEvent* event);
    void on_save_button_clicked();
    void on_cancel_button_clicked();
    void on_no_button_clicked();

private:
    Ui::save_quit_dialog *ui;
};

#endif // SAVE_DIALOG_H
