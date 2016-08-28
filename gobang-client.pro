#-------------------------------------------------
#
# Project created by QtCreator 2016-08-28T12:26:35
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gobang-client
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    connectserver.cpp \
    messagehandle.cpp

HEADERS  += mainwidget.h \
    connectserver.h \
    messagehandle.h

FORMS    += mainwidget.ui
