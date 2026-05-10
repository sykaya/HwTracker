cmake_minimum_required(VERSION 3.16)

project(HwTracker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets LinguistTools Network)
find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools Network)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/draggablelabel.cpp
        include/mainwindow.h
        include/draggablelabel.h
        include/includes.h
        src/app.rc
)

set(UI_SOURCES forms/mainwindow.ui)


set(TS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/HwTracker_en_US.ts")

if(WIN32)
    set(APP_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/assets/icon.ico")
    list(APPEND PROJECT_SOURCES ${APP_ICON_RESOURCE})
endif()

qt_add_executable(HwTracker
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${UI_SOURCES}
)

if(EXISTS ${TS_FILES})
    qt_add_translations(HwTracker TS_FILES ${TS_FILES})
endif()

target_link_libraries(HwTracker PRIVATE
    Qt6::Widgets
    Qt6::Network
)

if(WIN32)
    target_link_libraries(HwTracker PRIVATE iphlpapi ws2_32 pdh)
endif()


target_include_directories(HwTracker PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
)

set_target_properties(HwTracker PROPERTIES
    WIN32_EXECUTABLE TRUE
)

qt_finalize_executable(HwTracker)
