#include <QApplication>
#include "TextEditor.h"

using namespace TextEditor;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyWindow* myWindow = new TextEditor::MyWindow();
    myWindow->show();

    Signal* signal = new Signal();
    QObject::connect(myWindow, SIGNAL(Simple(QString)), signal, SLOT(Simple(QString)));
    QObject::connect(myWindow, SIGNAL(Inverse(QString)), signal,SLOT(Inverse(QString)));
    QObject::connect(myWindow, SIGNAL(UpperCase(QString)), signal, SLOT(UpperCase(QString)));
    QObject::connect(myWindow, SIGNAL(Inverse_and_UpperCase(QString)), signal, SLOT(Inverse_and_UpperCase(QString)));

    return app.exec();
}
