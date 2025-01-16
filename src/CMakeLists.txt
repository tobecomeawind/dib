add_executable(main main.c)

add_subdirectory(algs)
add_subdirectory(core)
add_subdirectory(hash)
add_subdirectory(language_core)

target_link_libraries(main
	PRIVATE
		algs
		core
		hash
		language_core
)

target_include_directories(main
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
