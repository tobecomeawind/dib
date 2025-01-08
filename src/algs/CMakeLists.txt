set(LIBRARY_NAME algs)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/algs.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/algs.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC		
		${CMAKE_CURRENT_LIST_DIR}
		${CMAKE_CURRENT_LIST_DIR}/../types
		${CMAKE_CURRENT_LIST_DIR}/../language_core/tokens
		${CMAKE_CURRENT_LIST_DIR}/../core/graph
		${CMAKE_CURRENT_LIST_DIR}/../core/entity_type
		${CMAKE_CURRENT_LIST_DIR}/../core/node
		${CMAKE_CURRENT_LIST_DIR}/../core/data
		${CMAKE_CURRENT_LIST_DIR}/../core/relation
)
