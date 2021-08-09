cmake_minimum_required( VERSION 3.10.2 )

project( test_lib_blockchain
        VERSION 0.1
        DESCRIPTION "Testing blockchain module."
        )

add_executable( blockchain_app_test src/test_blockchain.c )

target_link_libraries( blockchain_app_test
        PRIVATE
        LII::blockchain
        Unity
)

add_test(blockchain_test blockchain_app)
