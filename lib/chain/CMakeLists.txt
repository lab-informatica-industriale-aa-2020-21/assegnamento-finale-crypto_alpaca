cmake_minimum_required( VERSION 3.10.2 )

project( chain_lib
        VERSION 0.1
        DESCRIPTION "Module that returns the blockchain as a list of mined blocks."
        )

add_library(chain STATIC src/chain.c)

target_include_directories(chain
        PUBLIC include
        )

add_library(LII::chain ALIAS chain)
