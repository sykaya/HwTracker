cmake_minimum_required(VERSION 3.16)

project(HwTracker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Network)

set(TS_FILES HwTracker_en_US.ts)
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        DraggableLabel.h
        includes.h
        mainwindow.ui
        app.rc
        DraggableLabel.cpp
        ${TS_FILES}
)


if(WIN32)
    set(APP_ICON_RESOURCE "assets/icoo.ico")
    list(APPEND PROJECT_SOURCES ${APP_ICON_RESOURCE})
endif()


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(HwTracker
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        app.rc
        assets/icoo.ico
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(HwTracker SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(HwTracker
            ${PROJECT_SOURCES}
        )
    endif()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(HwTracker PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

if(WIN32)
    target_link_libraries(HwTracker PRIVATE
        iphlpapi
        ws2_32
        pdh
    )
endif()

target_include_directories(HwTracker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.HwTracker)
endif()

set_target_properties(HwTracker PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS HwTracker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(HwTracker)
endif()
