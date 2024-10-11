set(LIBRARY_NAME core)


get_filename_component(PARENT_DIR ${CMAKE_CURRENT_LIST_DIR}/.. ABSOLUTE)

include_directories(
	                ${CMAKE_CURRENT_LIST_DIR}/entity_type
	                ${CMAKE_CURRENT_LIST_DIR}/data
	                ${CMAKE_CURRENT_LIST_DIR}/relation
					${PARENT_DIR}/types
					${PARENT_DIR}/hash
					)

#add_library(${LIBRARY_NAME} "")

add_subdirectory(data)
add_subdirectory(node)
add_subdirectory(relation)

add_library(${LIBRARY_NAME} 
	$<TARGET_OBJECTS:data>
	$<TARGET_OBJECTS:node>
	$<TARGET_OBJECTS:relation>
)



target_link_libraries(${LIBRARY_NAME}
		data
		node
		relation
		m
)


#[[
target_include_directories(${LIBRARY_NAME}
	PUBLIC	
		${CMAKE_CURRENT_LIST_DIR}
		${CMAKE_CURRENT_LIST_DIR}/../types
		${CMAKE_CURRENT_LIST_DIR}/../hash
)
]]

