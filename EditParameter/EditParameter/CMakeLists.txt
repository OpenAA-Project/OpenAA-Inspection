# CMakeLists.txt generated from EditParameter.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(EditParameter LANGUAGES CXX)

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
find_package(Qt6 REQUIRED COMPONENTS Network Core5Compat Sql Core Gui Widgets)

# Find OpenMP
find_package(OpenMP REQUIRED)

set(PROJECT_SOURCES
    "../../EditGUI/EditGUI/EditSyncGUIForm.cpp"
    "../../GeneralSource/XGUIGlobal.cpp"
    "../../Open/XShowVersion.cpp"
    "ComponentParameterDialog.cpp"
    "EditEachPageLocalDialog.cpp"
    "EditParameter.cpp"
    "EditParameterResource.cpp"
    "main.cpp"
)

set(PROJECT_HEADERS
    "EditParameter.h"
    "../../EditGUI/EditGUI/EditSyncGUIForm.h"
    "../../Open/SingleExecute.h"
    "EditEachPageLocalDialog.h"
    "ComponentParameterDialog.h"
    "../../Open/XSingleExecuteBySocket.h"
    "../../Open/XGUIInExe.h"
)

set(PROJECT_FORMS
    "../../EditGUI/EditGUI/EditSyncGUIForm.ui"
    "ComponentParameterDialog.ui"
    "EditEachPageLocalDialog.ui"
    "EditParameter.ui"
)

set(PROJECT_RESOURCES
    "EditParameter.qrc"
)

# Other resource files (icons, images)
set(PROJECT_OTHER_RESOURCES
    "EditParameter.rc"
    "EditParameter.ico"
    "EditParameter.png"
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
        "../../ServiceLib/ServiceLib"
        "../../OpenSource/DisplayImage"
        "../../EditGUI/EditGUI"
        "../../Integrator/IntegrationLib"
        "../../OpenSource/Component"
        "../../Open"
        "../../GeneralSource"
        "../../EditGUI/EditGUILib"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "../../Lib/Release"
        "../../EditGUI"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:"ServiceExecutionEditor.lib">
        $<$<CONFIG:Release>:"DisplayImage.lib">
        $<$<CONFIG:Release>:"ServiceLib.lib">
        $<$<CONFIG:Release>:"Component.lib">
        $<$<CONFIG:Release>:"EditGUILib.lib">
        $<$<CONFIG:Release>:"IntegrationLib.lib">
        $<$<CONFIG:Release>:"CommonGUIDLL.lib">
    )
