# CMakeLists.txt generated from InspectionEditor.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(InspectionEditor LANGUAGES CXX)

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
find_package(Qt6 REQUIRED COMPONENTS Sql Core Xml Gui Widgets Core5Compat Network)

# Find OpenMP
find_package(OpenMP REQUIRED)

set(PROJECT_SOURCES
    "../GeneralSource/XEntryPointWithoutSequence.cpp"
    "../GeneralSource/XGUIGlobal.cpp"
    "../InspectionPlayer/InspectionPlayer/IDatabaseMessageDialog.cpp"
    "../Open/XShowVersion.cpp"
    "BootupLogoForm.cpp"
    "ClosingForm.cpp"
    "InspectionEditorResource.cpp"
    "main.cpp"
)

set(PROJECT_HEADERS
    "../Hasplib/Hasplib/hasplib.h"
    "../Open/XShowVersion.h"
    "../Open/XTypeDef.h"
    "InspectionEditorResource.h"
    "../GeneralSource/XApplication.h"
    "../InspectionPlayer/InspectionPlayer/IDatabaseMessageDialog.h"
    "../Open/XSingleExecuteBySocket.h"
    "ClosingForm.h"
    "BootupLogoForm.h"
)

set(PROJECT_FORMS
    "ClosingForm.ui"
    "InspectionEditor.ui"
    "BootupLogoForm.ui"
)

set(PROJECT_RESOURCES
    "InspectionEditor.qrc"
)

# Other resource files (icons, images)
set(PROJECT_OTHER_RESOURCES
    "InspectionEditor.rc"
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
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/.."
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/.."
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "../EditGUI/EditGUI"
        "../Open"
        "../InspectionPlayer/InspectionPlayer"
        "../ServiceLib/ServiceLib/GeneratedFiles"
        "../Debug"
        "../EditGUI/EditGUI/GeneratedFiles"
        "../ServiceLib/EditPasswordOnControl"
        "../OpenSource/DisplayImage/GeneratedFiles"
        "../ServiceLib/EditPasswordOnControl/GeneratedFiles"
        "../Integrator/IntegrationLib"
        "./GeneratedFiles/"
        "../EditGUI/EditGUILib/GeneratedFiles"
        "./"
        "../Hasplib/Hasplib"
        "../OpenSource/DisplayImage"
        "../OpenSource/Component"
        "../GeneralSource"
        "../ServiceLib/CommonGUIDLL"
        "../ServiceLib/ServiceLib"
        "../Sentinellib/Sentinellib"
        "../InspectionPlayer/InspectionPlayer/GeneratedFiles"
        "../ServiceLib/CommonGUIDLL/GeneratedFiles"
        "./GeneratedFiles"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "../Lib/Debug"
        "PlatformSDK/Lib/AMD64"
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
        $<$<CONFIG:Debug>:"ServiceLib.lib">
        $<$<CONFIG:Debug>:"IntegrationLib.lib">
        $<$<CONFIG:Debug>:"EditPasswordOnControl.lib">
        $<$<CONFIG:Debug>:"Component.lib">
        $<$<CONFIG:Debug>:"DisplayImage.lib">
        $<$<CONFIG:Debug>:"Hasp.lib">
        $<$<CONFIG:Debug>:"wsock32.lib">
        $<$<CONFIG:Debug>:"Sentinel.lib">
        $<$<CONFIG:Debug>:"CommonGUIDLL.lib">
    )
