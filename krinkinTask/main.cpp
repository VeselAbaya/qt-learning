#include "lastuserinfo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LastUserInfo w;
    w.show();

    return app.exec();
}
