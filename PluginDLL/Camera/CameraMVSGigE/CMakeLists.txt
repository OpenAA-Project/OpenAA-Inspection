# CMakeLists.txt generated from CameraMVSGigE.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(CameraMVSGigE LANGUAGES CXX)

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

    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        # Linux / Raspberry Pi specific settings
    endif()
endif()

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets Core5Compat Gui Sql)

# Find OpenMP
find_package(OpenMP REQUIRED)

set(PROJECT_SOURCES
    "../../../../OpenAA-OtherLibrary/HIKRobot/MVS/MvCamera.cpp"
    "SelectUserSetDialog.cpp"
    "ShowCameraDialog.cpp"
    "../../../Open/SystemVersion.cpp"
    "CameraMVSGigE.cpp"
)

set(PROJECT_HEADERS
    "CameraMVSGigECommon.h"
    "cameramvsgige_global.h"
    "SelectUserSetDialog.h"
    "CameraMVSGigE.h"
    "ShowCameraDialog.h"
)

set(PROJECT_FORMS
    "SelectUserSetDialog.ui"
    "ShowCameraDialog.ui"
)

# Define the target
add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_FORMS}
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
    $<$<CONFIG:Debug>:
        "CAMERAMVSGIGE_LIB"
    >
)

if(MSVC)
endif()

# --- End of Debug ---

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../PluginDLL"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../PluginDLL"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../PluginDLL"
)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../PluginDLL"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../PluginDLL"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../PluginDLL"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "/opt/MVS/include"
        "../../../Open"
        "/opt/MVS/Includes"
        "$ENV{HOME}/OpenAA-OtherLibrary/HIKRobot/MVS"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "../../../Lib/Release"
        "/opt/MVS/lib/aarch64"
        "/opt/MVS/lib/64"
        "/opt/MVS/Libraries/win64"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "CAMERAMVSGIGE_LIB"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:"MvCameraControl.lib">
        $<$<CONFIG:Release>:"ServiceLib.lib">
    )
elseif(UNIX)
    # --- Dynamic Library Linking for MvCameraControl (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(MVCAMERACONTROL_SHARED_LIB_RELEASE NAMES MvCameraControl PATHS "../../../Lib/Release" "/opt/MVS/lib/aarch64" "/opt/MVS/lib/64" "/opt/MVS/Libraries/win64")
    if(MVCAMERACONTROL_SHARED_LIB_RELEASE)
        set(MVCAMERACONTROL_FINAL_LIB_RELEASE ${MVCAMERACONTROL_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(MVCAMERACONTROL_STATIC_LIB_RELEASE NAMES libMvCameraControl.a PATHS "../../../Lib/Release" "/opt/MVS/lib/aarch64" "/opt/MVS/lib/64" "/opt/MVS/Libraries/win64")
        if(MVCAMERACONTROL_STATIC_LIB_RELEASE)
            set(MVCAMERACONTROL_FINAL_LIB_RELEASE ${MVCAMERACONTROL_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(MVCAMERACONTROL_FINAL_LIB_RELEASE MvCameraControl)
        endif()
    endif()

    # --- Dynamic Library Linking for ServiceLib (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICELIB_SHARED_LIB_RELEASE NAMES ServiceLib PATHS "../../../Lib/Release" "/opt/MVS/lib/aarch64" "/opt/MVS/lib/64" "/opt/MVS/Libraries/win64")
    if(SERVICELIB_SHARED_LIB_RELEASE)
        set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICELIB_STATIC_LIB_RELEASE NAMES libServiceLib.a PATHS "../../../Lib/Release" "/opt/MVS/lib/aarch64" "/opt/MVS/lib/64" "/opt/MVS/Libraries/win64")
        if(SERVICELIB_STATIC_LIB_RELEASE)
            set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICELIB_FINAL_LIB_RELEASE ServiceLib)
        endif()
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:-Wl,--start-group>
        $<$<CONFIG:Release>:${MVCAMERACONTROL_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${SERVICELIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:-Wl,--end-group>
    )
endif()

if(MSVC)
endif()

# --- End of Release ---

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::Widgets
    Qt6::Core5Compat
    Qt6::Gui
    Qt6::Sql
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

target_compile_options(${PROJECT_NAME} PRIVATE
    -O0
    -g
)

    # --- Dynamic Library Linking for ForWindows ---
    # 1. First, search for the shared library (.so)
    find_library(FORWINDOWS_SHARED_LIB NAMES ForWindows PATHS "/usr/local/lib/" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/" "$ENV{HOME}/OpenAA6/Lib/Release")

    if(FORWINDOWS_SHARED_LIB)
        message(STATUS "Found Shared Library: ${FORWINDOWS_SHARED_LIB}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${FORWINDOWS_SHARED_LIB})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(FORWINDOWS_STATIC_LIB NAMES libForWindows.a PATHS "/usr/local/lib/" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/" "$ENV{HOME}/OpenAA6/Lib/Release")
        if(FORWINDOWS_STATIC_LIB)
            message(STATUS "Found Static Library: ${FORWINDOWS_STATIC_LIB}")
            target_link_libraries(${PROJECT_NAME} PRIVATE ${FORWINDOWS_STATIC_LIB})
        else()
            message(WARNING "Library ForWindows not found!")
        endif()
    endif()

    # --- Dynamic Library Linking for NetworkDrive ---
    # 1. First, search for the shared library (.so)
    find_library(NETWORKDRIVE_SHARED_LIB NAMES NetworkDrive PATHS "${CMAKE_CURRENT_SOURCE_DIR}/.." "${CMAKE_CURRENT_SOURCE_DIR}/../.." "${CMAKE_CURRENT_SOURCE_DIR}/../../.." "${CMAKE_CURRENT_SOURCE_DIR}/../../../.." NO_DEFAULT_PATH)

    if(NETWORKDRIVE_SHARED_LIB)
        message(STATUS "Found Shared Library: ${NETWORKDRIVE_SHARED_LIB}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${NETWORKDRIVE_SHARED_LIB})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(NETWORKDRIVE_STATIC_LIB NAMES libNetworkDrive.a PATHS "${CMAKE_CURRENT_SOURCE_DIR}/.." "${CMAKE_CURRENT_SOURCE_DIR}/../.." "${CMAKE_CURRENT_SOURCE_DIR}/../../.." "${CMAKE_CURRENT_SOURCE_DIR}/../../../.." NO_DEFAULT_PATH)
        if(NETWORKDRIVE_STATIC_LIB)
            message(STATUS "Found Static Library: ${NETWORKDRIVE_STATIC_LIB}")
            target_link_libraries(${PROJECT_NAME} PRIVATE ${NETWORKDRIVE_STATIC_LIB})
        else()
            message(WARNING "Library NetworkDrive not found!")
        endif()
    endif()

    # --- Dynamic Library Linking for png16 ---
    # 1. First, search for the shared library (.so)
    find_library(PNG16_SHARED_LIB NAMES png16 PATHS "/usr/local/lib/" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/" "$ENV{HOME}/OpenAA6/Lib/Release")

    if(PNG16_SHARED_LIB)
        message(STATUS "Found Shared Library: ${PNG16_SHARED_LIB}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${PNG16_SHARED_LIB})
    else()
        # 2. If not found, search for the static library (.a)
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

