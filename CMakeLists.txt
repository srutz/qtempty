cmake_minimum_required(VERSION 3.16)

project(TableView VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

qt_add_executable(TableView
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    mymodel.h mymodel.cpp
    icons.qrc
)

target_link_libraries(TableView PRIVATE Qt6::Widgets)

qt_finalize_executable(TableView)
