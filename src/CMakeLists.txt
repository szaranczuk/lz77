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

add_executable(lz77_compress lz77/lz77_compress.c)
target_include_directories(lz77_compress PUBLIC "${PROJECT_SOURCE_DIR}/include/")
target_link_libraries(lz77_compress PUBLIC lz77_block)


add_executable(lz77_decompress lz77/lz77_decompress.c)
target_include_directories(lz77_decompress PUBLIC "${PROJECT_SOURCE_DIR}/include/")
target_link_libraries(lz77_decompress PUBLIC lz77_block)

set_target_properties(lz77_compress lz77_decompress PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")