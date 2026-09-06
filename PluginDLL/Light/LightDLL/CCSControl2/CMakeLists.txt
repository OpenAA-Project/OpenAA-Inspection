# CMakeLists.txt generated from CCSControl2.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(CCSControl2 LANGUAGES CXX)

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
    # Allow multiple definitions to mimic MSVC static library linking behavior
    add_link_options("-Wl,--allow-multiple-definition")

    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        # Linux / Raspberry Pi specific settings
    endif()
endif()

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets Network Gui Core5Compat Core Sql)

set(PROJECT_SOURCES
    "../../../../GeneralSource/XHidCommand.cpp"
    "../../../../Open/SystemVersion.cpp"
    "CCSControl2.cpp"
    "SettingDialog.cpp"
    "XCCSControl2.cpp"
)

set(PROJECT_HEADERS
    "../../../../Open/XHidCommand.h"
    "CCSControl2.h"
    "ccscontrol2_global.h"
    "XCCSControl2.h"
    "SettingDialog.h"
)

set(PROJECT_FORMS
    "SettingDialog.ui"
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
        "./../../../../Open"
        "."
        "./../../../../GeneralSource"
        "./GeneratedFiles"
        "./../../../../GeneralSource/Sequence"
        "./GeneratedFiles/"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "/lib/win7/amd64"
        "../../../../Lib/Debug"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            "ServiceLib.lib"
            "DisplayImage.lib"
            "Component.lib"
            "hid.lib"
            "SeqLib.lib"
            "setupapi.lib"
        >
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            -Wl,--start-group
            "libServiceLib.a"
            "libDisplayImage.a"
            "libComponent.a"
            "libhid.a"
            "libSeqLib.a"
            "libsetupapi.a"
            -Wl,--end-group
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
        "./../../../../Open"
        "."
        "./../../../../GeneralSource"
        "./GeneratedFiles"
        "./../../../../GeneralSource/Sequence"
        "./GeneratedFiles/"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "/lib/win7/amd64"
        "../../../../Lib/Release"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            "ServiceLib.lib"
            "hid.lib"
            "SeqLib.lib"
            "setupapi.lib"
        >
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            -Wl,--start-group
            "libServiceLib.a"
            "libhid.a"
            "libSeqLib.a"
            "libsetupapi.a"
            -Wl,--end-group
        >
    )
endif()

if(MSVC)
endif()

# --- End of Release ---

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Network
    Qt6::Gui
    Qt6::Core5Compat
    Qt6::Core
    Qt6::Sql
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

set(LIBNETWORKDRIVE_PATH "")
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../libNetworkDrive.so")
    set(LIBNETWORKDRIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../libNetworkDrive.so")
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../libNetworkDrive.so")
    set(LIBNETWORKDRIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libNetworkDrive.so")
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../../libNetworkDrive.so")
    set(LIBNETWORKDRIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libNetworkDrive.so")
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../../../libNetworkDrive.so")
    set(LIBNETWORKDRIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../libNetworkDrive.so")
else()
    message(FATAL_ERROR "Library libNetworkDrive.so not found in any specified paths.")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    "libForWindows.a"
    ${LIBNETWORKDRIVE_PATH}
    "libpng16.so"
)

