#-------------------------------------------------
#
# Project created by QtCreator 2017-07-11T16:13:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = slider_puzzle
TEMPLATE = app
#CONFIG += console
QMAKE_CXXFLAGS_RELEASE += -DNDEBUG

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

PRECOMPILED_HEADER = pch.h

SOURCES += main.cpp\
    board.cpp \
    numberitem.cpp \
    graphicsview.cpp \
    boardscene.cpp \
    boardgen.cpp \
    gamewindow.cpp \
    sizepickerdialog.cpp \
    boardrotator.cpp \
    numbermover.cpp \
    test_console_board.cpp \
    test_matrixgraph.cpp \
    test_edgegraph.cpp \
    test_numbermover.cpp \
    linemover.cpp \
    test_linemover.cpp \
    puzzle_mover.cpp \
    test_puzzlemover.cpp \
    movelist.cpp \
    moverparam.cpp \
    test_prioorityqueue.cpp \
    test_astar.cpp \
    debug_output.cpp \
    test_search_board.cpp \
    boardgraph.cpp

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
    edgegraph.h \
    matrixgraph.h \
    boardrotator.h \
    pch.h \
    numbermover.h \
    resizable_matrix.h \
    boolmatrix.h \
    linemover.h \
    puzzle_mover.h \
    movelist.h \
    moverparam.h \
    dijkstra.h \
    debug_output.h \
    boardgraph.h

DISTFILES += \
    test.txt
