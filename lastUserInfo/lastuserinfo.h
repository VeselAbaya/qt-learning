#ifndef LASTUSERINFO_H
#define LASTUSERINFO_H

#include <QDialog>
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QString>
#include <QErrorMessage>
#include <QDebug>
#include <QSettings>

class LastUserInfo: public QDialog {
    Q_OBJECT

public:
    explicit LastUserInfo(QWidget *parent = 0);

private:
    QLabel* firstNameLabel;
    QLabel* lastNameLabel;
    QLineEdit* firstNameLine;
    QLineEdit* lastNameLine;
    QGroupBox* sexGroupBox;
    QRadioButton* maleButton;
    QRadioButton* femaleButton;
    QPushButton* updateButton;
    QPushButton* closeButton;
    QPushButton* clearButton;

private slots:
    void updateClicked();
    void writeUserInfo();
    void readUserInfo();
    void removeUserInfo();
};
#endif // LASTUSERINFO_H
