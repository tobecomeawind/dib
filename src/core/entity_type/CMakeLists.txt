set(LIBRARY_NAME entity_type)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/entity_type.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
