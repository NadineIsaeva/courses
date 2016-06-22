#-------------------------------------------------
#
# Project created by QtCreator 2016-06-15T13:24:24
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += mobility c++11
MOBILITY += multimedia
TARGET = CourseWork
TEMPLATE = app


SOURCES += main.cpp\
        startwindow.cpp \
    memeswindow.cpp \
    chooselocalmeme.cpp \
    choosecolor.cpp \
    memescollection.cpp \
    memeitem.cpp \
    choosecategory.cpp

HEADERS  += startwindow.h \
    memeswindow.h \
    chooselocalmeme.h \
    choosecolor.h \
    memescollection.h \
    memeitem.h \
    choosecategory.h

FORMS    += startwindow.ui \
    memeswindow.ui \
    chooselocalmeme.ui \
    choosecolor.ui \
    memescollection.ui \
    choosecategory.ui
