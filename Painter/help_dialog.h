#ifndef HELP_DIALOG_H
#define HELP_DIALOG_H

#include <QDialog>

namespace Ui {
    class Help_dialog;
}

/*! \class Help_dialog
 * \brief Class for help dialog content */
class Help_dialog : public QDialog {
    Q_OBJECT

public:
    explicit Help_dialog(QWidget *parent = 0);
    ~Help_dialog();

private:
    Ui::Help_dialog *ui;
};

#endif // HELP_DIALOG_H
