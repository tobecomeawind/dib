set(LIBRARY_NAME parser)

add_library(${LIBRARY_NAME} "")


target_sources(${LIBRARY_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/parser.c
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/parser.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC
		${tokens_SOURCE_DIR}
		${lexer_SOURCE_DIR}
		${CMAKE_CURRENT_LIST_DIR}
)


target_link_libraries(${LIBRARY_NAME}
	lexer
	core	
)



#[[
target_include_directories(${LIBRARY_NAME}	
	PUBLIC	
		${PARSER_PATH}
)
]]
