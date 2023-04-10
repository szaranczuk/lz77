cmake_minimum_required(VERSION 3.20)

project(LZ77 VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)

add_library(suffix_array STATIC src/suffix_array.c)

add_executable(suffix_array_example src/suffix_array_example.c)

target_include_directories(suffix_array PUBLIC include/)

target_link_libraries(suffix_array_example PUBLIC suffix_array)

#Tests
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    add_subdirectory(tests)
endif()