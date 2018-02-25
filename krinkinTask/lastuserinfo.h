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

class UserInfo {
public:
    UserInfo(QString firstName="", QString lastName="", QString sex="Male") {
        if (!wasCreated) {
            this->firstName = firstName;
            this->lastName = lastName;
            this->sex = sex;

            wasCreated = true;
        }
    }

    QString getFirstName() const;
    QString getLastName() const;
    QString getSex() const;

    void setFirstName(QString firstName);
    void setLastName(QString lastName);
    void setSex(QString sex);

private:
    QString firstName;
    QString lastName;
    QString sex;
    bool wasCreated = false;
};


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
    UserInfo userInfo;

private slots:
    void updateClicked();
};
#endif // LASTUSERINFO_H
