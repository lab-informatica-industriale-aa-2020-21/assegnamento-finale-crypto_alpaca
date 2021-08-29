cmake_minimum_required( VERSION 3.10.2 )

project( hash_lib
        VERSION 0.2
        DESCRIPTION "Hashing library based on SHA-256"
        )

add_library(hash STATIC src/hash.c)

target_include_directories(hash
        PUBLIC include
        )

target_link_libraries(hash
	PUBLIC m
	PUBLIC LII::format_string
	)

add_library(LII::hash ALIAS hash)
