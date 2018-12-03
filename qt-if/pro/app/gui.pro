TEMPLATE = app

TARGET = gui
DESTDIR = out

DEPENDPATH += . inc src
INCLUDEPATH = inc/gui

#HEADERS += inc/*.hpp
HEADERS += inc/gui/*.hpp
#SOURCES += src/*.cpp
SOURCES += src/*.cpp
SOURCES += src/gui/*.cpp

OBJECTS_DIR = obj
MOC_DIR = moc
UI_DIR = ui

QT += widgets

