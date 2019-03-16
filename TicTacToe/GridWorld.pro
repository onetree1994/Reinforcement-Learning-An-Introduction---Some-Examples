#-------------------------------------------------
#
# Project created by QtCreator 2019-03-01T19:08:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GridWorld
TEMPLATE = app


SOURCES += main.cpp\
        gridworld.cpp \
    gridarea.cpp \
    curve.cpp

HEADERS  += gridworld.h \
    gridarea.h \
    curve.h

FORMS    += gridworld.ui
