#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T11:19:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Angry_Jellies
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameboard.cpp

HEADERS  += mainwindow.h \
    gameboard.h \
    Documentation.h

FORMS    += mainwindow.ui \
    gameboard.ui

RESOURCES += \
    images/images.qrc

DISTFILES +=
