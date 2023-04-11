add_library(utils STATIC utils/utils.c)
target_include_directories(utils PUBLIC "${PROJECT_SOURCE_DIR}/include/")

add_library(suffix_array STATIC suffix_array/suffix_array.c suffix_array/lcp_array.c suffix_array/lpf_array.c)
target_link_libraries(suffix_array PUBLIC utils)
add_executable(suffix_array_example suffix_array/suffix_array_example.c)
target_include_directories(suffix_array PUBLIC "${PROJECT_SOURCE_DIR}/include/")
target_link_libraries(suffix_array_example PUBLIC suffix_array utils)

add_library(list STATIC list/array_list.c)
target_include_directories(list PUBLIC "${PROJECT_SOURCE_DIR}/include/")
target_link_libraries(list PUBLIC utils)

add_library(lz77_block STATIC lz77/lz77_block.c)
target_include_directories(lz77_block PUBLIC "${PROJECT_SOURCE_DIR}/include/")
target_link_libraries(lz77_block PUBLIC suffix_array list utils)
