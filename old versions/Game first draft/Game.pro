#-------------------------------------------------
#
# Project created by QtCreator 2015-04-23T13:36:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    board.cpp \
    asteroid.cpp \
    bullets.cpp

HEADERS  += mainwindow.h \
    board.h \
    asteroid.h \
    bullets.h

FORMS    += \
    board.ui \
    mainwindow.ui

RESOURCES += \
    images.qrc
