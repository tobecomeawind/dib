cmake_minimum_required(VERSION 3.10)

project(main)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_VERBOSE_MAKEFILE ON) # to check debuf info

add_subdirectory(src)


#[[
	PUBLIC    -      for me and for everyone who depends on me
	INTERFACE - not  for me, but for everyone who depends on me
	PRIVATE   - only for me
]]
