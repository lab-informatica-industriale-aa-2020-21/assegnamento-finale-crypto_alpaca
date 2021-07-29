cmake_minimum_required( VERSION 3.10.2 )

project( test_lib_chain
        VERSION 0.1
        DESCRIPTION "Testing chain module."
        )

add_executable( chain_app_test src/test_chain.c )

target_link_libraries( chain_app_test
        PRIVATE
        LII::chain
        Unity
)

add_test(chain_test chain_app)
