cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

project(AIRPLANE C CXX)

set(Header_Files
	"airplane.h"
	"catch.hpp"
	"glider_math.h"
	"nrutil.h"
	)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
	"airplane.cpp"
	"glider_math.c"
	"main.cpp"
	"nrutil.c"
	)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
	${Header_Files}
	${Source_Files}
	)

add_executable(${PROJECT_NAME} ${ALL_FILES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lm")
