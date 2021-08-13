cmake_minimum_required( VERSION 3.10.2 )

project(gui<-lib
        VERSION 0.1
        DESCRIPTION "Grafic user interface."
        )

add_library(gui STATIC src/gui.c)

target_include_directories(gui
        PUBLIC include
        )

target_link_libraries(gui
        PUBLIC LII::blockchain
        )

add_library(LII::gui ALIAS gui)
