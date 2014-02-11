#-------------------------------------------------
#
# Project created by QtCreator 2014-02-07T14:50:24
#
#-------------------------------------------------

QT       += core gui network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = YouKu
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    jsondata.cpp \
    youkuparse.cpp \
    inputwidget.cpp \
    mypushbutton.cpp

HEADERS  += widget.h \
    jsondata.h \
    youkuparse.h \
    inputwidget.h \
    mypushbutton.h

RESOURCES += \
    res.qrc
