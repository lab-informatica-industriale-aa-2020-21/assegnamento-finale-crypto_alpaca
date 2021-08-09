cmake_minimum_required( VERSION 3.10.2 )

project( blockchain_lib
        VERSION 0.1
        DESCRIPTION "Chains, Blocks and Transactions management."
        )

add_library(file_IO STATIC src/blockchain.c)

target_include_directories(blockchain
        PUBLIC include
        )

target_link_libraries(blockchain
	PUBLIC LII::hash
	PUBLIC LII::format_string
        )

add_library(LII::blockchain ALIAS blockchain)
