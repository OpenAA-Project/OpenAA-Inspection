# CMakeLists.txt generated from RecordMoiveWinExe.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(RecordMoiveWinExe LANGUAGES CXX)

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
find_package(Qt6 REQUIRED COMPONENTS Gui Sql Core5Compat Core Widgets Network)

# Find OpenMP
find_package(OpenMP REQUIRED)

set(PROJECT_SOURCES
    "XRecordMovieExe.cpp"
    "../../Open/XShowVersion.cpp"
    "RecordMoiveWinExe.cpp"
    "main.cpp"
)

set(PROJECT_HEADERS
    "RecordMoiveWinExe.h"
    "XRecordMovieExe.h"
)

set(PROJECT_FORMS
    "RecordMoiveWinExe.ui"
)

set(PROJECT_RESOURCES
    "RecordMoiveWinExe.qrc"
)

qt_wrap_ui(PROJECT_SOURCES ${PROJECT_FORMS})
qt_add_resources(PROJECT_SOURCES ${PROJECT_RESOURCES})

# Define the target
add_executable(${PROJECT_NAME}
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

# Link OpenMP
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)

# === Configuration-specific settings ===

if(MSVC)
endif()

# --- End of Debug ---

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../.."
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../.."
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../.."
)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../.."
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../.."
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../.."
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "../RecordMovie"
        "../../Open"
        "."
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "../../Lib/Release"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            "mfplat.lib"
            "dxgi.lib"
            "mfuuid.lib"
            "mfreadwrite.lib"
            "mf.lib"
            "d3d11.lib"
            "DisplayOpenGL.lib"
            "Vfw32.Lib"
            "ServiceLib.lib"
            "CommonGUIDLL.lib"
            "Component.lib"
        >
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            -Wl,--start-group
            "libmfplat.a"
            "libdxgi.a"
            "libmfuuid.a"
            "libmfreadwrite.a"
            "libmf.a"
            "libd3d11.a"
            "libDisplayOpenGL.a"
            "libVfw32.a"
            "libServiceLib.a"
            "libCommonGUIDLL.a"
            "libComponent.a"
            -Wl,--end-group
        >
    )
endif()

if(MSVC)
endif()

# --- End of Release ---

# Avoid "Is a directory" linker error by appending "App" to the output name
# if a directory with the same name as the target already exists in the output path.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../${PROJECT_NAME}" AND IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../${PROJECT_NAME}")
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}App")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Gui
    Qt6::Sql
    Qt6::Core5Compat
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
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

