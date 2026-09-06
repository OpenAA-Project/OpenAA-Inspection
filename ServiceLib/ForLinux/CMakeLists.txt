# CMakeLists.txt generated from ForLinux.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(ForLinux LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(WIN32)
    add_compile_definitions(WIN32 _WINDOWS)
endif()

if(UNIX)
    # Dead code stripping (remove unused functions/data)
    add_compile_options(-ffunction-sections -fdata-sections)
    add_link_options("-Wl,--gc-sections")

    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        # Linux / Raspberry Pi specific settings
    endif()
endif()

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

set(PROJECT_SOURCES
    "XForLinux.cpp"
    "ForLinux.cpp"
)

set(PROJECT_HEADERS
    "../../Open/XForLinux.h"
    "forlinux_global.h"
    "ForLinux.h"
)


# Define the target
add_library(${PROJECT_NAME} STATIC
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
)

# === Configuration-specific sources ===
if(DEFINED PROJECT_SOURCES_DEBUG)
    target_sources(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:${PROJECT_SOURCES_DEBUG}>)
endif()

if(DEFINED PROJECT_SOURCES_RELEASE)
    target_sources(${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:${PROJECT_SOURCES_RELEASE}>)
endif()

# === Configuration-specific settings ===

if(MSVC)
endif()

# --- End of Debug ---

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "../../Open"
    >
)

if(MSVC)
endif()

# --- End of Release ---

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
)

# === Additional Custom Settings ===

target_include_directories(${PROJECT_NAME} PRIVATE
    "/home/megatrade/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/OpenXLSX"
    "/home/megatrade/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/build/OpenXLSX/"
    "x64/Release/qt"
    "x64/Release/qt/uic"
)

target_link_directories(${PROJECT_NAME} PRIVATE
    "/usr/local/lib/"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    "libpng16.so"
)

