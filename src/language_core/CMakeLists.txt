cmake_minimum_required(VERSION 3.28)

project(cli)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_VERBOSE_MAKEFILE ON) # to check debuf info

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../algs 
	             ${CMAKE_CURRENT_BINARY_DIR}/algs)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../hash
	             ${CMAKE_CURRENT_BINARY_DIR}/hash)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../core
                 ${CMAKE_CURRENT_BINARY_DIR}/core)

add_subdirectory(tokens)
add_subdirectory(lexer)
add_subdirectory(parser)

add_executable(${PROJECT_NAME} main.c)


target_link_libraries(${PROJECT_NAME}
	PUBLIC		
		hash
		core
		
		lexer	
		tokens
		parser
		algs
		
		m
)
