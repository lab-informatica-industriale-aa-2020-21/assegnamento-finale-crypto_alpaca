cmake_minimum_required( VERSION 3.10.2 )

project( file_IO_lib
        VERSION 0.1
        DESCRIPTION "Data format with strings, R/W text files."
        )

add_library(file_IO STATIC src/file_IO.c)

target_include_directories(file_IO
        PUBLIC include
        )

target_link_libraries(file_IO
	PUBLIC LII::blockchain
	PUBLIC LII::format_string
        PUBLIC LII::hash
        )

add_library(LII::file_IO ALIAS file_IO)
