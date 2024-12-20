cmake_minimum_required(VERSION 3.28)

project(cli)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_VERBOSE_MAKEFILE ON)

#[[
include_directories( 
				   	${CMAKE_CURRENT_LIST_DIR}/tokens
				   	${CMAKE_CURRENT_LIST_DIR}/../algs
					${CMAKE_CURRENT_LIST_DIR}/../hash
	                ${CMAKE_CURRENT_LIST_DIR}/../types 
	                ${CMAKE_CURRENT_LIST_DIR}/lexer
	                ${CMAKE_CURRENT_LIST_DIR}/parser
)
]]

#[[ Building Libraries ]] 



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

#[[
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../core/data
	             ${CMAKE_CURRENT_BINARY_DIR}/data)
			 
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../core/relation
	             ${CMAKE_CURRENT_BINARY_DIR}/relation)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../core/node
	             ${CMAKE_CURRENT_BINARY_DIR}/node)

		node
		data
		hash
		relation
		m
)
]]
