#-------------------------------------------------
#
# Project created by QtCreator 2017-12-21T04:06:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prot1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \ 
    a.cpp \
    bvh.cpp \
    campol.cpp \
    pol.cpp \
    pol_reach_constraint.cpp \
    qua.cpp \
    rot2.cpp \
    san.cpp \
    thr.cpp \
    two.cpp \
    utiuti.cpp \
    my_graphic_view.cpp

HEADERS += \
        mainwindow.h \ 
    a.h \
    bvh.h \
    campol.h \
    pol.h \
    pol_reach_constraint.h \
    qua.h \
    rot2.h \
    san.h \
    thr.h \
    two.h \
    utiuti.h \
    my_graphic_view.h

FORMS += \
        mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
INCLUDEPATH += /home/ambi/myc/smth/src
