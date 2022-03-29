cmake_minimum_required(VERSION 3.14)

project(remoteApi LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(TAG_LIB_NAME ${PROJECT_NAME} CACHE INTERNAL "target lib name")

add_subdirectory(meta_libs)
add_subdirectory(src)
#install(TARGETS ${TAG_LIB_NAME} LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
add_subdirectory(test_send_ui)
