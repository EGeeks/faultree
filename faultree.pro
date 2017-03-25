#-------------------------------------------------
#
# Project created by QtCreator 2017-03-18T10:35:31
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = faultree
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    mainwindow.cpp \
    centerform.cpp \
    mydb.cpp \
    zhenduanform.cpp \
    treemanageform.cpp \
    ruleform.cpp

HEADERS  += login.h \
    mainwindow.h \
    centerform.h \
    mydb.h \
    zhenduanform.h \
    common.h \
    treemanageform.h \
    ruleform.h

FORMS    += login.ui \
    mainwindow.ui \
    centerform.ui \
    zhenduanform.ui \
    treemanageform.ui \
    ruleform.ui

RESOURCES += \
    image.qrc
