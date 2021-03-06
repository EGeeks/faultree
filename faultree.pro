#-------------------------------------------------
#
# Project created by QtCreator 2017-03-18T10:35:31
#
#-------------------------------------------------

QT       += core gui sql axcontainer printsupport
#QT       += core gui sql printsupport

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
    ruleform.cpp \
    addtreenodedialog.cpp \
    rulemanagedialog.cpp \
    parammanagedialog.cpp \
    ruleeditdialog.cpp \
    parameditdialog.cpp \
    schememanagedialog.cpp \
    schemeeditdialog.cpp \
    accountdialog.cpp \
    fileform.cpp

HEADERS  += login.h \
    mainwindow.h \
    centerform.h \
    mydb.h \
    zhenduanform.h \
    common.h \
    treemanageform.h \
    ruleform.h \
    addtreenodedialog.h \
    rulemanagedialog.h \
    parammanagedialog.h \
    ruleeditdialog.h \
    parameditdialog.h \
    schememanagedialog.h \
    schemeeditdialog.h \
    accountdialog.h \
    fileform.h

FORMS    += login.ui \
    mainwindow.ui \
    centerform.ui \
    zhenduanform.ui \
    treemanageform.ui \
    ruleform.ui \
    addtreenodedialog.ui \
    rulemanagedialog.ui \
    parammanagedialog.ui \
    ruleeditdialog.ui \
    parameditdialog.ui \
    schememanagedialog.ui \
    schemeeditdialog.ui \
    accountdialog.ui \
    fileform.ui

RESOURCES += \
    image.qrc
