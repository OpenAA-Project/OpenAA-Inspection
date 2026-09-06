# CMakeLists.txt generated from IntegrationNGCategorizedList.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(IntegrationNGCategorizedList LANGUAGES CXX)

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
find_package(Qt6 REQUIRED COMPONENTS Network Widgets Core Sql Core5Compat Gui)

# Find OpenMP
find_package(OpenMP REQUIRED)

set(PROJECT_SOURCES
    "IntegrationNGCategorizedListForm.cpp"
    "IntegrationNGCategorizedListResource.cpp"
    "../../../Open/GUIDllCommon.cpp"
    "../../../Open/SystemVersion.cpp"
    "IntegrationNGCategorizedList.cpp"
)

set(PROJECT_HEADERS
    "integrationngcategorizedlist_global.h"
    "IntegrationNGCategorizedListForm.h"
    "IntegrationNGCategorizedList.h"
)

set(PROJECT_FORMS
    "IntegrationNGCategorizedListForm.ui"
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
        "INTEGRATIONNGCATEGORIZEDLIST_LIB"
    >
)

if(MSVC)
endif()

# --- End of Debug ---

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../GUI"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../GUI"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../GUI"
)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../GUI"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../GUI"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../GUI"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "../../../OpenSource/InputInTouchPanel"
        "../../IntegrationLib"
        "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/include"
        "."
        "../../../OpenSource/Component"
        "../../../Open"
        "./GeneratedFiles/"
        "./GeneratedFiles"
        "../../../OpenSource/DisplayImage"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/lib"
        "../../../Lib/Release"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "INTEGRATIONNGCATEGORIZEDLIST_LIB"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:"InputInTouchPanel.lib">
        $<$<CONFIG:Release>:"IntegrationLib.lib">
        $<$<CONFIG:Release>:"xlsxwriter.lib">
        $<$<CONFIG:Release>:"ServiceLib.lib">
    )
