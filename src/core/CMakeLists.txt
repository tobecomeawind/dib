set(LIBRARY_NAME core)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_LIST_DIR}/.. ABSOLUTE)

include_directories(
					${CMAKE_CURRENT_LIST_DIR}/node
					${CMAKE_CURRENT_LIST_DIR}/storage
					${CMAKE_CURRENT_LIST_DIR}/storage/serialization
					${CMAKE_CURRENT_LIST_DIR}/storage/deserialization
					${CMAKE_CURRENT_LIST_DIR}/entity_type
					${CMAKE_CURRENT_LIST_DIR}/data
					${CMAKE_CURRENT_LIST_DIR}/relation
					${PARENT_DIR}/language_core/tokens
					${PARENT_DIR}/types
					${PARENT_DIR}/hash
					)

#add_library(${LIBRARY_NAME} "")

add_subdirectory(entity_type)
add_subdirectory(storage)
add_subdirectory(relation)
add_subdirectory(data)
add_subdirectory(node)


#add_library(${LIBRARY_NAME} "")


add_library(${LIBRARY_NAME} 
	$<TARGET_OBJECTS:deserialization>
	$<TARGET_OBJECTS:serialization>
	$<TARGET_OBJECTS:data>
	$<TARGET_OBJECTS:node>
	$<TARGET_OBJECTS:relation>
)



target_link_libraries(${LIBRARY_NAME}
		entity_type		
		deserialization
		serialization
		data
		node
		relation
		m

)

