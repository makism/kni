#-------------------------------------------------
#
# Project created by QtCreator 2012-03-17T08:55:28
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = kni-demo
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

unix:!macx:!symbian: LIBS += -L$$PWD/../kni-build-desktop-Qt_in_PATH_Debug/ -lkni

INCLUDEPATH += $$PWD/../kni
DEPENDPATH += $$PWD/../kni

INCLUDEPATH += /usr/include/ni/
