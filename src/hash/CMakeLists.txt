set(LIBRARY_NAME hash)


add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		hash.c
	PUBLIC
	    ${CMAKE_CURRENT_LIST_DIR}/hash.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
