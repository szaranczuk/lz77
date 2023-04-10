cmake_minimum_required(VERSION 3.20)

project(LZ77 VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)

add_subdirectory(src)


#Tests
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    add_subdirectory(tests)
endif()