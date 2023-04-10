add_library(suffix_array STATIC suffix_array.c)
add_executable(suffix_array_example suffix_array_example.c)
target_include_directories(suffix_array PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_link_libraries(suffix_array_example PUBLIC suffix_array)
