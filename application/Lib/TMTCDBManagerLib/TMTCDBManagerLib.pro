#-------------------------------------------------
#
# Project created by QtCreator 2015-04-23T08:42:37
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = TMTCDBManagerLib
TEMPLATE = lib

DEFINES += TMTCDBMANAGERLIB_LIBRARY

SOURCES += tmtcdbmanagerlib.cpp

HEADERS += tmtcdbmanagerlib.h\
        tmtcdbmanagerlib_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
