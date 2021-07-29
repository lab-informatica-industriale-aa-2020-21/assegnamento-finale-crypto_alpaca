cmake_minimum_required( VERSION 3.10.2 )

project( test_lib_block
        VERSION 0.1
        DESCRIPTION "Testing block module."
        )

add_executable( block_app_test src/test_block.c )

target_link_libraries( block_app_test
        PRIVATE
        LII::block
        Unity
)

add_test(block_test block_app)
