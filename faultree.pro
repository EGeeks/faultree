#-------------------------------------------------
#
# Project created by QtCreator 2017-03-18T10:35:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = faultree
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    mainwindow.cpp

HEADERS  += login.h \
    mainwindow.h

FORMS    += login.ui \
    mainwindow.ui

RESOURCES += \
    image.qrc
