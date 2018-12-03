TEMPLATE = lib
#CONFIG += staticlib

TARGET = qt-if
DESTDIR = lib

DEPENDPATH += . inc src
INCLUDEPATH = inc ../support/inc

HEADERS += inc/*.hpp
SOURCES += src/*.cpp

LIBS += -L../support/lib -lsupport

OBJECTS_DIR = obj
MOC_DIR = moc
UI_DIR = ui

QT += widgets

#QMAKE_LFLAGS += -Xlinker -Bstatic
#QMAKE_LFLAGS += -static
#QMAKE_LFLAGS = -static -static-libgcc

#QMAKE_POST_LINK = cp lib/* ../control/lib/

#build.commands =
build.depends = all

#release.commands =
release.depends = all

#debug.commands =
debug.depends = all

QMAKE_EXTRA_TARGETS += build release debug
