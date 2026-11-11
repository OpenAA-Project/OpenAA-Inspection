# CMakeLists.txt generated from PlayVideoWidget.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.

cmake_minimum_required(VERSION 3.16)

project(PlayVideoWidget LANGUAGES CXX)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
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

    # Find FFmpeg libraries for Linux / Raspberry Pi
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(FFMPEG REQUIRED IMPORTED_TARGET
        libavformat
        libavcodec
        libswscale
        libavutil
    )
endif()

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Multimedia Gui Core5Compat OpenGL Sql Widgets Core Network OpenGLWidgets MultimediaWidgets)

# Find OpenMP
find_package(OpenMP REQUIRED)

set(PROJECT_SOURCES
    "../../Open/GUIDllCommon.cpp"
    "../../Open/SystemVersion.cpp"
    "MMFVideoWidget.cpp"
    "PlayVideoWidget.cpp"
)

set(PROJECT_HEADERS
    "playvideowidget_global.h"
    "XVideoCommon.h"
    "XVideoWidget.h"
    "PlayVideoWidget.h"
)

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

target_compile_definitions(${PROJECT_NAME} PRIVATE
    "PLAYVIDEOWIDGET_LIB"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../GUI"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../GUI"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../GUI"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../GUI"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../GUI"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../GUI"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "../../Open"
)

target_link_directories(${PROJECT_NAME} PRIVATE
    "../../Lib/Release"
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        dxgi.lib
        mfreadwrite.lib
        mfplat.lib
        ServiceLib.lib
        d3d11.lib
        mfuuid.lib
        mf.lib
        DisplayOpenGL.lib
        CommonGUIDLL.lib
        Component.lib
    )
elseif(UNIX)
    # --- Dynamic Library Linking for ServiceLib (Release) ---
    find_library(SERVICELIB_SHARED_LIB_RELEASE NAMES ServiceLib PATHS "../../Lib/Release")
    if(SERVICELIB_SHARED_LIB_RELEASE)
        set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_SHARED_LIB_RELEASE})
    else()
        find_library(SERVICELIB_STATIC_LIB_RELEASE NAMES libServiceLib.a PATHS "../../Lib/Release")
        if(SERVICELIB_STATIC_LIB_RELEASE)
            set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_STATIC_LIB_RELEASE})
        else()
            set(SERVICELIB_FINAL_LIB_RELEASE ServiceLib)
        endif()
    endif()

    # --- Dynamic Library Linking for DisplayOpenGL (Release) ---
    find_library(DISPLAYOPENGL_SHARED_LIB_RELEASE NAMES DisplayOpenGL PATHS "../../Lib/Release")
    if(DISPLAYOPENGL_SHARED_LIB_RELEASE)
        set(DISPLAYOPENGL_FINAL_LIB_RELEASE ${DISPLAYOPENGL_SHARED_LIB_RELEASE})
    else()
        find_library(DISPLAYOPENGL_STATIC_LIB_RELEASE NAMES libDisplayOpenGL.a PATHS "../../Lib/Release")
        if(DISPLAYOPENGL_STATIC_LIB_RELEASE)
            set(DISPLAYOPENGL_FINAL_LIB_RELEASE ${DISPLAYOPENGL_STATIC_LIB_RELEASE})
        else()
            set(DISPLAYOPENGL_FINAL_LIB_RELEASE DisplayOpenGL)
        endif()
    endif()

    # --- Dynamic Library Linking for CommonGUIDLL (Release) ---
    find_library(COMMONGUIDLL_SHARED_LIB_RELEASE NAMES CommonGUIDLL PATHS "../../Lib/Release")
    if(COMMONGUIDLL_SHARED_LIB_RELEASE)
        set(COMMONGUIDLL_FINAL_LIB_RELEASE ${COMMONGUIDLL_SHARED_LIB_RELEASE})
    else()
        find_library(COMMONGUIDLL_STATIC_LIB_RELEASE NAMES libCommonGUIDLL.a PATHS "../../Lib/Release")
        if(COMMONGUIDLL_STATIC_LIB_RELEASE)
            set(COMMONGUIDLL_FINAL_LIB_RELEASE ${COMMONGUIDLL_STATIC_LIB_RELEASE})
        else()
            set(COMMONGUIDLL_FINAL_LIB_RELEASE CommonGUIDLL)
        endif()
    endif()

    # --- Dynamic Library Linking for Component (Release) ---
    find_library(COMPONENT_SHARED_LIB_RELEASE NAMES Component PATHS "../../Lib/Release")
    if(COMPONENT_SHARED_LIB_RELEASE)
        set(COMPONENT_FINAL_LIB_RELEASE ${COMPONENT_SHARED_LIB_RELEASE})
    else()
        find_library(COMPONENT_STATIC_LIB_RELEASE NAMES libComponent.a PATHS "../../Lib/Release")
        if(COMPONENT_STATIC_LIB_RELEASE)
            set(COMPONENT_FINAL_LIB_RELEASE ${COMPONENT_STATIC_LIB_RELEASE})
        else()
            set(COMPONENT_FINAL_LIB_RELEASE Component)
        endif()
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE
        -Wl,--start-group
        ${SERVICELIB_FINAL_LIB_RELEASE}
        ${DISPLAYOPENGL_FINAL_LIB_RELEASE}
        ${COMMONGUIDLL_FINAL_LIB_RELEASE}
        ${COMPONENT_FINAL_LIB_RELEASE}
        -Wl,--end-group
        PkgConfig::FFMPEG
    )
