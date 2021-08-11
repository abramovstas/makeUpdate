cmake_minimum_required(VERSION 3.5)

project(makeUpdate LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)

add_executable(makeUpdate
  main.cpp
  mainwidget.cpp
  mainwidget.h
  mainwidget.ui
  job.cpp
  job.h
)

target_link_libraries(makeUpdate Qt5::Core Qt5::Gui Qt5::Widgets)
