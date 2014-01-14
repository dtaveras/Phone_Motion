#-------------------------------------------------
#
# Project created by QtCreator 2014-01-13T17:22:09
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Phone_Motion
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwindow.cpp

HEADERS  += mainwindow.h \
    glwindow.h

FORMS    += mainwindow.ui

LIBS += -lglut
