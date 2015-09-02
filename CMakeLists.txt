
project(spellcorrection C CXX)

set(CXX_FLAGS
	-Wall
	-g
	-std=c++11
	-Wno-deprecated
   )
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(INCLUDE_LIST
	${PROJECT_SOURCE_DIR}/inc
	${PROJECT_SOURCE_DIR}/inc/net
	${PROJECT_SOURCE_DIR}/inc/threadpool
	)
include_directories(${INCLUDE_LIST})

set(CMAKE_CXX_COMPILER "g++")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(src)


