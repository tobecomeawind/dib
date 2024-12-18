set(LIBRARY_NAME data)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/data.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/data.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
		${CMAKE_CURRENT_LIST_DIR}/../../types
		${CMAKE_CURRENT_LIST_DIR}/../../language_core/tokens
		${CMAKE_CURRENT_LIST_DIR}/../entity_type
)
