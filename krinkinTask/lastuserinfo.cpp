#include "lastuserinfo.h"

LastUserInfo::LastUserInfo(QWidget *parent): QDialog(parent) {
    QHBoxLayout* nameLayout = new QHBoxLayout();

    QVBoxLayout* labelsLayout = new QVBoxLayout();
    firstNameLabel = new QLabel("First name");
    lastNameLabel = new QLabel("Last name");
    labelsLayout->addWidget(firstNameLabel);
    labelsLayout->addWidget(lastNameLabel);

    QVBoxLayout* linesEditLayout = new QVBoxLayout();
    firstNameLine = new QLineEdit(userInfo.getFirstName());
    lastNameLine = new QLineEdit(userInfo.getLastName());
    linesEditLayout->addWidget(firstNameLine);
    linesEditLayout->addWidget(lastNameLine);

    nameLayout->addLayout(labelsLayout);
    nameLayout->addLayout(linesEditLayout);

    QHBoxLayout* sexLayout = new QHBoxLayout();
    sexGroupBox = new QGroupBox("Sex");
    maleButton = new QRadioButton("Male");
    femaleButton = new QRadioButton("Female");
    sexLayout->addWidget(maleButton);
    sexLayout->addWidget(femaleButton);
    sexGroupBox->setLayout(sexLayout);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    updateButton = new QPushButton("Update");
    closeButton = new QPushButton("Close");
    connect(updateButton, SIGNAL(clicked(bool)), this, SLOT(updateClicked()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    buttonLayout->addWidget(updateButton);
    buttonLayout->addWidget(closeButton);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(nameLayout);
    mainLayout->addWidget(sexGroupBox);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle("Last user information");
    setMinimumWidth(300);
}

void LastUserInfo::updateClicked() {
    userInfo.setFirstName(firstNameLine->text());
    userInfo.setLastName(lastNameLine->text());
    if (maleButton->isChecked()) {
        userInfo.setSex("Male");
    } else if (femaleButton->isChecked()) {
        userInfo.setSex("Female");
    }

    close();
}

QString UserInfo::getFirstName() const {
    return firstName;
}

QString UserInfo::getLastName() const {
    return lastName;
}

QString UserInfo::getSex() const {
    return sex;
}

void UserInfo::setFirstName(QString firstName) {
    this->firstName = firstName;
}

void UserInfo::setLastName(QString lastName) {
    this->lastName = lastName;
}

void UserInfo::setSex(QString sex) {
    this->sex = sex;
}


