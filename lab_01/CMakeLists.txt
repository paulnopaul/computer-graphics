cmake_minimum_required(VERSION 3.15)
project(lab_01)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH /Users/pavelceklin/Qt/5.14.0/clang_64)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(lab_01
        main.cpp
        mainwindow.cpp mainwindow.h
        drawwindow.ui mainwindow.cpp mainwindow.h)
target_link_libraries(lab_01 Qt5::Widgets)