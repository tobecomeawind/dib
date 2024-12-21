cmake_minimum_required(VERSION 3.10)

project(main)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)


#[[
	PUBLIC    -      for me and for everyone who depends on me
	INTERFACE - not  for me, but for everyone who depends on me
	PRIVATE   - only for me
]]
