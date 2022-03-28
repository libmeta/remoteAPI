cmake_minimum_required(VERSION 3.14)

project(test_send)
add_executable(${PROJECT_NAME} test_send.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${TAG_LIB_NAME})

