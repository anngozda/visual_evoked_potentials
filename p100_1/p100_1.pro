#-------------------------------------------------
#
# Project created by QtCreator 2018-11-03T14:28:33
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = p100_1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sendbroadcastthread.cpp \
    p100.cpp

HEADERS  += mainwindow.h \
    sendbroadcastthread.h \
    p100.h

FORMS    += mainwindow.ui \
    p100.ui
