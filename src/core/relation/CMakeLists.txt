set(LIBRARY_NAME relation)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		relation.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/relation.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
