set(LIBRARY_NAME files)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/files.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/files.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC	
		${CMAKE_CURRENT_LIST_DIR}	
)
