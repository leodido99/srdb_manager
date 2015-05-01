#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T11:16:48
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = SC2KManager
TEMPLATE = lib

DEFINES += SC2KMANAGER_LIBRARY

SOURCES += sc2kmanager.cpp

HEADERS += sc2kmanager.h\
        sc2kmanager_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
