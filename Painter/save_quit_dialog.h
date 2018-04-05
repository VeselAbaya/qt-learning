#ifndef SAVE_QUIT_DIALOG_H
#define SAVE_QUIT_DIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
    class Save_quit_dialog;
}

class Save_quit_dialog: public QDialog {
    Q_OBJECT

public:
    explicit Save_quit_dialog(QWidget *parent = 0);
    ~Save_quit_dialog();

signals:
    void save_button_clicked();
    void cancel_button_clicked(bool);

private slots:
    void closeEvent(QCloseEvent* event);
    void on_save_button_clicked();
    void on_cancel_button_clicked();
    void on_no_button_clicked();

private:
    Ui::Save_quit_dialog *ui;
};

#endif // SAVE_QUIT_DIALOG_H
