cmake_minimum_required(VERSION 3.14)

project(remoteApi LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(meta_libs)

add_library(${PROJECT_NAME} SHARED
  remoteapi.cpp
  remoteapi.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE meta_libs)
target_compile_definitions(${PROJECT_NAME} PRIVATE REMOTEAPI_LIBRARY)
