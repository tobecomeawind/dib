add_executable(main main.c)

add_subdirectory(algs)
add_subdirectory(core)
add_subdirectory(hash)

include_directories(
	${CMAKE_CURRENT_LIST_DIR}/core/
	${CMAKE_CURRENT_LIST_DIR}/core/entity_type
)

target_link_libraries(main
	PRIVATE
		algs
		core
		hash
)

target_include_directories(main
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
		#${CMAKE_CURRENT_LIST_DIR}/core/node
)
