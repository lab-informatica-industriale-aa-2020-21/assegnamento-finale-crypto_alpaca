cmake_minimum_required( VERSION 3.10.2 )

project(format_string_lib
        VERSION 0.1
        DESCRIPTION "Data format with strings"
        )

add_library(format_string STATIC src/format_string.c)

target_include_directories(format_string
        PUBLIC include
        )

target_link_libraries(format_string
	PUBLIC LII::transaction
        PUBLIC LII::block
        )

add_library(LII::format_string ALIAS format_string)
