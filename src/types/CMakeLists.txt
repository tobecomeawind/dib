set(LIBRARY_NAME types)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PUBLIC
	    ${CMAKE_CURRENT_LIST_DIR}/types.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
