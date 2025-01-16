set(LIBRARY_NAME language_core)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/language_core.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/language_core.h
)


#[[
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../algs 
	             ${CMAKE_CURRENT_BINARY_DIR}/algs)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../hash
	             ${CMAKE_CURRENT_BINARY_DIR}/hash)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../core
                 ${CMAKE_CURRENT_BINARY_DIR}/core)


]]

target_include_directories(${LIBRARY_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}	
)

add_subdirectory(parser)
add_subdirectory(tokens)
add_subdirectory(lexer)

target_link_libraries(${LIBRARY_NAME}
	PUBLIC		
		hash
		core
		
		lexer	
		tokens
		parser
		algs
		
		m
)
