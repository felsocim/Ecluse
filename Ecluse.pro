#-------------------------------------------------
#
# Project created by QtCreator 2017-03-06T10:18:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ecluse
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    vanne.cpp \
    porte.cpp \
    signalisation.cpp \
    panne.cpp

HEADERS  += mainwindow.h \
    vanne.h \
    porte.h \
    signalisation.h \
    panne.h

FORMS    += mainwindow.ui

RESOURCES += \
    resimages.qrc
