cmake_minimum_required(VERSION 3.20)
project(Bejeweled)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Bejeweled
        src/main.cpp
        src/db/Player.cpp src/db/Player.h
        src/db/db.cpp src/db/db.h
        src/Item.cpp src/Item.h
        src/GameJudge.cpp src/GameJudge.h src/MapBuild.cpp src/MapBuild.h src/DataProcess.cpp src/DataProcess.h)

target_link_libraries(Bejeweled
        sqlite3
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets)

