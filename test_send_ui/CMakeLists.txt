cmake_minimum_required(VERSION 3.5)

project(test_send_ui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    dialog.cpp
    dialog.hpp
    dialog.ui
    )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(test_send_ui
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET test_send_ui APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(test_send_ui SHARED
            ${PROJECT_SOURCES}
            )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(test_send_ui
            ${PROJECT_SOURCES}
            )
    endif()
endif()

target_link_libraries(test_send_ui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(test_send_ui PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.test_remote.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(test_send_ui)
endif()



macro(add_dynamic_lib LIB_NAME LIB_PATH)
    add_library(${LIB_NAME} SHARED IMPORTED)
    set_target_properties(${LIB_NAME}  PROPERTIES IMPORTED_LOCATION ${LIB_PATH})
    list(APPEND _LINK_LIBS ${LIB_NAME})
endmacro(add_dynamic_lib)

if(ANDROID)
    set(_ANDROID_LIBRARY_DIR                    ${CMAKE_CURRENT_BINARY_DIR}/android-build/libs/arm64-v8a)
    file(GLOB META_SO                           ${CMAKE_BINARY_DIR}/meta_libs/*.so)
    file(GLOB REMOTE_API_SO                     ${CMAKE_BINARY_DIR}/src/*.so)
    file(COPY ${META_SO} DESTINATION            ${_ANDROID_LIBRARY_DIR} FOLLOW_SYMLINK_CHAIN)
    file(COPY ${REMOTE_API_SO} DESTINATION      ${_ANDROID_LIBRARY_DIR} FOLLOW_SYMLINK_CHAIN)

    add_dynamic_lib(_remoteApi                  ${CMAKE_BINARY_DIR}/src/libremoteApi.so)
    add_dynamic_lib(srt                         ${CMAKE_BINARY_DIR}/meta_libs/libsrt.so)
    add_dynamic_lib(ssl                         ${CMAKE_BINARY_DIR}/meta_libs/libssl.so)
    add_dynamic_lib(crypto                      ${CMAKE_BINARY_DIR}/meta_libs/libcrypto.so)
    add_dynamic_lib(avcodec                     ${CMAKE_BINARY_DIR}/meta_libs/libavcodec.so)
    add_dynamic_lib(avfilter                    ${CMAKE_BINARY_DIR}/meta_libs/libavfilter.so)
    add_dynamic_lib(avformat                    ${CMAKE_BINARY_DIR}/meta_libs/libavformat.so)
    add_dynamic_lib(avutil                      ${CMAKE_BINARY_DIR}/meta_libs/libavutil.so)
    add_dynamic_lib(swresample                  ${CMAKE_BINARY_DIR}/meta_libs/libswresample.so)
    add_dynamic_lib(swscale                     ${CMAKE_BINARY_DIR}/meta_libs/libswscale.so)

    include_directories(test_send_ui PRIVATE ${CMAKE_SOURCE_DIR}/include)
    message("_LINK_LIBS = ${_LINK_LIBS}")
    target_link_libraries(test_send_ui PRIVATE
        ${_LINK_LIBS}
        )

endif(ANDROID)
