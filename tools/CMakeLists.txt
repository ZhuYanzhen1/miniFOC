cmake_minimum_required(VERSION 3.5)

project(miniFOC_Monitor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(app_RC app.rc)

set_property(SOURCE app.rc APPEND PROPERTY
        OBJECT_DEPENDS ${PROJECT_SOURCE_DIR}/icon.ico
        )

find_package(Qt5 COMPONENTS Widgets SerialPort PrintSupport REQUIRED)

add_executable(miniFOC_Monitor WIN32 ${app_RC} main.cpp mainwindow.cpp mainwindow.h mainwindow.ui
                mdtp/decrypt.cpp mdtp/encrypt.cpp qcustomplot.h qcustomplot.cpp)

target_link_libraries(miniFOC_Monitor PRIVATE Qt5::Widgets Qt5::SerialPort Qt5::PrintSupport)
