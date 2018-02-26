#include "lastuserinfo.h"

LastUserInfo::LastUserInfo(QWidget *parent): QDialog(parent) {
    QHBoxLayout* nameLayout = new QHBoxLayout();

    QVBoxLayout* labelsLayout = new QVBoxLayout();
    firstNameLabel = new QLabel("First name");
    lastNameLabel = new QLabel("Last name");
    labelsLayout->addWidget(firstNameLabel);
    labelsLayout->addWidget(lastNameLabel);

    QVBoxLayout* linesEditLayout = new QVBoxLayout();
    firstNameLine = new QLineEdit();
    lastNameLine = new QLineEdit();
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
    clearButton = new QPushButton("Clear");
    connect(updateButton, SIGNAL(clicked(bool)), this, SLOT(updateClicked()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(removeUserInfo()));
    buttonLayout->addWidget(updateButton);
    buttonLayout->addWidget(closeButton);
    buttonLayout->addWidget(clearButton);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(nameLayout);
    mainLayout->addWidget(sexGroupBox);
    mainLayout->addLayout(buttonLayout);

    readUserInfo();
    setLayout(mainLayout);
    setWindowTitle("Last user information");
    setMinimumWidth(300);
}

void LastUserInfo::updateClicked() {
    writeUserInfo();
    close();
}

void LastUserInfo::writeUserInfo() {
    QSettings userInfo("My soft", "Last user information");

    userInfo.beginGroup("LastUserInfo");
    userInfo.setValue("firstName", firstNameLine->text());
    userInfo.setValue("lastName", lastNameLine->text());
    if (maleButton->isChecked()) {
        userInfo.setValue("sex", "male");
    } else if (femaleButton->isChecked()) {
        userInfo.setValue("sex", "female");
    } else {
        QErrorMessage* errMsg = new QErrorMessage();
        errMsg->showMessage("Select your gender");
    }
}

void LastUserInfo::readUserInfo() {
    QSettings userInfo("My soft", "Last user information");

    userInfo.beginGroup("LastUserInfo");
    firstNameLine->setText(userInfo.value("firstName", "").toString());
    lastNameLine->setText(userInfo.value("lastName", "").toString());
    if (userInfo.value("sex").toString() == "male") {
        maleButton->setChecked(true);
    } else if (userInfo.value("sex").toString() == "female") {
        femaleButton->setChecked(true);
    }
}

void LastUserInfo::removeUserInfo() {
    QSettings userInfo("My soft", "Last user information");

    userInfo.beginGroup("LastUserInfo");
    userInfo.setValue("firstName", "");
    userInfo.setValue("lastName", "");
    userInfo.setValue("sex", "");
    userInfo.endGroup();

    firstNameLine->setText("");
    lastNameLine->setText("");

    maleButton->setAutoExclusive(false);
    maleButton->setChecked(false);
//    maleButton->setAutoExclusive(true);
//    femaleButton->setAutoExclusive(false);
    femaleButton->setChecked(false);
    maleButton->setAutoExclusive(true);
}

