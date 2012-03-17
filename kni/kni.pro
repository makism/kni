#-------------------------------------------------
#
# Project created by QtCreator 2012-03-17T08:54:46
#
#-------------------------------------------------

QT       += opengl

QT       -= gui

TARGET   = kni
TEMPLATE = lib

DEFINES += KNI_LIBRARY

SOURCES += \
    knicontext.cpp \
    knionicontext.cpp \
    knidepthgenerator.cpp \
    knigenerator.cpp

HEADERS +=\
    kni_global.h \
    knionicontext.h \
    knicontext.h \
    knidepthgenerator.h \
    kni_namespace.h \
    kni.h \
    knigenerator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += /usr/include/ni/
LIBS += -L/usr/lib/ -lOpenNI






































