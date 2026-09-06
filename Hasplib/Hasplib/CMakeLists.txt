# CMakeLists.txt generated from Hasplib.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(Hasplib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(WIN32)
    add_compile_definitions(WIN32 _WINDOWS)
endif()

if(UNIX)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        # Linux / Raspberry Pi specific settings
    endif()
endif()

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Sql Network Core5Compat Xml Gui Widgets)

set(PROJECT_SOURCES
    "hasplib.cpp"
)

set(PROJECT_HEADERS
    "../../Open/hasp_hl.h"
    "hasplib.h"
    "hasp_vcode.h"
    "hasplib_global.h"
)


# Define the target
add_library(${PROJECT_NAME} STATIC
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
)

# === Configuration-specific settings ===

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Debug"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Debug"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Debug"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "./GeneratedFiles/$(Configuration)"
        "./GeneratedFiles/"
        "../../Open"
        "./GeneratedFiles"
    >
)

if(MSVC)
endif()

# --- End of Debug ---

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "./GeneratedFiles/$(Configuration)"
        "./GeneratedFiles/"
        "$(OpenAAUseLibrary)/HASP/Sentinel"
        "../../Open"
        "./GeneratedFiles"
    >
)

if(MSVC)
endif()

# --- End of Release ---

if(MSVC)
endif()

# --- End of Template ---

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Sql
    Qt6::Network
    Qt6::Core5Compat
    Qt6::Xml
    Qt6::Gui
    Qt6::Widgets
)


# =========================================================================
# WARNING: The following MSBuild macros were not resolved during conversion:
#   $(OpenAAUseLibrary)
# Please define them in CMake or add them to the macro replacements list.
# =========================================================================
