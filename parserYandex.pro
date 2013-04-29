#-------------------------------------------------
#
# Project created by QtCreator 2013-04-22T14:41:55
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = parserYandex
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    author.cpp \
    howtouse.cpp \
    saver.cpp

HEADERS  += mainwindow.h \
    author.h \
    howtouse.h \
    saver.h

FORMS    += mainwindow.ui \
    author.ui \
    howtouse.ui

RESOURCES += \
    resource.qrc
