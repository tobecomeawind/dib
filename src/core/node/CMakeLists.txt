set(LIBRARY_NAME node)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		node.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/node.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
