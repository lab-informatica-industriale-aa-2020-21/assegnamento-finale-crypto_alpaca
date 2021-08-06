cmake_minimum_required( VERSION 3.10.2 )

project( test_lib_format_string
        VERSION 0.1
        DESCRIPTION "Testing format_string module."
        )

add_executable( format_string_app_test src/test_format_string.c )

target_link_libraries( format_string_app_test
        PRIVATE
        LII::format_string
        Unity
)

add_test(format_string_test format_string_app)
