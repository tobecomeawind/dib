set(LIBRARY_NAME entity_type)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/entity_type.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/entity_type.h
)


target_include_directories(${LIBRARY_NAME}
	PUBLIC
		${hash_SOURCE_DIR}	
		${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${LIBRARY_NAME}
	hash
)
