#-------------------------------------------------
#
# Project created by QtCreator 2012-04-04T18:45:46
#
#-------------------------------------------------

QT       += core dbus

QT       -= gui

TARGET = kni-dbus
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lkdeui
INCLUDEPATH += "/usr/include/KDE/"

SOURCES += main.cpp \
    kni.cpp

HEADERS += \
    kni.h


