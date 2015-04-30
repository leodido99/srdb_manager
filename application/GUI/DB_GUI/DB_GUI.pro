#-------------------------------------------------
#
# Project created by QtCreator 2015-04-22T16:32:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DB_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

MYDLLDIR = $$IN_PWD/../../Lib/dll

# As our header files are in the same directory, we can make Qt Creator find it
# by specifying it as INCLUDEPATH.
INCLUDEPATH += $$MYDLLDIR

# Dependency to library domain (libdomain.so for Unices or domain.dll on Win32)
# Repeat this for more libraries if needed.
win32:LIBS += $$quote($$MYDLLDIR/TMTCDBManagerLib.dll)
 unix:LIBS += $$quote(-L$$MYDLLDIR) -lTMTCDBManagerLib
