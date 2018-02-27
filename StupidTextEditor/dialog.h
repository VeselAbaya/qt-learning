#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QPushButton>

namespace Ui {
class Dialog;
}

class Dialog: public QDialog {
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;

signals:
    void filePath(QString const& path);

private slots:
    void okClicked();
};

#endif // DIALOG_H
