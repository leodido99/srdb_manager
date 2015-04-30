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

SOURCES += tmtcdbmanagerlib.cpp \
    sc2kmanager.cpp

HEADERS += tmtcdbmanagerlib.h\
        tmtcdbmanagerlib_global.h \
    sc2kmanager.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

# Set the destination directory of the shared libraries
# MYDLLDIR is a name something I made up myself, DESTDIR is a QMake variable.
# $$IN_PWD expands to the directory your .pro file is in.
# This example copies the final build output to ../dlls (one level above your project).
MYDLLDIR = $$IN_PWD/../dll

# We need quotes around the path in order to support whitespaces in the path
# for Windows. e.g. (''C:\Users\Gert van Dijk\...'').
# For some strange reason $$quote(...) does not seem to work for Windows here.
DESTDIR = \"$$MYDLLDIR\"

#
# Here's some magic to move all of the project's header files to the same DLL directory.
#

DDIR = \"$$MYDLLDIR/\"
SDIR = \"$$IN_PWD/\"
# Replace slashes in paths with backslashes for Windows
win32:file ~= s,/,\\,g
win32:DDIR ~= s,/,\\,g
win32:SDIR ~= s,/,\\,g
# For-loop to copy all header files to DDIR.
for(file, HEADERS) {
    QMAKE_POST_LINK += $$QMAKE_COPY $$quote($${SDIR}$${file}) $$quote($$DDIR) $$escape_expand(\\n\\t)
}
