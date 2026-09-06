# CMakeLists.txt generated from MakeMasterReport.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(MakeMasterReport LANGUAGES CXX)

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
find_package(Qt6 REQUIRED COMPONENTS Network Widgets Core Sql Xml Core5Compat Gui)

# Find OpenMP
find_package(OpenMP REQUIRED)

set(PROJECT_SOURCES
    "../../GeneralSource/XGUIGlobal.cpp"
    "../../Open/XShowVersion.cpp"
    "main.cpp"
    "MakeMasterReport.cpp"
    "ShowExecutingDialog.cpp"
    "XReportStructure.cpp"
)

set(PROJECT_HEADERS
    "MakeMasterReport.h"
    "../../Open/SingleExecute.h"
    "../../Open/XSingleExecuteBySocket.h"
    "XReportStructure.h"
    "ShowExecutingDialog.h"
)

set(PROJECT_FORMS
    "MakeMasterReport.ui"
    "ShowExecutingDialog.ui"
)

set(PROJECT_RESOURCES
    "MakeMasterReport.qrc"
)

# Other resource files (icons, images)
set(PROJECT_OTHER_RESOURCES
    "MakeMasterReport.rc"
)

# Define the target
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_FORMS}
    ${PROJECT_RESOURCES}
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
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../.."
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../.."
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../.."
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../.."
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../.."
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../.."
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "../../GUI/ButtonSelectMachine/GeneratedFiles"
        "../../EditGUI/EditGUILib/GeneratedFiles"
        "./"
        "../../OpenSource/Component"
        "../../GUI/ButtonSelectMachine"
        "../../ServiceLib/EXCEL/include_cpp"
        "../../Integrator/IntegrationLib"
        "../../ServiceLib/ServiceLib"
        "../../GeneralSource"
        "../../Hasplib/Hasplib"
        "../../EditGUI/EditGUI/GeneratedFiles"
        "./GeneratedFiles/"
        "../../EditGUI/EditGUI"
        "../../ServiceLib/CommonGUIDLL"
        "./GeneratedFiles"
        "../../ServiceLib/ServiceLib/GeneratedFiles"
        "./../../Open"
        "../../EditGUI/EditGUILib"
        "../../ServiceLib/CommonGUIDLL/GeneratedFiles"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "../../Lib/Debug"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "UNICODE"
        "QT_LARGEFILE_SUPPORT"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:"DisplayImage.lib">
        $<$<CONFIG:Debug>:"IntegrationLib.lib">
        $<$<CONFIG:Debug>:"Component.lib">
        $<$<CONFIG:Debug>:"CommonGUIDLL.lib">
        $<$<CONFIG:Debug>:"ServiceLib.lib">
    )
