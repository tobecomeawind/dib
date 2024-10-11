set(LIBRARY_NAME data)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		data.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/data.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
