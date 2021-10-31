cmake_minimum_required(VERSION 3.5)

project(TestTask VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        src/Figure/Point/point.cpp
        src/Figure/Point/point.h
        src/Figure/figure.cpp
        src/Figure/figure.h
        src/FigureFrame/figureframe.h
        src/FigureFrame/figureframe.cpp
        src/Interface/mainwindow.cpp
        src/Interface/mainwindow.h
        src/Interface/mainwindow.ui
        src/main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TestTask
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TestTask APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TestTask SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TestTask
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TestTask PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(TestTask PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TestTask)
endif()

#TESTS

set (gtest_force_shared_crt ON CACHE BOOL "MSVC defaults to shared CRT" FORCE)
add_subdirectory(googletest)
target_compile_definitions(gtest
  PUBLIC
    GTEST_LANG_CXX17
    GTEST_HAS_TR1_TUPLE=0
)

set (TEST_SOURCES tests/figuretest.cpp src/Figure/figure.cpp src/Figure/Point/point.cpp) 
add_executable(tests)
target_sources(tests
  PRIVATE
    ${TEST_SOURCES}
)

set_target_properties(tests PROPERTIES COMPILE_FLAGS "${cxx_strict}")
target_link_libraries(tests gtest_main Qt${QT_VERSION_MAJOR}::Core)
enable_testing()
include(GoogleTest)
gtest_add_tests(TARGET tests SOURCES ${TEST_SOURCES})
