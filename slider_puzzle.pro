#-------------------------------------------------
#
# Project created by QtCreator 2017-07-11T16:13:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = slider_puzzle
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
    matrix.cpp \
    board.cpp \
    pos.cpp \
    numberitem.cpp \
    graphicsview.cpp \
    boardscene.cpp \
    boardgen.cpp \
    gamewindow.cpp \
    sizepickerdialog.cpp \
    matrixgraph.cpp

HEADERS  += \
    board.h \
    matrix.h \
    pos.h \
    numberitem.h \
    graphicsview.h \
    boardscene.h \
    boardgen.h \
    gamewindow.h \
    sizepickerdialog.h \
    graph.h \
    edgegraph.h \
    matrixgraph.h

DISTFILES += \
    test.txt
