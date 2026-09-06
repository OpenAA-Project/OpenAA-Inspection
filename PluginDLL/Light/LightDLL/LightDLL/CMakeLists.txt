# CMakeLists.txt generated from LightDLL.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(LightDLL LANGUAGES CXX)

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
find_package(Qt6 REQUIRED COMPONENTS Sql Gui SerialPort Widgets Network Core5Compat Core)

set(PROJECT_SOURCES
    "../../../../GeneralSource/LED64CTRLib.cpp"
    "../../../../GeneralSource/WinDriver10.21/wd_register_lib.c"
    "LightDLL.cpp"
    "LightDLL1.cpp"
    "LightDLL1Form.cpp"
    "LightDLL2Form.cpp"
    "../../../../Open/SystemVersion.cpp"
)

set(PROJECT_HEADERS
    "../../../../Open/LED64CTRLib.h"
    "LightDLL.h"
    "lightdll1.h"
    "lightdll_global.h"
    "../../../../Open/XLightDLL.h"
)

set(PROJECT_FORMS
    "LightDLL1Form.ui"
    "LightDLL2Form.ui"
)

set(PROJECT_SOURCES_DEBUG
    "GeneratedFiles/Debug/moc_LightDLL2Form.cpp"
)

set(PROJECT_SOURCES_RELEASE
    "GeneratedFiles/Release/moc_LightDLL2Form.cpp"
)

qt_wrap_ui(PROJECT_SOURCES ${PROJECT_FORMS})

# Define the target
add_library(${PROJECT_NAME} SHARED
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

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../../PluginDLL"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../../PluginDLL"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../../PluginDLL"
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../../PluginDLL"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../../PluginDLL"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../../PluginDLL"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "./GeneratedFiles"
        "../../../../Open"
        "./GeneratedFiles/"
        "./../../../../GeneralSource/WinDriver10.21"
        "./GeneratedFiles/$(Configuration)"
        "../../../../GeneralSource"
        "$(WD_BASEDIR)"
        "../../../../PluginDLL/Light/LightDLL/LightDLL"
        "$(WD_BASEDIR)/include"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "$(WD_BASEDIR)/lib/amd64"
        "../../../../Open"
        "../../../../lib/Debug"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            "DisplayImage.lib"
            "ForWindows.lib"
            "winmm.lib"
            "Component.lib"
            "ServiceLib.lib"
            "wdapi901.lib"
        >
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            "libDisplayImage.a"
            "libForWindows.a"
            "libwinmm.a"
            "libComponent.a"
            "libServiceLib.a"
            "libwdapi901.a"
        >
    )
endif()

if(MSVC)
endif()

# --- End of Debug ---

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../../PluginDLL"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../../PluginDLL"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../../PluginDLL"
)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../../PluginDLL"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../../PluginDLL"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../../PluginDLL"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "./GeneratedFiles"
        "../../../../Open"
        "./GeneratedFiles/"
        "./../../../../GeneralSource/WinDriver10.21"
        "./GeneratedFiles/$(Configuration)"
        "$(WD_BASEDIR)"
        "../../../../PluginDLL/Light/LightDLL/LightDLL"
        "$(WD_BASEDIR)/include"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "$(WD_BASEDIR)/lib/amd64"
        "../../../../Open"
        "../../../../lib/Release"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            "ForWindows.lib"
            "winmm.lib"
            "ServiceLib.lib"
            "wdapi901.lib"
        >
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            "libForWindows.a"
            "libwinmm.a"
            "libServiceLib.a"
            "libwdapi901.a"
        >
    )
endif()

if(MSVC)
endif()

# --- End of Release ---

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Template>:
        "./GeneratedFiles"
        "./GeneratedFiles/"
    >
)

if(MSVC)
endif()

# --- End of Template ---

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Sql
    Qt6::Gui
    Qt6::SerialPort
    Qt6::Widgets
    Qt6::Network
    Qt6::Core5Compat
    Qt6::Core
)

# === Additional Custom Settings ===

target_include_directories(${PROJECT_NAME} PRIVATE
    "/home/megatrade/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/OpenXLSX"
    "/home/megatrade/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/build/OpenXLSX/"
)


# =========================================================================
# WARNING: The following MSBuild macros were not resolved during conversion:
#   $(WD_BASEDIR)
# Please define them in CMake or add them to the macro replacements list.
# =========================================================================
