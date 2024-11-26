set(LIBRARY_NAME lexer)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/lexer.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/lexer.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC	
		${CMAKE_CURRENT_LIST_DIR}
)
