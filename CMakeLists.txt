cmake_minimum_required(VERSION 3.5)

project(mybiguint)


enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

set(
	
	SOURCES 
	test_mybiguint.cpp
)

set(
	
	HEADERS 
	mybiguint.h
)


set(
	CMAKE_CXX_STANDARD 11
)

set(
	CMAKE_CXX_STANDARD_REQUIRED on
)

set(
	CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror"
)

add_executable(

	test_mybiguint 
	${SOURCES} ${HEADERS}
)

target_link_libraries(
	
	test_mybiguint PRIVATE
	gtest gtest_main
	pthread
)

