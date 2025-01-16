set(LIBRARY_NAME language_core)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/language_core.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/language_core.h
)


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
