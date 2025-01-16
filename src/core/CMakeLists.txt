set(LIBRARY_NAME core)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_LIST_DIR}/.. ABSOLUTE)


add_subdirectory(entity_type)
add_subdirectory(storage)
add_subdirectory(relation)
add_subdirectory(data)
add_subdirectory(node)
add_subdirectory(graph)


add_library(${LIBRARY_NAME} 
	$<TARGET_OBJECTS:files>
	$<TARGET_OBJECTS:deserialization>
	$<TARGET_OBJECTS:serialization>
	$<TARGET_OBJECTS:data>
	$<TARGET_OBJECTS:node>
	$<TARGET_OBJECTS:relation>
	$<TARGET_OBJECTS:graph>
)


target_link_libraries(${LIBRARY_NAME}
		entity_type		
		files
		deserialization
		serialization
		data
		node
		relation
		graph
		m

)

