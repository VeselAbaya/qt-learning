#-------------------------------------------------
#
# Project created by QtCreator 2018-03-23T13:17:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Painter
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    bmp_image24.cpp \
    bmp.cpp \
    my_graphics_scene.cpp \
    save_dialog.cpp \
    crop_dialog.cpp \
    expanse_dialog.cpp \
    help_dialog.cpp \
    info_dialog.cpp

HEADERS += \
        mainwindow.h \
    bmp_image24.h \
    bmp_image.h \
    bmp.h \
    my_graphics_scene.h \
    save_dialog.h \
    resize_direction.h \
    crop_dialog.h \
    expanse_dialog.h \
    help_dialog.h \
    info_dialog.h

FORMS += \
        mainwindow.ui \
    save_dialog.ui \
    crop_dialog.ui \
    expanse_dialog.ui \
    help_dialog.ui
