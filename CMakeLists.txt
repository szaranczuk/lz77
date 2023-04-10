cmake_minimum_required(VERSION 3.10)

project(LZ77 VERSION 1.0 LANGUAGES C)

add_library(suffix_array STATIC Sources/suffix_array.c)

add_executable(suffix_array_example Sources/suffix_array_example.c)

target_include_directories(suffix_array PUBLIC Include/)
target_compile_features(suffix_array PUBLIC c_std_11)

target_link_libraries(suffix_array_example PUBLIC suffix_array)
