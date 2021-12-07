#-------------------------------------------------
#
# Project created by QtCreator 2021-11-20T02:56:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ownSaper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        field.cpp \
        fieldcell.cpp \
        usermodedialog.cpp

HEADERS  += mainwindow.h \
            field.h \
            fieldcell.h \
            statefields.h \
            helper.h \
            usermodedialog.h

DISTFILES += \
            ownSaper.pro.user

FORMS += \
            usermodedialog.ui
