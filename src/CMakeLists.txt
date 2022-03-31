cmake_minimum_required(VERSION 3.14)

project(src)
set(TAG_LIB_NAME remoteApi)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} _SOURCES)
#file(GLOB _SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(${TAG_LIB_NAME} SHARED
    ${_SOURCES}
    )

target_include_directories(${TAG_LIB_NAME} PRIVATE
    ${META_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    )

message("META_INCLUDES = ${META_INCLUDES}")

target_link_directories(${TAG_LIB_NAME} PRIVATE
    ${META_DIRECTORIES}
    ${CMAKE_CURRENT_BINARY_DIR}
    )
message("META_DIRECTORIES = ${META_DIRECTORIES}")

target_link_libraries(${TAG_LIB_NAME} PRIVATE
    ${META_LIBS}
    )
message("META_LIBS = ${META_LIBS}")
target_compile_definitions(${TAG_LIB_NAME} PRIVATE REMOTEAPI_LIBRARY)
#set_target_properties(${TAG_LIB_NAME} PROPERTIES
#        BUILD_WITH_INSTALL_RPATH FALSE
#        LINK_FLAGS "-Wl,-rpath,$ORIGIN/")
