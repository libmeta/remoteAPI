cmake_minimum_required(VERSION 3.14)

project(remoteApi LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/meta_libs/cmake")

include(CompilerWarnings)

message("=>start add_subdirectory(meta_libs)")
add_subdirectory(meta_libs)
message("=>end add_subdirectory(meta_libs)")

message("=>start add_subdirectory(src)")
add_subdirectory(src)
message("=>end add_subdirectory(src)")

set(NEED_DEBUG_TESTS true)
if(${NEED_DEBUG_TESTS})
message("=>start add_subdirectory(test_remote_ui)")
add_subdirectory(test_remote_ui)
message("=>end add_subdirectory(test_remote_ui)")
endif()
#install(TARGETS ${TAG_LIB_NAME} LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
