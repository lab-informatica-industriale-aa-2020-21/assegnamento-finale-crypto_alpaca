cmake_minimum_required( VERSION 3.10.2 )

project( test_lib_hash
        VERSION 0.2
        DESCRIPTION "Testing the hashing function."
        )

add_executable( hash_app_test src/hash.c )

target_link_libraries( modulo_app_test
        PRIVATE
        LII::hash
        Unity
)

add_test(hash_test hash_app)
