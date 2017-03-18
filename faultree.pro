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
    mainwindow.cpp \
    centerform.cpp

HEADERS  += login.h \
    mainwindow.h \
    centerform.h

FORMS    += login.ui \
    mainwindow.ui \
    centerform.ui

RESOURCES += \
    image.qrc
