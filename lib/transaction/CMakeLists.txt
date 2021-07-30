cmake_minimum_required( VERSION 3.10.2 )

project( hash_lib
        VERSION 0.1
        DESCRIPTION "Module for managing electronic transaction lists."
        )

add_library(transaction STATIC src/transaction.c)

target_include_directories(transaction
        PUBLIC include
        )

target_link_libraries(transaction
	PUBLIC LII::hash
	)

add_library(LII::transaction ALIAS transaction)
