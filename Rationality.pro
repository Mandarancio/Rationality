# -------------------------------------------------
# Project created by QtCreator 2010-06-19T22:25:59
# -------------------------------------------------
include(QFreeDesktopMime/QFreeDesktopMime.pro)
QT += sql \
    xml \
    dbus \
    webkit
TEMPLATE = app
TARGET = Rationality
MOC_DIR = tmp
OBJECTS_DIR = obj
DESTDIR = bin
SOURCES += main.cpp \
    rationality.cpp \
    folderview.cpp \
    element.cpp \
    attribute.cpp \
    relation.cpp \
    relationbar.cpp \
    filedatabase.cpp \
    searchbutton.cpp \
    tagview.cpp \
    filterbar.cpp \
    leftbar.cpp \
    panelbutton.cpp \
    searchbar.cpp \
    backbutton.cpp \
    forwardbutton.cpp \
    filterbutton.cpp \
    propertybar.cpp \
    elementfile.cpp
HEADERS += rationality.h \
    folderview.h \
    element.h \
    attribute.h \
    relation.h \
    relationbar.h \
    filedatabase.h \
    searchbutton.h \
    tagview.h \
    filterbar.h \
    leftbar.h \
    panelbutton.h \
    searchbar.h \
    backbutton.h \
    forwardbutton.h \
    filter.h \
    filterbutton.h \
    propertybar.h \
    elementfile.h
FORMS += rationality.ui
OTHER_FILES += 
#RESOURCES += Resource.qrc
