cmake_minimum_required(VERSION 3.0)
project(gad)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS "program_options")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
enable_testing()

add_subdirectory(third_party)
add_subdirectory(src)
add_subdirectory(test)
