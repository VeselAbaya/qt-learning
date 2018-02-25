#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QObject>
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

namespace TextEditor {
    class MyWindow: public QDialog {
        Q_OBJECT // Macros for qmake
    public:
        MyWindow(QWidget* parent=0);
    private:
        QLabel* label;
        QLineEdit* lineEdit;
        QCheckBox* check1;
        QCheckBox* check2;
        QPushButton* buttonOk;
        QPushButton* buttonClose;
    private slots:
    void OkClicked();
        void TextChange(QString str);
    signals:
        void Simple(QString str);
        void UpperCase(QString str);
        void Inverse(QString str);
        void Inverse_and_UpperCase(QString str);
    };

    class Signal: public QObject {
        Q_OBJECT
    private:
        QString str;
    public slots:
        void Simple(QString str);
        void UpperCase(QString str);
        void Inverse(QString str);
        void Inverse_and_UpperCase(QString str);
    };
}

#endif // MYWINDOW_H
