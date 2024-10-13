set(LIBRARY_NAME tokens)


add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		tokens.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/tokens.h
)


target_include_directories(${LIBRARY_NAME}
	PUBLIC	
		${CMAKE_CURRENT_LIST_DIR}
)