elseif(UNIX)
    # --- Exact/Static Library Linking for DisplayImage (Debug) ---
    # 1. Search for the exact library or static library
    find_library(DISPLAYIMAGE_STATIC_LIB_DEBUG NAMES "libDisplayImage.a" PATHS "../../Lib/Debug")
    if(DISPLAYIMAGE_STATIC_LIB_DEBUG)
        set(DISPLAYIMAGE_FINAL_LIB_DEBUG ${DISPLAYIMAGE_STATIC_LIB_DEBUG})
    else()
        # Fallback if not found (e.g. system library)
        set(DISPLAYIMAGE_FINAL_LIB_DEBUG DisplayImage)
    endif()

    # --- Exact/Static Library Linking for IntegrationLib (Debug) ---
    # 1. Search for the exact library or static library
    find_library(INTEGRATIONLIB_STATIC_LIB_DEBUG NAMES "libIntegrationLib.a" PATHS "../../Lib/Debug")
    if(INTEGRATIONLIB_STATIC_LIB_DEBUG)
        set(INTEGRATIONLIB_FINAL_LIB_DEBUG ${INTEGRATIONLIB_STATIC_LIB_DEBUG})
    else()
        # Fallback if not found (e.g. system library)
        set(INTEGRATIONLIB_FINAL_LIB_DEBUG IntegrationLib)
    endif()

    # --- Exact/Static Library Linking for Component (Debug) ---
    # 1. Search for the exact library or static library
    find_library(COMPONENT_STATIC_LIB_DEBUG NAMES "libComponent.a" PATHS "../../Lib/Debug")
    if(COMPONENT_STATIC_LIB_DEBUG)
        set(COMPONENT_FINAL_LIB_DEBUG ${COMPONENT_STATIC_LIB_DEBUG})
    else()
        # Fallback if not found (e.g. system library)
        set(COMPONENT_FINAL_LIB_DEBUG Component)
    endif()

    # --- Exact/Static Library Linking for CommonGUIDLL (Debug) ---
    # 1. Search for the exact library or static library
    find_library(COMMONGUIDLL_STATIC_LIB_DEBUG NAMES "libCommonGUIDLL.a" PATHS "../../Lib/Debug")
    if(COMMONGUIDLL_STATIC_LIB_DEBUG)
        set(COMMONGUIDLL_FINAL_LIB_DEBUG ${COMMONGUIDLL_STATIC_LIB_DEBUG})
    else()
        # Fallback if not found (e.g. system library)
        set(COMMONGUIDLL_FINAL_LIB_DEBUG CommonGUIDLL)
    endif()

    # --- Exact/Static Library Linking for ServiceLib (Debug) ---
    # 1. Search for the exact library or static library
    find_library(SERVICELIB_STATIC_LIB_DEBUG NAMES "libServiceLib.a" PATHS "../../Lib/Debug")
    if(SERVICELIB_STATIC_LIB_DEBUG)
        set(SERVICELIB_FINAL_LIB_DEBUG ${SERVICELIB_STATIC_LIB_DEBUG})
    else()
        # Fallback if not found (e.g. system library)
        set(SERVICELIB_FINAL_LIB_DEBUG ServiceLib)
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:-Wl,--start-group>
        $<$<CONFIG:Debug>:${DISPLAYIMAGE_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${INTEGRATIONLIB_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${COMPONENT_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${COMMONGUIDLL_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${SERVICELIB_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:-Wl,--end-group>
    )
endif()

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
        "../../GUI/ButtonSelectMachine/GeneratedFiles"
        "./"
        "../../OpenSource/Component"
        "../../GUI/ButtonSelectMachine"
        "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/include"
        "../../Integrator/IntegrationLib"
        "../../GeneralSource"
        "./GeneratedFiles/"
        "../../ServiceLib/CommonGUIDLL"
        "./GeneratedFiles"
        "./../../Open"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "../../Lib/Release"
        "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/lib"
        "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/lib"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "QT_NO_DEBUG"
        "NDEBUG"
        "UNICODE"
        "QT_LARGEFILE_SUPPORT"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:"ServiceExecutionEditor.lib">
        $<$<CONFIG:Release>:"IntegrationLib.lib">
        $<$<CONFIG:Release>:"Component.lib">
        $<$<CONFIG:Release>:"xlsxwriter.lib">
        $<$<CONFIG:Release>:"OpenXLSX.lib">
        $<$<CONFIG:Release>:"CommonGUIDLL.lib">
        $<$<CONFIG:Release>:"ServiceLib.lib">
    )
elseif(UNIX)
    # --- Exact/Static Library Linking for ServiceExecutionEditor (Release) ---
    # 1. Search for the exact library or static library
    find_library(SERVICEEXECUTIONEDITOR_STATIC_LIB_RELEASE NAMES "libServiceExecutionEditor.a" PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/lib" "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/lib")
    if(SERVICEEXECUTIONEDITOR_STATIC_LIB_RELEASE)
        set(SERVICEEXECUTIONEDITOR_FINAL_LIB_RELEASE ${SERVICEEXECUTIONEDITOR_STATIC_LIB_RELEASE})
    else()
        # Fallback if not found (e.g. system library)
        set(SERVICEEXECUTIONEDITOR_FINAL_LIB_RELEASE ServiceExecutionEditor)
    endif()

    # --- Exact/Static Library Linking for IntegrationLib (Release) ---
    # 1. Search for the exact library or static library
    find_library(INTEGRATIONLIB_STATIC_LIB_RELEASE NAMES "libIntegrationLib.a" PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/lib" "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/lib")
    if(INTEGRATIONLIB_STATIC_LIB_RELEASE)
        set(INTEGRATIONLIB_FINAL_LIB_RELEASE ${INTEGRATIONLIB_STATIC_LIB_RELEASE})
    else()
        # Fallback if not found (e.g. system library)
        set(INTEGRATIONLIB_FINAL_LIB_RELEASE IntegrationLib)
    endif()

    # --- Exact/Static Library Linking for Component (Release) ---
    # 1. Search for the exact library or static library
    find_library(COMPONENT_STATIC_LIB_RELEASE NAMES "libComponent.a" PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/lib" "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/lib")
    if(COMPONENT_STATIC_LIB_RELEASE)
        set(COMPONENT_FINAL_LIB_RELEASE ${COMPONENT_STATIC_LIB_RELEASE})
    else()
        # Fallback if not found (e.g. system library)
        set(COMPONENT_FINAL_LIB_RELEASE Component)
    endif()

    # --- Exact/Static Library Linking for xlsxwriter (Release) ---
    # 1. Search for the exact library or static library
    find_library(XLSXWRITER_STATIC_LIB_RELEASE NAMES "libxlsxwriter.a" PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/lib" "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/lib")
    if(XLSXWRITER_STATIC_LIB_RELEASE)
        set(XLSXWRITER_FINAL_LIB_RELEASE ${XLSXWRITER_STATIC_LIB_RELEASE})
    else()
        # Fallback if not found (e.g. system library)
        set(XLSXWRITER_FINAL_LIB_RELEASE xlsxwriter)
    endif()

    # --- Exact/Static Library Linking for OpenXLSX (Release) ---
    # 1. Search for the exact library or static library
    find_library(OPENXLSX_STATIC_LIB_RELEASE NAMES "libOpenXLSX.a" PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/lib" "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/lib")
    if(OPENXLSX_STATIC_LIB_RELEASE)
        set(OPENXLSX_FINAL_LIB_RELEASE ${OPENXLSX_STATIC_LIB_RELEASE})
    else()
        # Fallback if not found (e.g. system library)
        set(OPENXLSX_FINAL_LIB_RELEASE OpenXLSX)
    endif()

    # --- Exact/Static Library Linking for CommonGUIDLL (Release) ---
    # 1. Search for the exact library or static library
    find_library(COMMONGUIDLL_STATIC_LIB_RELEASE NAMES "libCommonGUIDLL.a" PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/lib" "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/lib")
    if(COMMONGUIDLL_STATIC_LIB_RELEASE)
        set(COMMONGUIDLL_FINAL_LIB_RELEASE ${COMMONGUIDLL_STATIC_LIB_RELEASE})
    else()
        # Fallback if not found (e.g. system library)
        set(COMMONGUIDLL_FINAL_LIB_RELEASE CommonGUIDLL)
    endif()

    # --- Exact/Static Library Linking for ServiceLib (Release) ---
    # 1. Search for the exact library or static library
    find_library(SERVICELIB_STATIC_LIB_RELEASE NAMES "libServiceLib.a" PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/lib" "$ENV{HOME}/OpenAA-OtherLibrary/LibXLSXWriter/libxlsxwriter/lib")
    if(SERVICELIB_STATIC_LIB_RELEASE)
        set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_STATIC_LIB_RELEASE})
    else()
        # Fallback if not found (e.g. system library)
        set(SERVICELIB_FINAL_LIB_RELEASE ServiceLib)
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:-Wl,--start-group>
        $<$<CONFIG:Release>:${SERVICEEXECUTIONEDITOR_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${INTEGRATIONLIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${COMPONENT_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${XLSXWRITER_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${OPENXLSX_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${COMMONGUIDLL_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${SERVICELIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:-Wl,--end-group>
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
    Qt6::Network
    Qt6::Widgets
    Qt6::Core
    Qt6::Sql
    Qt6::Xml
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

