#ifndef SAVE_DIALOG_H
#define SAVE_DIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QLabel>
#include <QString>

namespace Ui {
    class save_quit_dialog;
}

/*! \class Save_dialog
 * \brief Class implements saving dialog
 */
class Save_dialog: public QDialog {
    Q_OBJECT

public:
    explicit Save_dialog(QWidget *parent = 0);
    ~Save_dialog();

signals:
    /*! Signal emited when save button is clicked
     * \param save_dialog Pointer on this dialog
     * (needed to open make this dialog parent of file dialog)
     */
    void save_button_clicked(QWidget* save_dialog);
    /*! Signal emited when cancel button is clicked
     * \param clicked If cancel clicked - true, else - false
     */
    void cancel_button_clicked(bool clicked);

private slots:
    void closeEvent(QCloseEvent* event);
    void on_save_button_clicked();
    void on_cancel_button_clicked();
    void on_no_button_clicked();

private:
    Ui::save_quit_dialog *ui;
};

#endif // SAVE_DIALOG_H
