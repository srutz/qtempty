cmake_minimum_required(VERSION 3.5)
project(qtapp VERSION 1.0 LANGUAGES CXX)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(PROJECT_SOURCES
    main.cpp
)
qt_add_executable(qtapp MANUAL_FINALIZATION ${PROJECT_SOURCES})
target_link_libraries(qtapp PRIVATE Qt6::Widgets)
qt_finalize_executable(qtapp)
