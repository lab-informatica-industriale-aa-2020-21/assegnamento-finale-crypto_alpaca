cmake_minimum_required( VERSION 3.10.2)

project( Main_application
         VERSION 1.0
         DESCRIPTION "Developing main application" )

add_executable(application src/main.c)

target_link_libraries(application
    PRIVATE LII::hash
	PRIVATE LII::blockchain
	PRIVATE LII::file_IO
	PRIVATE LII::format_string
    PRIVATE LII::gui
)
