cmake_minimum_required(VERSION 3.14)

project(remoteApi LANGUAGES CXX)
set(TAG_LIB_NAME remoteApi)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(meta_libs)

aux_source_directory(push PUSH)
add_library(${TAG_LIB_NAME} SHARED
  ${PUSH}
  remoteapi.cpp
  remoteapi.hpp
)

target_include_directories(${TAG_LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TAG_LIB_NAME} PRIVATE ${META_LIBS_NAME})
target_compile_definitions(${TAG_LIB_NAME} PRIVATE REMOTEAPI_LIBRARY)
#install(TARGETS ${TAG_LIB_NAME} LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
#add_executable(test_send ${CMAKE_CURRENT_SOURCE_DIR}/test/test_send.cpp)
#target_link_libraries(test_send PRIVATE ${TAG_LIB_NAME} )

#add_subdirectory(test_send)
add_subdirectory(test_send_ui)
