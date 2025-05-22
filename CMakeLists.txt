cmake_minimum_required(VERSION 3.16)
project(Notatnik)

set(CMAKE_CXX_STANDARD 17)

# Włącz MOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Qt
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/mingw_64/lib/cmake")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(Notatnik
        main.cpp
        src/MainWindow.cpp
        include/MainWindow.h
)

# Wymuś automoc na pliku nagłówkowym
set_source_files_properties(include/MainWindow.h PROPERTIES SKIP_AUTOMOC OFF)

# Ścieżka do nagłówków
target_include_directories(Notatnik PRIVATE include)

target_link_libraries(Notatnik
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)
