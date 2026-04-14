cmake_minimum_required(VERSION 3.16)
project(slider_puzzle VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

if (CMAKE_BUILD_TYPE STREQUAL "ASAN") 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g ")

endif()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto -fno-exceptions -fno-rtti -fvisibility=hidden ")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto")

find_package(Qt6 REQUIRED COMPONENTS Gui Widgets)

qt_standard_project_setup()

qt_add_executable(slider_puzzle WIN32 MACOSX_BUNDLE
    NineSolver.cpp NineSolver.h
    NumSolver.h
    basic_pos.h
    board.cpp board.h
    board_api.cpp board_api.h
    boardgraph.cpp boardgraph.h
    boardrotator.cpp boardrotator.h
    boardscene.cpp boardscene.h
    boolmatrix.h
    debug_output.cpp debug_output.h
    dijkstra.h
    edgegraph.h
    gamewindow.cpp gamewindow.h
    graphicsview.cpp graphicsview.h
    linemover.cpp linemover.h
    main.cpp
    matrix.h
    matrixgraph.cpp matrixgraph.h
    movedirection.h
    movelist.cpp movelist.h
    moverparam.cpp moverparam.h
    numberitem.cpp numberitem.h
    numberitemobject.cpp numberitemobject.h
    numbermover.cpp numbermover.h
    origin_matrix.cpp origin_matrix.h
    pch.h
    pos.h
    puzzle_mover.cpp puzzle_mover.h
    resizable_matrix.h
    sizepickerdialog.cpp sizepickerdialog.h
)
target_compile_definitions(slider_puzzle PRIVATE
    QT_DEPRECATED_WARNINGS
)

target_link_libraries(slider_puzzle PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

target_compile_options(slider_puzzle PRIVATE
    -std=c++20
)

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(slider_puzzle PRIVATE
        Qt::Widgets
    )
endif()

if(Debug)
    target_sources(slider_puzzle PUBLIC
        test_astar.cpp
        test_console_board.cpp
        test_edgegraph.cpp
        test_gen.cpp
        test_linemover.cpp
        test_matrixgraph.cpp
        test_numbermover.cpp
        test_optimize_move.cpp
        test_prioorityqueue.cpp
        test_puzzlemover.cpp
        test_search_board.cpp
    )
endif()

install(TARGETS slider_puzzle
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET slider_puzzle
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
