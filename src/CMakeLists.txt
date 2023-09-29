add_library(diskCacheEnablerVR MODULE diskcache.cpp)

target_include_directories(diskCacheEnablerVR PRIVATE ${CMAKE_SOURCE_DIR}/deps/f4sevr/f4sevr ${CMAKE_SOURCE_DIR}/deps/f4sevr/common)
