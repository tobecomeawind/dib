set(LIBRARY_NAME relation)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/relation.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/relation.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC
        ${hash_SOURCE_DIR}
		${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${LIBRARY_NAME}
	hash	
)
