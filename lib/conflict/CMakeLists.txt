cmake_minimum_required( VERSION 3.10.2 )

project( conflict_lib
        VERSION 0.1
        DESCRIPTION "Module for managing blochain's conflicts."
        )

add_library(conflict STATIC src/conflict.c)

target_include_directories(conflict
        PUBLIC include
        )

add_library(LII::conflict ALIAS conflict)
