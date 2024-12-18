set(LIBRARY_NAME hash)


add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/hash.c
	PUBLIC
	    ${CMAKE_CURRENT_LIST_DIR}/hash.h
)


target_include_directories(${LIBRARY_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)


target_link_libraries(${LIBRARY_NAME}
	core
)

