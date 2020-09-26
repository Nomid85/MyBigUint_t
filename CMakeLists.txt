cmake_minimum_required(VERSION 3.16)

project(mybiguint)

find_library(CMATH_LIBRARY cmath)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_executable(mybiguint mybiguint.cpp)