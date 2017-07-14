#-------------------------------------------------
#
# Project created by QtCreator 2017-07-13T12:16:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DungeonCrawlerUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    project.cpp \
    map.cpp \
    tile.cpp \
    logger.cpp \
    homescreen.cpp \
    flatbutton.cpp

HEADERS  += mainwindow.h \
    project.h \
    map.h \
    tile.h \
    logger.h \
    homescreen.h \
    flatbutton.h

FORMS    += mainwindow.ui \
    homescreen.ui

DISTFILES += \
    config.txt

