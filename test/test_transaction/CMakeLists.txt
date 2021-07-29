cmake_minimum_required( VERSION 3.10.2 )

project( test_lib_transaction
        VERSION 0.1
        DESCRIPTION "Testing Transaction module."
        )

add_executable( transaction_app_test src/test_transaction.c )

target_link_libraries( transaction_app_test
        PRIVATE
        LII::transaction
        Unity
)

add_test(transaction_test transaction_app)