elseif(UNIX)
    # --- Dynamic Library Linking for ServiceLib (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICELIB_SHARED_LIB_DEBUG NAMES ServiceLib PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
    if(SERVICELIB_SHARED_LIB_DEBUG)
        set(SERVICELIB_FINAL_LIB_DEBUG ${SERVICELIB_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICELIB_STATIC_LIB_DEBUG NAMES libServiceLib.a PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
        if(SERVICELIB_STATIC_LIB_DEBUG)
            set(SERVICELIB_FINAL_LIB_DEBUG ${SERVICELIB_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICELIB_FINAL_LIB_DEBUG ServiceLib)
        endif()
    endif()

    # --- Dynamic Library Linking for IntegrationLib (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(INTEGRATIONLIB_SHARED_LIB_DEBUG NAMES IntegrationLib PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
    if(INTEGRATIONLIB_SHARED_LIB_DEBUG)
        set(INTEGRATIONLIB_FINAL_LIB_DEBUG ${INTEGRATIONLIB_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(INTEGRATIONLIB_STATIC_LIB_DEBUG NAMES libIntegrationLib.a PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
        if(INTEGRATIONLIB_STATIC_LIB_DEBUG)
            set(INTEGRATIONLIB_FINAL_LIB_DEBUG ${INTEGRATIONLIB_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(INTEGRATIONLIB_FINAL_LIB_DEBUG IntegrationLib)
        endif()
    endif()

    # --- Dynamic Library Linking for EditPasswordOnControl (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(EDITPASSWORDONCONTROL_SHARED_LIB_DEBUG NAMES EditPasswordOnControl PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
    if(EDITPASSWORDONCONTROL_SHARED_LIB_DEBUG)
        set(EDITPASSWORDONCONTROL_FINAL_LIB_DEBUG ${EDITPASSWORDONCONTROL_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(EDITPASSWORDONCONTROL_STATIC_LIB_DEBUG NAMES libEditPasswordOnControl.a PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
        if(EDITPASSWORDONCONTROL_STATIC_LIB_DEBUG)
            set(EDITPASSWORDONCONTROL_FINAL_LIB_DEBUG ${EDITPASSWORDONCONTROL_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(EDITPASSWORDONCONTROL_FINAL_LIB_DEBUG EditPasswordOnControl)
        endif()
    endif()

    # --- Dynamic Library Linking for Component (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(COMPONENT_SHARED_LIB_DEBUG NAMES Component PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
    if(COMPONENT_SHARED_LIB_DEBUG)
        set(COMPONENT_FINAL_LIB_DEBUG ${COMPONENT_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMPONENT_STATIC_LIB_DEBUG NAMES libComponent.a PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
        if(COMPONENT_STATIC_LIB_DEBUG)
            set(COMPONENT_FINAL_LIB_DEBUG ${COMPONENT_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(COMPONENT_FINAL_LIB_DEBUG Component)
        endif()
    endif()

    # --- Dynamic Library Linking for DisplayImage (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(DISPLAYIMAGE_SHARED_LIB_DEBUG NAMES DisplayImage PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
    if(DISPLAYIMAGE_SHARED_LIB_DEBUG)
        set(DISPLAYIMAGE_FINAL_LIB_DEBUG ${DISPLAYIMAGE_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(DISPLAYIMAGE_STATIC_LIB_DEBUG NAMES libDisplayImage.a PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
        if(DISPLAYIMAGE_STATIC_LIB_DEBUG)
            set(DISPLAYIMAGE_FINAL_LIB_DEBUG ${DISPLAYIMAGE_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(DISPLAYIMAGE_FINAL_LIB_DEBUG DisplayImage)
        endif()
    endif()

    # --- Dynamic Library Linking for Hasp (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(HASP_SHARED_LIB_DEBUG NAMES Hasp PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
    if(HASP_SHARED_LIB_DEBUG)
        set(HASP_FINAL_LIB_DEBUG ${HASP_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(HASP_STATIC_LIB_DEBUG NAMES libHasp.a PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
        if(HASP_STATIC_LIB_DEBUG)
            set(HASP_FINAL_LIB_DEBUG ${HASP_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(HASP_FINAL_LIB_DEBUG Hasp)
        endif()
    endif()

    # --- Dynamic Library Linking for wsock32 (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(WSOCK32_SHARED_LIB_DEBUG NAMES wsock32 PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
    if(WSOCK32_SHARED_LIB_DEBUG)
        set(WSOCK32_FINAL_LIB_DEBUG ${WSOCK32_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(WSOCK32_STATIC_LIB_DEBUG NAMES libwsock32.a PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
        if(WSOCK32_STATIC_LIB_DEBUG)
            set(WSOCK32_FINAL_LIB_DEBUG ${WSOCK32_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(WSOCK32_FINAL_LIB_DEBUG wsock32)
        endif()
    endif()

    # --- Dynamic Library Linking for Sentinel (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(SENTINEL_SHARED_LIB_DEBUG NAMES Sentinel PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
    if(SENTINEL_SHARED_LIB_DEBUG)
        set(SENTINEL_FINAL_LIB_DEBUG ${SENTINEL_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SENTINEL_STATIC_LIB_DEBUG NAMES libSentinel.a PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
        if(SENTINEL_STATIC_LIB_DEBUG)
            set(SENTINEL_FINAL_LIB_DEBUG ${SENTINEL_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(SENTINEL_FINAL_LIB_DEBUG Sentinel)
        endif()
    endif()

    # --- Dynamic Library Linking for CommonGUIDLL (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(COMMONGUIDLL_SHARED_LIB_DEBUG NAMES CommonGUIDLL PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
    if(COMMONGUIDLL_SHARED_LIB_DEBUG)
        set(COMMONGUIDLL_FINAL_LIB_DEBUG ${COMMONGUIDLL_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMMONGUIDLL_STATIC_LIB_DEBUG NAMES libCommonGUIDLL.a PATHS "../Lib/Debug" "PlatformSDK/Lib/AMD64")
        if(COMMONGUIDLL_STATIC_LIB_DEBUG)
            set(COMMONGUIDLL_FINAL_LIB_DEBUG ${COMMONGUIDLL_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(COMMONGUIDLL_FINAL_LIB_DEBUG CommonGUIDLL)
        endif()
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:-Wl,--start-group>
        $<$<CONFIG:Debug>:${SERVICELIB_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${INTEGRATIONLIB_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${EDITPASSWORDONCONTROL_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${COMPONENT_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${DISPLAYIMAGE_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${HASP_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${WSOCK32_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${SENTINEL_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${COMMONGUIDLL_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:-Wl,--end-group>
    )
endif()

if(MSVC)
endif()

# --- End of Debug ---

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/.."
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/.."
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "../Open"
        "../InspectionPlayer/InspectionPlayer"
        "../ServiceLib/EditPasswordOnControl"
        "../Integrator/IntegrationLib"
        "./GeneratedFiles/"
        "./"
        "../Hasplib/Hasplib"
        "../OpenSource/DisplayImage"
        "../OpenSource/Component"
        "../GeneralSource"
        "../ServiceLib/CommonGUIDLL"
        "../ServiceLib/ServiceLib"
        "../Sentinellib/Sentinellib"
        "../InspectionPlayer/InspectionPlayer/GeneratedFiles"
        "./GeneratedFiles"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "PlatformSDK/Lib/AMD64"
        "../Lib/Release"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "UNICODE"
        "QT_NO_DEBUG"
        "QT_LARGEFILE_SUPPORT"
        "No_HASP_ENABLE"
        "NDEBUG"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:"ServiceLib.lib">
        $<$<CONFIG:Release>:"IntegrationLib.lib">
        $<$<CONFIG:Release>:"EditPasswordOnControl.lib">
        $<$<CONFIG:Release>:"ServiceExecutionEditor.lib">
        $<$<CONFIG:Release>:"Component.lib">
        $<$<CONFIG:Release>:"DisplayImage.lib">
        $<$<CONFIG:Release>:"CommonGUIDLL.lib">
    )
elseif(UNIX)
    # --- Dynamic Library Linking for ServiceLib (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICELIB_SHARED_LIB_RELEASE NAMES ServiceLib PATHS "PlatformSDK/Lib/AMD64" "../Lib/Release")
    if(SERVICELIB_SHARED_LIB_RELEASE)
        set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICELIB_STATIC_LIB_RELEASE NAMES libServiceLib.a PATHS "PlatformSDK/Lib/AMD64" "../Lib/Release")
        if(SERVICELIB_STATIC_LIB_RELEASE)
            set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICELIB_FINAL_LIB_RELEASE ServiceLib)
        endif()
    endif()

    # --- Dynamic Library Linking for IntegrationLib (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(INTEGRATIONLIB_SHARED_LIB_RELEASE NAMES IntegrationLib PATHS "PlatformSDK/Lib/AMD64" "../Lib/Release")
    if(INTEGRATIONLIB_SHARED_LIB_RELEASE)
        set(INTEGRATIONLIB_FINAL_LIB_RELEASE ${INTEGRATIONLIB_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(INTEGRATIONLIB_STATIC_LIB_RELEASE NAMES libIntegrationLib.a PATHS "PlatformSDK/Lib/AMD64" "../Lib/Release")
        if(INTEGRATIONLIB_STATIC_LIB_RELEASE)
            set(INTEGRATIONLIB_FINAL_LIB_RELEASE ${INTEGRATIONLIB_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(INTEGRATIONLIB_FINAL_LIB_RELEASE IntegrationLib)
        endif()
    endif()

    # --- Dynamic Library Linking for EditPasswordOnControl (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(EDITPASSWORDONCONTROL_SHARED_LIB_RELEASE NAMES EditPasswordOnControl PATHS "PlatformSDK/Lib/AMD64" "../Lib/Release")
    if(EDITPASSWORDONCONTROL_SHARED_LIB_RELEASE)
        set(EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE ${EDITPASSWORDONCONTROL_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(EDITPASSWORDONCONTROL_STATIC_LIB_RELEASE NAMES libEditPasswordOnControl.a PATHS "PlatformSDK/Lib/AMD64" "../Lib/Release")
        if(EDITPASSWORDONCONTROL_STATIC_LIB_RELEASE)
            set(EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE ${EDITPASSWORDONCONTROL_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE EditPasswordOnControl)
        endif()
    endif()

    # --- Dynamic Library Linking for ServiceExecutionEditor (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICEEXECUTIONEDITOR_SHARED_LIB_RELEASE NAMES ServiceExecutionEditor PATHS "PlatformSDK/Lib/AMD64" "../Lib/Release")
    if(SERVICEEXECUTIONEDITOR_SHARED_LIB_RELEASE)
        set(SERVICEEXECUTIONEDITOR_FINAL_LIB_RELEASE ${SERVICEEXECUTIONEDITOR_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICEEXECUTIONEDITOR_STATIC_LIB_RELEASE NAMES libServiceExecutionEditor.a PATHS "PlatformSDK/Lib/AMD64" "../Lib/Release")
        if(SERVICEEXECUTIONEDITOR_STATIC_LIB_RELEASE)
            set(SERVICEEXECUTIONEDITOR_FINAL_LIB_RELEASE ${SERVICEEXECUTIONEDITOR_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICEEXECUTIONEDITOR_FINAL_LIB_RELEASE ServiceExecutionEditor)
        endif()
    endif()

    # --- Dynamic Library Linking for Component (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(COMPONENT_SHARED_LIB_RELEASE NAMES Component PATHS "PlatformSDK/Lib/AMD64" "../Lib/Release")
    if(COMPONENT_SHARED_LIB_RELEASE)
        set(COMPONENT_FINAL_LIB_RELEASE ${COMPONENT_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMPONENT_STATIC_LIB_RELEASE NAMES libComponent.a PATHS "PlatformSDK/Lib/AMD64" "../Lib/Release")
        if(COMPONENT_STATIC_LIB_RELEASE)
            set(COMPONENT_FINAL_LIB_RELEASE ${COMPONENT_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(COMPONENT_FINAL_LIB_RELEASE Component)
        endif()
    endif()

    # --- Dynamic Library Linking for DisplayImage (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(DISPLAYIMAGE_SHARED_LIB_RELEASE NAMES DisplayImage PATHS "PlatformSDK/Lib/AMD64" "../Lib/Release")
    if(DISPLAYIMAGE_SHARED_LIB_RELEASE)
        set(DISPLAYIMAGE_FINAL_LIB_RELEASE ${DISPLAYIMAGE_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(DISPLAYIMAGE_STATIC_LIB_RELEASE NAMES libDisplayImage.a PATHS "PlatformSDK/Lib/AMD64" "../Lib/Release")
        if(DISPLAYIMAGE_STATIC_LIB_RELEASE)
            set(DISPLAYIMAGE_FINAL_LIB_RELEASE ${DISPLAYIMAGE_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(DISPLAYIMAGE_FINAL_LIB_RELEASE DisplayImage)
        endif()
    endif()

    # --- Dynamic Library Linking for CommonGUIDLL (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(COMMONGUIDLL_SHARED_LIB_RELEASE NAMES CommonGUIDLL PATHS "PlatformSDK/Lib/AMD64" "../Lib/Release")
    if(COMMONGUIDLL_SHARED_LIB_RELEASE)
        set(COMMONGUIDLL_FINAL_LIB_RELEASE ${COMMONGUIDLL_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMMONGUIDLL_STATIC_LIB_RELEASE NAMES libCommonGUIDLL.a PATHS "PlatformSDK/Lib/AMD64" "../Lib/Release")
        if(COMMONGUIDLL_STATIC_LIB_RELEASE)
            set(COMMONGUIDLL_FINAL_LIB_RELEASE ${COMMONGUIDLL_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(COMMONGUIDLL_FINAL_LIB_RELEASE CommonGUIDLL)
        endif()
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:-Wl,--start-group>
        $<$<CONFIG:Release>:${SERVICELIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${INTEGRATIONLIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${SERVICEEXECUTIONEDITOR_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${COMPONENT_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${DISPLAYIMAGE_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${COMMONGUIDLL_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:-Wl,--end-group>
    )
endif()

if(MSVC)
endif()

# --- End of Release ---

# Avoid "Is a directory" linker error by appending "App" to the output name
# if a directory with the same name as the target already exists in the output path.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}" AND IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}")
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}App")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Sql
    Qt6::Core
    Qt6::Xml
    Qt6::Gui
    Qt6::Widgets
    Qt6::Core5Compat
    Qt6::Network
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
    -ffunction-sections -fdata-sections
    -fsigned-char
)

target_link_options(${PROJECT_NAME} PRIVATE
    "-Wl,--no-undefined"
    "-Wl,--gc-sections"
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

