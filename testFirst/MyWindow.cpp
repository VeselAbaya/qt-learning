#include "TextEditor.h"

TextEditor::MyWindow::MyWindow(QWidget* parent): QDialog(parent) {
    label    = new QLabel("&Enter");
    lineEdit = new QLineEdit();
    label->setBuddy(lineEdit);
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(TextChange(QString)));

    check1 = new QCheckBox("Upper case");
    check2 = new QCheckBox("Inverse");

    buttonOk = new QPushButton("Ok");
    buttonOk->setDefault(true);
    buttonOk->setEnabled(false);
    connect(buttonOk, SIGNAL(clicked(bool)), this, SLOT(OkClicked()));

    buttonClose = new QPushButton("Close");
    connect(buttonClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    QHBoxLayout* inputLayout = new QHBoxLayout();
    inputLayout->addWidget(label);
    inputLayout->addWidget(lineEdit);

    QVBoxLayout* checkLayout = new QVBoxLayout();
    checkLayout->addWidget(check1);
    checkLayout->addWidget(check2);

    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->addLayout(inputLayout);
    leftLayout->addLayout(checkLayout);

    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->addWidget(buttonOk);
    rightLayout->addWidget(buttonClose);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);
    setWindowTitle("Stupid editinig");
}

void TextEditor::MyWindow::TextChange(QString str) {
    buttonOk->setEnabled(!str.isEmpty());
}

void TextEditor::MyWindow::OkClicked() {
    if (!check1->isChecked() && !check2->isChecked()) {
        emit Simple(lineEdit->text());
    } else if (check1->isChecked() && check2->isChecked()) {
        emit Inverse_and_UpperCase(lineEdit->text());
    } else if (check1->isChecked()) {
        emit UpperCase(lineEdit->text());
    } else if (check2->isChecked()) {
        emit Inverse(lineEdit->text());
    }
}

void TextEditor::Signal::Simple(QString str) {
    QMessageBox* msgBox = new QMessageBox();
    msgBox->setText(str);
    msgBox->setMinimumSize(300, 300);
    msgBox->show();
}

void TextEditor::Signal::UpperCase(QString str) {
    QMessageBox* msgBox = new QMessageBox();
    msgBox->setText(str.toUpper());
    msgBox->setMinimumSize(300, 300);
    msgBox->exec();
}

void TextEditor::Signal::Inverse(QString str) {
    QString res;
    for (auto str_it = str.rbegin(); str_it != str.rend(); ++str_it) {
        res.append(*str_it);
    }

    QMessageBox* msgBox = new QMessageBox();
    msgBox->setText(res);
    msgBox->setMinimumSize(300, 300);
    msgBox->exec();
}

void TextEditor::Signal::Inverse_and_UpperCase(QString str) {
    QString res;
    for (auto str_it = str.rbegin(); str_it != str.rend(); ++str_it) {
        res.append(*str_it);
    }

    QMessageBox* msgBox = new QMessageBox();
    msgBox->setText(res.toUpper());
    msgBox->setMinimumSize(300, 300);
    msgBox->exec();
}
