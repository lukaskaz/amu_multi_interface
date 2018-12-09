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

clean_id.commands = "@echo \"Cleaning the dependency \'$(QMAKE_TARGET)\'\""
clean_id.depends =

notparallel.target = .NOTPARALLEL
#notparallel.commands =
#notparallel.depends = print_id all

#build.commands =
build.depends = all

#rebuild.commands =
rebuild.depends = all

#release.commands =
release.depends = all

#debug.commands =
debug.depends = all

#compiler_moc_header_clean.commands =
compiler_moc_header_clean.depends = clean_id

QMAKE_EXTRA_TARGETS += build rebuild release debug compiler_moc_header_clean clean_id


#QMAKE_LFLAGS += -Xlinker -Bstatic
#QMAKE_LFLAGS += -static
#QMAKE_LFLAGS = -static -static-libgcc

#QMAKE_POST_LINK = cp lib/* ../control/lib/
