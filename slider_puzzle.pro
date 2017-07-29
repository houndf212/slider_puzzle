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

HEADERS += \
    basic_pos.h \
    board.h \
    board_api.h \
    boardgraph.h \
    boardrotator.h \
    boardscene.h \
    boolmatrix.h \
    debug_output.h \
    dijkstra.h \
    edgegraph.h \
    gamewindow.h \
    graphicsview.h \
    linemover.h \
    matrix.h \
    matrixgraph.h \
    movedirection.h \
    movelist.h \
    moverparam.h \
    numberitem.h \
    numbermover.h \
    pos.h \
    puzzle_mover.h \
    resizable_matrix.h \
    sizepickerdialog.h

SOURCES += \
    board.cpp \
    board_api.cpp \
    boardgraph.cpp \
    boardrotator.cpp \
    boardscene.cpp \
    debug_output.cpp \
    gamewindow.cpp \
    graphicsview.cpp \
    linemover.cpp \
    main.cpp \
    matrixgraph.cpp \
    movelist.cpp \
    moverparam.cpp \
    numberitem.cpp \
    numbermover.cpp \
    puzzle_mover.cpp \
    sizepickerdialog.cpp

Debug {
SOURCES += \
    test_astar.cpp \
    test_console_board.cpp \
    test_edgegraph.cpp \
    test_gen.cpp \
    test_linemover.cpp \
    test_matrixgraph.cpp \
    test_numbermover.cpp \
    test_optimize_move.cpp \
    test_prioorityqueue.cpp \
    test_puzzlemover.cpp \
    test_search_board.cpp
}