elseif(UNIX)
    # --- Dynamic Library Linking for ServiceExecutionEditor (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICEEXECUTIONEDITOR_SHARED_LIB_RELEASE NAMES ServiceExecutionEditor PATHS "../../Lib/Release" "../../EditGUI")
    if(SERVICEEXECUTIONEDITOR_SHARED_LIB_RELEASE)
        set(SERVICEEXECUTIONEDITOR_FINAL_LIB_RELEASE ${SERVICEEXECUTIONEDITOR_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICEEXECUTIONEDITOR_STATIC_LIB_RELEASE NAMES libServiceExecutionEditor.a PATHS "../../Lib/Release" "../../EditGUI")
        if(SERVICEEXECUTIONEDITOR_STATIC_LIB_RELEASE)
            set(SERVICEEXECUTIONEDITOR_FINAL_LIB_RELEASE ${SERVICEEXECUTIONEDITOR_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICEEXECUTIONEDITOR_FINAL_LIB_RELEASE ServiceExecutionEditor)
        endif()
    endif()

    # --- Dynamic Library Linking for DisplayImage (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(DISPLAYIMAGE_SHARED_LIB_RELEASE NAMES DisplayImage PATHS "../../Lib/Release" "../../EditGUI")
    if(DISPLAYIMAGE_SHARED_LIB_RELEASE)
        set(DISPLAYIMAGE_FINAL_LIB_RELEASE ${DISPLAYIMAGE_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(DISPLAYIMAGE_STATIC_LIB_RELEASE NAMES libDisplayImage.a PATHS "../../Lib/Release" "../../EditGUI")
        if(DISPLAYIMAGE_STATIC_LIB_RELEASE)
            set(DISPLAYIMAGE_FINAL_LIB_RELEASE ${DISPLAYIMAGE_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(DISPLAYIMAGE_FINAL_LIB_RELEASE DisplayImage)
        endif()
    endif()

    # --- Dynamic Library Linking for ServiceLib (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICELIB_SHARED_LIB_RELEASE NAMES ServiceLib PATHS "../../Lib/Release" "../../EditGUI")
    if(SERVICELIB_SHARED_LIB_RELEASE)
        set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICELIB_STATIC_LIB_RELEASE NAMES libServiceLib.a PATHS "../../Lib/Release" "../../EditGUI")
        if(SERVICELIB_STATIC_LIB_RELEASE)
            set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICELIB_FINAL_LIB_RELEASE ServiceLib)
        endif()
    endif()

    # --- Dynamic Library Linking for Component (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(COMPONENT_SHARED_LIB_RELEASE NAMES Component PATHS "../../Lib/Release" "../../EditGUI")
    if(COMPONENT_SHARED_LIB_RELEASE)
        set(COMPONENT_FINAL_LIB_RELEASE ${COMPONENT_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMPONENT_STATIC_LIB_RELEASE NAMES libComponent.a PATHS "../../Lib/Release" "../../EditGUI")
        if(COMPONENT_STATIC_LIB_RELEASE)
            set(COMPONENT_FINAL_LIB_RELEASE ${COMPONENT_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(COMPONENT_FINAL_LIB_RELEASE Component)
        endif()
    endif()

    # --- Dynamic Library Linking for EditGUILib (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(EDITGUILIB_SHARED_LIB_RELEASE NAMES EditGUILib PATHS "../../Lib/Release" "../../EditGUI")
    if(EDITGUILIB_SHARED_LIB_RELEASE)
        set(EDITGUILIB_FINAL_LIB_RELEASE ${EDITGUILIB_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(EDITGUILIB_STATIC_LIB_RELEASE NAMES libEditGUILib.a PATHS "../../Lib/Release" "../../EditGUI")
        if(EDITGUILIB_STATIC_LIB_RELEASE)
            set(EDITGUILIB_FINAL_LIB_RELEASE ${EDITGUILIB_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(EDITGUILIB_FINAL_LIB_RELEASE EditGUILib)
        endif()
    endif()

    # --- Dynamic Library Linking for IntegrationLib (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(INTEGRATIONLIB_SHARED_LIB_RELEASE NAMES IntegrationLib PATHS "../../Lib/Release" "../../EditGUI")
    if(INTEGRATIONLIB_SHARED_LIB_RELEASE)
        set(INTEGRATIONLIB_FINAL_LIB_RELEASE ${INTEGRATIONLIB_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(INTEGRATIONLIB_STATIC_LIB_RELEASE NAMES libIntegrationLib.a PATHS "../../Lib/Release" "../../EditGUI")
        if(INTEGRATIONLIB_STATIC_LIB_RELEASE)
            set(INTEGRATIONLIB_FINAL_LIB_RELEASE ${INTEGRATIONLIB_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(INTEGRATIONLIB_FINAL_LIB_RELEASE IntegrationLib)
        endif()
    endif()

    # --- Dynamic Library Linking for CommonGUIDLL (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(COMMONGUIDLL_SHARED_LIB_RELEASE NAMES CommonGUIDLL PATHS "../../Lib/Release" "../../EditGUI")
    if(COMMONGUIDLL_SHARED_LIB_RELEASE)
        set(COMMONGUIDLL_FINAL_LIB_RELEASE ${COMMONGUIDLL_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMMONGUIDLL_STATIC_LIB_RELEASE NAMES libCommonGUIDLL.a PATHS "../../Lib/Release" "../../EditGUI")
        if(COMMONGUIDLL_STATIC_LIB_RELEASE)
            set(COMMONGUIDLL_FINAL_LIB_RELEASE ${COMMONGUIDLL_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(COMMONGUIDLL_FINAL_LIB_RELEASE CommonGUIDLL)
        endif()
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:-Wl,--start-group>
        $<$<CONFIG:Release>:${SERVICEEXECUTIONEDITOR_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${DISPLAYIMAGE_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${SERVICELIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${COMPONENT_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${EDITGUILIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${INTEGRATIONLIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${COMMONGUIDLL_FINAL_LIB_RELEASE}>
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
    Qt6::Core5Compat
    Qt6::Sql
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
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

# =========================================================================
# .desktop file configuration and installation
# =========================================================================
if(UNIX AND NOT APPLE)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/EditParameter.desktop.in"
        "${CMAKE_CURRENT_BINARY_DIR}/EditParameter.desktop"
        @ONLY
    )
    install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/EditParameter.desktop"
        DESTINATION "$ENV{HOME}/.local/share/applications"
    )
endif()

