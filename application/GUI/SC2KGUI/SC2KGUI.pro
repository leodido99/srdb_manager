#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T11:18:44
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SC2KGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sc2kdbmanager.cpp \
    recorddialog.cpp \
    packetwidget.cpp \
    puslist.cpp \
    pusitem.cpp

HEADERS  += mainwindow.h \
    sc2kdbmanager.h \
    recorddialog.h \
    packetwidget.h \
    puslist.h \
    pusitem.h

FORMS    += mainwindow.ui

#LIBPATH = ../../lib/dlls

#DEPENDPATH += $$LIBPATH
#INCLUDEPATH += $$LIBPATH

#LIBS += -L$$LIBPATH -lSC2KManager
