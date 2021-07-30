cmake_minimum_required( VERSION 3.10.2 )

project( block_lib
        VERSION 0.1
        DESCRIPTION "Module that returns a block to be mined."
        )

add_library(block STATIC src/block.c)

target_include_directories(block
        PUBLIC include
        )

target_link_libraries(block
        PUBLIC LII::transaction
        )

add_library(LII::block ALIAS block)
