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
    glwindow.cpp \
    leaplistener.cpp \
    leapcontroller.cpp

HEADERS  += mainwindow.h \
    glwindow.h \
    leaplistener.h \
    leapcontroller.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -I"$$_PRO_FILE_PWD_/include"

LIBS += -lglut "/Users/delvistaveras/Desktop/Build_18/Phone_Motion/lib/libLeap.dylib"
