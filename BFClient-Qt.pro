#-------------------------------------------------
#
# Project created by QtCreator 2016-10-22T14:24:09
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BFClient-Qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loginwindow.cpp \
    sessionmgr.cpp \
    openwindow.cpp

HEADERS  += mainwindow.h \
    loginwindow.h \
    sessionmgr.h \
    openwindow.h

FORMS    += mainwindow.ui \
    loginwindow.ui \
    openwindow.ui

DISTFILES += \
    LICENSE \
    README.md
