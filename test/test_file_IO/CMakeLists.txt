cmake_minimum_required( VERSION 3.10.2 )

project( test_lib_file_IO
        VERSION 0.1
        DESCRIPTION "Testing file_IO module."
        )

add_executable( file_IO_app_test src/test_file_IO.c )

target_link_libraries( file_IO_app_test
        PRIVATE
        LII::file_IO
        Unity
)

add_test(file_IO_test file_IO_app)
