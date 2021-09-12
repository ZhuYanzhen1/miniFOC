cmake_minimum_required(VERSION 3.5)

project(monitor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(app_WINRC app_win32.rc)

set_property(SOURCE app_win32.rc APPEND PROPERTY
        OBJECT_DEPENDS ${PROJECT_SOURCE_DIR}/icon.ico
        )

find_package(Qt5 COMPONENTS Widgets SerialPort PrintSupport REQUIRED)

add_executable(monitor WIN32 ${app_WINRC} main.cpp mainwindow.cpp mainwindow.h mainwindow.ui
                mdtp/decrypt.cpp mdtp/encrypt.cpp qcustomplot.h qcustomplot.cpp)

target_link_libraries(monitor PRIVATE Qt5::Widgets Qt5::SerialPort Qt5::PrintSupport)
