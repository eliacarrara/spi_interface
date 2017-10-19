project(spi_inteface)
cmake_minimum_required (VERSION 3.2.2)

# directory settings 
set(SRC_DIR    			${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(CMAKE_CURRENT_BINARY_DIR  	${CMAKE_CURRENT_SOURCE_DIR}/build/)
set(EXECUTABLE_OUTPUT_PATH      ${CMAKE_CURRENT_SOURCE_DIR}/out/)

# include directory
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${SRC_DIR})

# compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -std=c++17 -fPIC")

# collect files
set(files 	src/main.cpp
                src/spi_interface.h src/spi_interface.cpp)

# build application
add_executable(spi_inteface ${files})
