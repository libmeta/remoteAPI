cmake_minimum_required(VERSION 3.14)

project(remoteApi LANGUAGES CXX)

ENABLE_LANGUAGE(ASM)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/meta_libs/cmake")
#add_compile_options(-DANDROID_STL=c++_static)
include(InitSystemName)
include(CompilerWarnings)
include(OptionDefinition)

add_compile_definitions(WEBRTC_ABSL_MUTEX)
add_compile_definitions(RTC_DISABLE_LOGGING)
if(POSIX)
    add_compile_definitions(WEBRTC_LINUX)
    add_compile_definitions(WEBRTC_POSIX)
endif()

add_option_on_definition(HAVE_FFMPEG)
add_option_on_definition(HAVE_WEBRTC)
add_option_on_definition(HAVE_SIGSLOT)
add_option_on_definition(HAVE_MARL)

message("=>start add_subdirectory(meta_libs)")
add_subdirectory(meta_libs)
message("=>end add_subdirectory(meta_libs)")

message("=>start add_subdirectory(src)")
add_subdirectory(src)
message("=>end add_subdirectory(src)")

set(NEED_DEBUG_UI_TESTS true)
if(${NEED_DEBUG_UI_TESTS})
    message("=>start add_subdirectory(test_remote_ui)")
    add_subdirectory(test_remote_ui)
    message("=>end add_subdirectory(test_remote_ui)")
endif()

#install(TARGETS ${TAG_LIB_NAME} LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
