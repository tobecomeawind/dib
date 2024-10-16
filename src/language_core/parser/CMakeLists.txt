set(LIBRARY_NAME parser)


add_library(${LIBRARY_NAME} "")


target_sources(${LIBRARY_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/parser.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/parser.h
)

target_include_directories(${LIBRARY_NAME}	
	PUBLIC	
		${CMAKE_CURRENT_LIST_DIR}
)