elseif(UNIX)
    # --- Exact/Static Library Linking for InputInTouchPanel (Release) ---
    # 1. Search for the exact library or static library
    find_library(INPUTINTOUCHPANEL_STATIC_LIB_RELEASE NAMES "libInputInTouchPanel.a" PATHS "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/lib" "../../../Lib/Release")
    if(INPUTINTOUCHPANEL_STATIC_LIB_RELEASE)
        set(INPUTINTOUCHPANEL_FINAL_LIB_RELEASE ${INPUTINTOUCHPANEL_STATIC_LIB_RELEASE})
    else()
        # Fallback if not found (e.g. system library)
        set(INPUTINTOUCHPANEL_FINAL_LIB_RELEASE InputInTouchPanel)
    endif()

    # --- Exact/Static Library Linking for IntegrationLib (Release) ---
    # 1. Search for the exact library or static library
    find_library(INTEGRATIONLIB_STATIC_LIB_RELEASE NAMES "libIntegrationLib.a" PATHS "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/lib" "../../../Lib/Release")
    if(INTEGRATIONLIB_STATIC_LIB_RELEASE)
        set(INTEGRATIONLIB_FINAL_LIB_RELEASE ${INTEGRATIONLIB_STATIC_LIB_RELEASE})
    else()
        # Fallback if not found (e.g. system library)
        set(INTEGRATIONLIB_FINAL_LIB_RELEASE IntegrationLib)
    endif()

    # --- Exact/Static Library Linking for xlsxwriter (Release) ---
    # 1. Search for the exact library or static library
    find_library(XLSXWRITER_STATIC_LIB_RELEASE NAMES "libxlsxwriter.a" PATHS "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/lib" "../../../Lib/Release")
    if(XLSXWRITER_STATIC_LIB_RELEASE)
        set(XLSXWRITER_FINAL_LIB_RELEASE ${XLSXWRITER_STATIC_LIB_RELEASE})
    else()
        # Fallback if not found (e.g. system library)
        set(XLSXWRITER_FINAL_LIB_RELEASE xlsxwriter)
    endif()

    # --- Exact/Static Library Linking for ServiceLib (Release) ---
    # 1. Search for the exact library or static library
    find_library(SERVICELIB_STATIC_LIB_RELEASE NAMES "libServiceLib.a" PATHS "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/lib" "../../../Lib/Release")
    if(SERVICELIB_STATIC_LIB_RELEASE)
        set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_STATIC_LIB_RELEASE})
    else()
        # Fallback if not found (e.g. system library)
        set(SERVICELIB_FINAL_LIB_RELEASE ServiceLib)
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:-Wl,--start-group>
        $<$<CONFIG:Release>:${INPUTINTOUCHPANEL_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${INTEGRATIONLIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${XLSXWRITER_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${SERVICELIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:-Wl,--end-group>
    )
endif()

if(MSVC)
endif()

# --- End of Release ---

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Network
    Qt6::Widgets
    Qt6::Core
    Qt6::Sql
    Qt6::Core5Compat
    Qt6::Gui
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
    "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/lib/"
    "$ENV{HOME}/OpenAA6/Lib/Release"
)

target_link_options(${PROJECT_NAME} PRIVATE
    "-Wl,--no-undefined"
)

    # --- Exact/Static Library Linking for ForWindows ---
    find_library(FORWINDOWS_STATIC_LIB NAMES "libForWindows.a" PATHS "/usr/local/lib/" "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/lib/" "$ENV{HOME}/OpenAA6/Lib/Release")

    if(FORWINDOWS_STATIC_LIB)
        message(STATUS "Found Exact/Static Library: ${FORWINDOWS_STATIC_LIB}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${FORWINDOWS_STATIC_LIB})
    else()
        message(WARNING "Library libForWindows.a not found! Fallback to default linking.")
        target_link_libraries(${PROJECT_NAME} PRIVATE "libForWindows.a")
    endif()

    # --- Exact/Static Library Linking for NetworkDrive ---
    find_library(NETWORKDRIVE_STATIC_LIB NAMES "libNetworkDrive.so" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/.." "${CMAKE_CURRENT_SOURCE_DIR}/../.." "${CMAKE_CURRENT_SOURCE_DIR}/../../.." "${CMAKE_CURRENT_SOURCE_DIR}/../../../.." NO_DEFAULT_PATH)

    if(NETWORKDRIVE_STATIC_LIB)
        message(STATUS "Found Exact/Static Library: ${NETWORKDRIVE_STATIC_LIB}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${NETWORKDRIVE_STATIC_LIB})
    else()
        message(WARNING "Library libNetworkDrive.so not found! Fallback to default linking.")
        target_link_libraries(${PROJECT_NAME} PRIVATE "libNetworkDrive.so")
    endif()

    # --- Exact/Static Library Linking for miniz ---
    find_library(MINIZ_STATIC_LIB NAMES "libminiz.a" PATHS "/usr/local/lib/" "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/lib/" "$ENV{HOME}/OpenAA6/Lib/Release")

    if(MINIZ_STATIC_LIB)
        message(STATUS "Found Exact/Static Library: ${MINIZ_STATIC_LIB}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${MINIZ_STATIC_LIB})
    else()
        message(WARNING "Library libminiz.a not found! Fallback to default linking.")
        target_link_libraries(${PROJECT_NAME} PRIVATE miniz)
    endif()

    # --- Exact/Static Library Linking for png16 ---
    find_library(PNG16_STATIC_LIB NAMES "libpng16.so" PATHS "/usr/local/lib/" "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/lib/" "$ENV{HOME}/OpenAA6/Lib/Release")

    if(PNG16_STATIC_LIB)
        message(STATUS "Found Exact/Static Library: ${PNG16_STATIC_LIB}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${PNG16_STATIC_LIB})
    else()
        message(WARNING "Library libpng16.so not found! Fallback to default linking.")
        target_link_libraries(${PROJECT_NAME} PRIVATE "libpng16.so")
    endif()

    # --- Exact/Static Library Linking for pugixml ---
    find_library(PUGIXML_STATIC_LIB NAMES "libpugixml.a" PATHS "/usr/local/lib/" "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/lib/" "$ENV{HOME}/OpenAA6/Lib/Release")

    if(PUGIXML_STATIC_LIB)
        message(STATUS "Found Exact/Static Library: ${PUGIXML_STATIC_LIB}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${PUGIXML_STATIC_LIB})
    else()
        message(WARNING "Library libpugixml.a not found! Fallback to default linking.")
        target_link_libraries(${PROJECT_NAME} PRIVATE pugixml)
    endif()

    # --- System Library Linking for z ---
    target_link_libraries(${PROJECT_NAME} PRIVATE z)

# Link OpenMP
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)

