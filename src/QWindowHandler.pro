#-------------------------------------------------
#
# Project created by QtCreator 2018-02-25T00:09:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QWindowHandler
TEMPLATE = app

CONFIG += c++11

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
        widget.cpp \
    io/windowhandler.cpp \
    io/keysender.cpp \
    ui/qtaikobotwidget.cpp \
    ai/neural/neuralnet.cpp \
    io/qscreenscanner.cpp \
    controller/qtaikobotworker.cpp \
    controller/qtaikobotasync.cpp \
    controller/qtaikobotsync.cpp \
    controller/qtaikobot.cpp

HEADERS += \
        widget.h \
    io/windowhandler.h \
    io/keysender.h \
    ui/qtaikobotwidget.h \
    ai/neural/neuralnet.h \
    io/qscreenscanner.h \
    controller/qtaikobotworker.h \
    controller/qtaikobotasync.h \
    controller/qtaikobotsync.h \
    controller/qtaikobot.h
