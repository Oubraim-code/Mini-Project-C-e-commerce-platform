# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(EcommercePlatform VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the directory for header files
include_directories(include)

# Find all source files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Define the executable and the files needed to build it
add_executable(EcommerceApp main.cpp ${SOURCES})
