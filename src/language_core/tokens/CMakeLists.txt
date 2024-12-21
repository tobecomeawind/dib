set(LIBRARY_NAME tokens)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/tokens.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/tokens.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC
		${algs_SOURCE_DIR}	
		${CMAKE_CURRENT_LIST_DIR}
)


target_link_libraries(${LIBRARY_NAME}
	algs
)
