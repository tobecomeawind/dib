cmake_minimum_required(VERSION 3.28)


project(cli)

set(CMAKE_BUILD_TYPE Debug)


include_directories(${CMAKE_CURRENT_LIST_DIR}/../algs
	                ${CMAKE_CURRENT_LIST_DIR}/../types
	                ${CMAKE_CURRENT_LIST_DIR}/tokens
	                ${CMAKE_CURRENT_LIST_DIR}/lexer
	                ${CMAKE_CURRENT_LIST_DIR}/parser
)


add_subdirectory(tokens)
add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../algs build)

add_executable(${PROJECT_NAME} main.c)


target_link_libraries(${PROJECT_NAME}
	PUBLIC
		lexer	
		tokens
		algs
		parser
)
