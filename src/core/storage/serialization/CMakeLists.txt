set(LIBRARY_NAME serialization)


add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/serialization.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/serialization.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)



