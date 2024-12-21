set(LIBRARY_NAME node)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/node.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/node.h
)

include_directories(
	${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)