endif()

# --- End of Release ---

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Multimedia
    Qt6::Gui
    Qt6::Core5Compat
    Qt6::OpenGL
    Qt6::Sql
    Qt6::Widgets
    Qt6::Core
    Qt6::Network
    Qt6::OpenGLWidgets
    Qt6::MultimediaWidgets
)

# === Additional Custom Settings ===

target_include_directories(${PROJECT_NAME} PRIVATE
    "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/OpenXLSX"
    "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/build/OpenXLSX/"
    "x64/Release/qt"
    "x64/Release/qt/uic"
)

target_link_directories(${PROJECT_NAME} PRIVATE
    "/usr/local/lib/"
    "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/"
    "$ENV{HOME}/OpenAA6/Lib/Release"
)

if(UNIX)
    target_compile_options(${PROJECT_NAME} PRIVATE
        -ffunction-sections -fdata-sections
    )

    target_link_options(${PROJECT_NAME} PRIVATE
        "-Wl,--no-undefined"
        "-Wl,--gc-sections"
    )
endif()

# --- Dynamic Library Linking for ForWindows ---
find_library(FORWINDOWS_SHARED_LIB NAMES ForWindows PATHS "/usr/local/lib/" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/" "$ENV{HOME}/OpenAA6/Lib/Release")
if(FORWINDOWS_SHARED_LIB)
    message(STATUS "Found Shared Library: ${FORWINDOWS_SHARED_LIB}")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${FORWINDOWS_SHARED_LIB})
else()
    find_library(FORWINDOWS_STATIC_LIB NAMES libForWindows.a PATHS "/usr/local/lib/" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/" "$ENV{HOME}/OpenAA6/Lib/Release")
    if(FORWINDOWS_STATIC_LIB)
        message(STATUS "Found Static Library: ${FORWINDOWS_STATIC_LIB}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${FORWINDOWS_STATIC_LIB})
    else()
        message(WARNING "Library ForWindows not found!")
    endif()
endif()

# --- Dynamic Library Linking for NetworkDrive ---
find_library(NETWORKDRIVE_SHARED_LIB NAMES NetworkDrive PATHS "${CMAKE_CURRENT_SOURCE_DIR}/.." "${CMAKE_CURRENT_SOURCE_DIR}/../.." "${CMAKE_CURRENT_SOURCE_DIR}/../../.." "${CMAKE_CURRENT_SOURCE_DIR}/../../../.." NO_DEFAULT_PATH)
if(NETWORKDRIVE_SHARED_LIB)
    message(STATUS "Found Shared Library: ${NETWORKDRIVE_SHARED_LIB}")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${NETWORKDRIVE_SHARED_LIB})
else()
    find_library(NETWORKDRIVE_STATIC_LIB NAMES libNetworkDrive.a PATHS "${CMAKE_CURRENT_SOURCE_DIR}/.." "${CMAKE_CURRENT_SOURCE_DIR}/../.." "${CMAKE_CURRENT_SOURCE_DIR}/../../.." "${CMAKE_CURRENT_SOURCE_DIR}/../../../.." NO_DEFAULT_PATH)
    if(NETWORKDRIVE_STATIC_LIB)
        message(STATUS "Found Static Library: ${NETWORKDRIVE_STATIC_LIB}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${NETWORKDRIVE_STATIC_LIB})
    else()
        message(WARNING "Library NetworkDrive not found!")
    endif()
endif()

# --- Dynamic Library Linking for png16 ---
find_library(PNG16_SHARED_LIB NAMES png16 PATHS "/usr/local/lib/" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/" "$ENV{HOME}/OpenAA6/Lib/Release")
if(PNG16_SHARED_LIB)
    message(STATUS "Found Shared Library: ${PNG16_SHARED_LIB}")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PNG16_SHARED_LIB})
else()
    find_library(PNG16_STATIC_LIB NAMES libpng16.a PATHS "/usr/local/lib/" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/" "$ENV{HOME}/OpenAA6/Lib/Release")
    if(PNG16_STATIC_LIB)
        message(STATUS "Found Static Library: ${PNG16_STATIC_LIB}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${PNG16_STATIC_LIB})
    else()
        message(WARNING "Library png16 not found!")
    endif()
endif()

# Link OpenMP
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)