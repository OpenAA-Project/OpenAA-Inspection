# CMakeLists.txt generated from LearningServer.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(LearningServer LANGUAGES CXX)

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
find_package(Qt6 REQUIRED COMPONENTS Network Core5Compat Widgets Gui Sql Core)

# Find OpenMP
find_package(OpenMP REQUIRED)

set(PROJECT_SOURCES
    "../GeneralSource/SingleExecute.cpp"
    "../GeneralSource/XEntryPointWithoutSequence.cpp"
    "../Open/XShowVersion.cpp"
    "ConfirmForm.cpp"
    "EditLineDialog.cpp"
    "LearningServer.cpp"
    "LearningSettingDialog.cpp"
    "main.cpp"
    "XLearningServer.cpp"
    "XServerComm.cpp"
    "XServerLayerBase.cpp"
)

set(PROJECT_HEADERS
    "XServerComm.h"
    "LearningServer.h"
    "../Open/SingleExecute.h"
    "../Open/XSingleExecuteBySocket.h"
    "EditLineDialog.h"
    "XLearningServer.h"
    "XServerLayerBase.h"
    "ConfirmForm.h"
    "LearningSettingDialog.h"
)

set(PROJECT_FORMS
    "ConfirmForm.ui"
    "EditLineDialog.ui"
    "LearningServer.ui"
    "LearningSettingDialog.ui"
)

# Other resource files (icons, images)
set(PROJECT_OTHER_RESOURCES
    "LearningServer.rc"
)

# Define the target
add_executable(${PROJECT_NAME}
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
        "./../Open"
        "./../GeneralSource"
        "./"
        "../Integrator/IntegrationLib"
        "../ServiceLib/ServiceLib"
        "./../OpenSource/Component"
        "./../EditGUI/EditGUI"
        "./../EditGUI/EditGUI/GeneratedFiles"
        "./GeneratedFiles/$(Configuration)"
        "./GeneratedFiles"
        "./../OpenSource/Component/generatedfiles"
        "./GeneratedFiles/"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "../Win64Lib/Debug"
        "../Lib/Debug"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "QT_THREAD_SUPPORT"
        "UNICODE"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:"DisplayImage.lib">
        $<$<CONFIG:Debug>:"fbclient_static.lib">
        $<$<CONFIG:Debug>:"common_static.lib">
        $<$<CONFIG:Debug>:"ModelPageItem.lib">
        $<$<CONFIG:Debug>:"IntegrationLib.lib">
        $<$<CONFIG:Debug>:"Component.lib">
        $<$<CONFIG:Debug>:"ModelPageLayerItem.lib">
        $<$<CONFIG:Debug>:"common.lib">
        $<$<CONFIG:Debug>:"ServiceLib.lib">
    )
elseif(UNIX)
    # --- Dynamic Library Linking for DisplayImage (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(DISPLAYIMAGE_SHARED_LIB_DEBUG NAMES DisplayImage PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(DISPLAYIMAGE_SHARED_LIB_DEBUG)
        set(DISPLAYIMAGE_FINAL_LIB_DEBUG ${DISPLAYIMAGE_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(DISPLAYIMAGE_STATIC_LIB_DEBUG NAMES libDisplayImage.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(DISPLAYIMAGE_STATIC_LIB_DEBUG)
            set(DISPLAYIMAGE_FINAL_LIB_DEBUG ${DISPLAYIMAGE_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(DISPLAYIMAGE_FINAL_LIB_DEBUG DisplayImage)
        endif()
    endif()

    # --- Dynamic Library Linking for fbclient_static (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(FBCLIENT_STATIC_SHARED_LIB_DEBUG NAMES fbclient_static PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(FBCLIENT_STATIC_SHARED_LIB_DEBUG)
        set(FBCLIENT_STATIC_FINAL_LIB_DEBUG ${FBCLIENT_STATIC_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(FBCLIENT_STATIC_STATIC_LIB_DEBUG NAMES libfbclient_static.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(FBCLIENT_STATIC_STATIC_LIB_DEBUG)
            set(FBCLIENT_STATIC_FINAL_LIB_DEBUG ${FBCLIENT_STATIC_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(FBCLIENT_STATIC_FINAL_LIB_DEBUG fbclient_static)
        endif()
    endif()

    # --- Dynamic Library Linking for common_static (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(COMMON_STATIC_SHARED_LIB_DEBUG NAMES common_static PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(COMMON_STATIC_SHARED_LIB_DEBUG)
        set(COMMON_STATIC_FINAL_LIB_DEBUG ${COMMON_STATIC_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMMON_STATIC_STATIC_LIB_DEBUG NAMES libcommon_static.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(COMMON_STATIC_STATIC_LIB_DEBUG)
            set(COMMON_STATIC_FINAL_LIB_DEBUG ${COMMON_STATIC_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(COMMON_STATIC_FINAL_LIB_DEBUG common_static)
        endif()
    endif()

    # --- Dynamic Library Linking for ModelPageItem (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(MODELPAGEITEM_SHARED_LIB_DEBUG NAMES ModelPageItem PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(MODELPAGEITEM_SHARED_LIB_DEBUG)
        set(MODELPAGEITEM_FINAL_LIB_DEBUG ${MODELPAGEITEM_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(MODELPAGEITEM_STATIC_LIB_DEBUG NAMES libModelPageItem.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(MODELPAGEITEM_STATIC_LIB_DEBUG)
            set(MODELPAGEITEM_FINAL_LIB_DEBUG ${MODELPAGEITEM_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(MODELPAGEITEM_FINAL_LIB_DEBUG ModelPageItem)
        endif()
    endif()

    # --- Dynamic Library Linking for IntegrationLib (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(INTEGRATIONLIB_SHARED_LIB_DEBUG NAMES IntegrationLib PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(INTEGRATIONLIB_SHARED_LIB_DEBUG)
        set(INTEGRATIONLIB_FINAL_LIB_DEBUG ${INTEGRATIONLIB_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(INTEGRATIONLIB_STATIC_LIB_DEBUG NAMES libIntegrationLib.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(INTEGRATIONLIB_STATIC_LIB_DEBUG)
            set(INTEGRATIONLIB_FINAL_LIB_DEBUG ${INTEGRATIONLIB_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(INTEGRATIONLIB_FINAL_LIB_DEBUG IntegrationLib)
        endif()
    endif()

    # --- Dynamic Library Linking for Component (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(COMPONENT_SHARED_LIB_DEBUG NAMES Component PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(COMPONENT_SHARED_LIB_DEBUG)
        set(COMPONENT_FINAL_LIB_DEBUG ${COMPONENT_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMPONENT_STATIC_LIB_DEBUG NAMES libComponent.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(COMPONENT_STATIC_LIB_DEBUG)
            set(COMPONENT_FINAL_LIB_DEBUG ${COMPONENT_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(COMPONENT_FINAL_LIB_DEBUG Component)
        endif()
    endif()

    # --- Dynamic Library Linking for ModelPageLayerItem (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(MODELPAGELAYERITEM_SHARED_LIB_DEBUG NAMES ModelPageLayerItem PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(MODELPAGELAYERITEM_SHARED_LIB_DEBUG)
        set(MODELPAGELAYERITEM_FINAL_LIB_DEBUG ${MODELPAGELAYERITEM_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(MODELPAGELAYERITEM_STATIC_LIB_DEBUG NAMES libModelPageLayerItem.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(MODELPAGELAYERITEM_STATIC_LIB_DEBUG)
            set(MODELPAGELAYERITEM_FINAL_LIB_DEBUG ${MODELPAGELAYERITEM_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(MODELPAGELAYERITEM_FINAL_LIB_DEBUG ModelPageLayerItem)
        endif()
    endif()

    # --- Dynamic Library Linking for common (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(COMMON_SHARED_LIB_DEBUG NAMES common PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(COMMON_SHARED_LIB_DEBUG)
        set(COMMON_FINAL_LIB_DEBUG ${COMMON_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMMON_STATIC_LIB_DEBUG NAMES libcommon.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(COMMON_STATIC_LIB_DEBUG)
            set(COMMON_FINAL_LIB_DEBUG ${COMMON_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(COMMON_FINAL_LIB_DEBUG common)
        endif()
    endif()

    # --- Dynamic Library Linking for ServiceLib (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICELIB_SHARED_LIB_DEBUG NAMES ServiceLib PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(SERVICELIB_SHARED_LIB_DEBUG)
        set(SERVICELIB_FINAL_LIB_DEBUG ${SERVICELIB_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICELIB_STATIC_LIB_DEBUG NAMES libServiceLib.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(SERVICELIB_STATIC_LIB_DEBUG)
            set(SERVICELIB_FINAL_LIB_DEBUG ${SERVICELIB_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICELIB_FINAL_LIB_DEBUG ServiceLib)
        endif()
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:-Wl,--start-group>
        $<$<CONFIG:Debug>:${DISPLAYIMAGE_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${FBCLIENT_STATIC_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${COMMON_STATIC_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${MODELPAGEITEM_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${INTEGRATIONLIB_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${COMPONENT_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${MODELPAGELAYERITEM_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${COMMON_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${SERVICELIB_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:-Wl,--end-group>
    )
endif()

if(MSVC)
endif()

# --- End of Debug ---

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_INTEL_SSA "${CMAKE_CURRENT_SOURCE_DIR}/.."
    LIBRARY_OUTPUT_DIRECTORY_INTEL_SSA "${CMAKE_CURRENT_SOURCE_DIR}/.."
    RUNTIME_OUTPUT_DIRECTORY_INTEL_SSA "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

if(CMAKE_BUILD_TYPE STREQUAL "Intel_SSA" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Intel_SSA>:
        "./../Open"
        "./../GeneralSource"
        "./"
        "./../OpenSource/Component"
        "./GeneratedFiles/$(Configuration)"
        "./GeneratedFiles"
        "./../OpenSource/Component/generatedfiles"
        "./GeneratedFiles/"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Intel_SSA>:
        "../Win64Lib/Debug"
        "../Lib/Debug"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Intel_SSA>:
        "QT_THREAD_SUPPORT"
        "UNICODE"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Intel_SSA>:"DisplayImage.lib">
        $<$<CONFIG:Intel_SSA>:"fbclient_static.lib">
        $<$<CONFIG:Intel_SSA>:"common_static.lib">
        $<$<CONFIG:Intel_SSA>:"ModelPageItem.lib">
        $<$<CONFIG:Intel_SSA>:"Component.lib">
        $<$<CONFIG:Intel_SSA>:"ModelPageLayerItem.lib">
        $<$<CONFIG:Intel_SSA>:"common.lib">
        $<$<CONFIG:Intel_SSA>:"ServiceLib.lib">
    )
elseif(UNIX)
    # --- Dynamic Library Linking for DisplayImage (Intel_SSA) ---
    # 1. First, search for the shared library (.so)
    find_library(DISPLAYIMAGE_SHARED_LIB_INTEL_SSA NAMES DisplayImage PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(DISPLAYIMAGE_SHARED_LIB_INTEL_SSA)
        set(DISPLAYIMAGE_FINAL_LIB_INTEL_SSA ${DISPLAYIMAGE_SHARED_LIB_INTEL_SSA})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(DISPLAYIMAGE_STATIC_LIB_INTEL_SSA NAMES libDisplayImage.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(DISPLAYIMAGE_STATIC_LIB_INTEL_SSA)
            set(DISPLAYIMAGE_FINAL_LIB_INTEL_SSA ${DISPLAYIMAGE_STATIC_LIB_INTEL_SSA})
        else()
            # Fallback if not found (e.g. system library)
            set(DISPLAYIMAGE_FINAL_LIB_INTEL_SSA DisplayImage)
        endif()
    endif()

    # --- Dynamic Library Linking for fbclient_static (Intel_SSA) ---
    # 1. First, search for the shared library (.so)
    find_library(FBCLIENT_STATIC_SHARED_LIB_INTEL_SSA NAMES fbclient_static PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(FBCLIENT_STATIC_SHARED_LIB_INTEL_SSA)
        set(FBCLIENT_STATIC_FINAL_LIB_INTEL_SSA ${FBCLIENT_STATIC_SHARED_LIB_INTEL_SSA})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(FBCLIENT_STATIC_STATIC_LIB_INTEL_SSA NAMES libfbclient_static.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(FBCLIENT_STATIC_STATIC_LIB_INTEL_SSA)
            set(FBCLIENT_STATIC_FINAL_LIB_INTEL_SSA ${FBCLIENT_STATIC_STATIC_LIB_INTEL_SSA})
        else()
            # Fallback if not found (e.g. system library)
            set(FBCLIENT_STATIC_FINAL_LIB_INTEL_SSA fbclient_static)
        endif()
    endif()

    # --- Dynamic Library Linking for common_static (Intel_SSA) ---
    # 1. First, search for the shared library (.so)
    find_library(COMMON_STATIC_SHARED_LIB_INTEL_SSA NAMES common_static PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(COMMON_STATIC_SHARED_LIB_INTEL_SSA)
        set(COMMON_STATIC_FINAL_LIB_INTEL_SSA ${COMMON_STATIC_SHARED_LIB_INTEL_SSA})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMMON_STATIC_STATIC_LIB_INTEL_SSA NAMES libcommon_static.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(COMMON_STATIC_STATIC_LIB_INTEL_SSA)
            set(COMMON_STATIC_FINAL_LIB_INTEL_SSA ${COMMON_STATIC_STATIC_LIB_INTEL_SSA})
        else()
            # Fallback if not found (e.g. system library)
            set(COMMON_STATIC_FINAL_LIB_INTEL_SSA common_static)
        endif()
    endif()

    # --- Dynamic Library Linking for ModelPageItem (Intel_SSA) ---
    # 1. First, search for the shared library (.so)
    find_library(MODELPAGEITEM_SHARED_LIB_INTEL_SSA NAMES ModelPageItem PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(MODELPAGEITEM_SHARED_LIB_INTEL_SSA)
        set(MODELPAGEITEM_FINAL_LIB_INTEL_SSA ${MODELPAGEITEM_SHARED_LIB_INTEL_SSA})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(MODELPAGEITEM_STATIC_LIB_INTEL_SSA NAMES libModelPageItem.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(MODELPAGEITEM_STATIC_LIB_INTEL_SSA)
            set(MODELPAGEITEM_FINAL_LIB_INTEL_SSA ${MODELPAGEITEM_STATIC_LIB_INTEL_SSA})
        else()
            # Fallback if not found (e.g. system library)
            set(MODELPAGEITEM_FINAL_LIB_INTEL_SSA ModelPageItem)
        endif()
    endif()

    # --- Dynamic Library Linking for Component (Intel_SSA) ---
    # 1. First, search for the shared library (.so)
    find_library(COMPONENT_SHARED_LIB_INTEL_SSA NAMES Component PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(COMPONENT_SHARED_LIB_INTEL_SSA)
        set(COMPONENT_FINAL_LIB_INTEL_SSA ${COMPONENT_SHARED_LIB_INTEL_SSA})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMPONENT_STATIC_LIB_INTEL_SSA NAMES libComponent.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(COMPONENT_STATIC_LIB_INTEL_SSA)
            set(COMPONENT_FINAL_LIB_INTEL_SSA ${COMPONENT_STATIC_LIB_INTEL_SSA})
        else()
            # Fallback if not found (e.g. system library)
            set(COMPONENT_FINAL_LIB_INTEL_SSA Component)
        endif()
    endif()

    # --- Dynamic Library Linking for ModelPageLayerItem (Intel_SSA) ---
    # 1. First, search for the shared library (.so)
    find_library(MODELPAGELAYERITEM_SHARED_LIB_INTEL_SSA NAMES ModelPageLayerItem PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(MODELPAGELAYERITEM_SHARED_LIB_INTEL_SSA)
        set(MODELPAGELAYERITEM_FINAL_LIB_INTEL_SSA ${MODELPAGELAYERITEM_SHARED_LIB_INTEL_SSA})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(MODELPAGELAYERITEM_STATIC_LIB_INTEL_SSA NAMES libModelPageLayerItem.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(MODELPAGELAYERITEM_STATIC_LIB_INTEL_SSA)
            set(MODELPAGELAYERITEM_FINAL_LIB_INTEL_SSA ${MODELPAGELAYERITEM_STATIC_LIB_INTEL_SSA})
        else()
            # Fallback if not found (e.g. system library)
            set(MODELPAGELAYERITEM_FINAL_LIB_INTEL_SSA ModelPageLayerItem)
        endif()
    endif()

    # --- Dynamic Library Linking for common (Intel_SSA) ---
    # 1. First, search for the shared library (.so)
    find_library(COMMON_SHARED_LIB_INTEL_SSA NAMES common PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(COMMON_SHARED_LIB_INTEL_SSA)
        set(COMMON_FINAL_LIB_INTEL_SSA ${COMMON_SHARED_LIB_INTEL_SSA})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMMON_STATIC_LIB_INTEL_SSA NAMES libcommon.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(COMMON_STATIC_LIB_INTEL_SSA)
            set(COMMON_FINAL_LIB_INTEL_SSA ${COMMON_STATIC_LIB_INTEL_SSA})
        else()
            # Fallback if not found (e.g. system library)
            set(COMMON_FINAL_LIB_INTEL_SSA common)
        endif()
    endif()

    # --- Dynamic Library Linking for ServiceLib (Intel_SSA) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICELIB_SHARED_LIB_INTEL_SSA NAMES ServiceLib PATHS "../Win64Lib/Debug" "../Lib/Debug")
    if(SERVICELIB_SHARED_LIB_INTEL_SSA)
        set(SERVICELIB_FINAL_LIB_INTEL_SSA ${SERVICELIB_SHARED_LIB_INTEL_SSA})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICELIB_STATIC_LIB_INTEL_SSA NAMES libServiceLib.a PATHS "../Win64Lib/Debug" "../Lib/Debug")
        if(SERVICELIB_STATIC_LIB_INTEL_SSA)
            set(SERVICELIB_FINAL_LIB_INTEL_SSA ${SERVICELIB_STATIC_LIB_INTEL_SSA})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICELIB_FINAL_LIB_INTEL_SSA ServiceLib)
        endif()
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Intel_SSA>:-Wl,--start-group>
        $<$<CONFIG:Intel_SSA>:${DISPLAYIMAGE_FINAL_LIB_INTEL_SSA}>
        $<$<CONFIG:Intel_SSA>:${FBCLIENT_STATIC_FINAL_LIB_INTEL_SSA}>
        $<$<CONFIG:Intel_SSA>:${COMMON_STATIC_FINAL_LIB_INTEL_SSA}>
        $<$<CONFIG:Intel_SSA>:${MODELPAGEITEM_FINAL_LIB_INTEL_SSA}>
        $<$<CONFIG:Intel_SSA>:${COMPONENT_FINAL_LIB_INTEL_SSA}>
        $<$<CONFIG:Intel_SSA>:${MODELPAGELAYERITEM_FINAL_LIB_INTEL_SSA}>
        $<$<CONFIG:Intel_SSA>:${COMMON_FINAL_LIB_INTEL_SSA}>
        $<$<CONFIG:Intel_SSA>:${SERVICELIB_FINAL_LIB_INTEL_SSA}>
        $<$<CONFIG:Intel_SSA>:-Wl,--end-group>
    )
endif()

if(MSVC)
endif()

# --- End of Intel_SSA ---

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
        "./../Open"
        "./../GeneralSource"
        "./"
        "../Integrator/IntegrationLib"
        "../ServiceLib/ServiceLib"
        "./../OpenSource/Component"
        "./../EditGUI/EditGUI"
        "./../EditGUI/EditGUI/GeneratedFiles"
        "./GeneratedFiles/$(Configuration)"
        "./GeneratedFiles"
        "./../OpenSource/Component/generatedfiles"
        "./GeneratedFiles/"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "../Lib/Release"
        "../Win64Lib/Release"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "NDEBUG"
        "QT_NO_DEBUG"
        "QT_THREAD_SUPPORT"
        "UNICODE"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:"DisplayImage.lib">
        $<$<CONFIG:Release>:"CommonGUIDLL.lib">
        $<$<CONFIG:Release>:"IntegrationLib.lib">
        $<$<CONFIG:Release>:"Component.lib">
        $<$<CONFIG:Release>:"ServiceExecution.lib">
        $<$<CONFIG:Release>:"ServiceLib.lib">
    )
elseif(UNIX)
    # --- Dynamic Library Linking for DisplayImage (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(DISPLAYIMAGE_SHARED_LIB_RELEASE NAMES DisplayImage PATHS "../Lib/Release" "../Win64Lib/Release")
    if(DISPLAYIMAGE_SHARED_LIB_RELEASE)
        set(DISPLAYIMAGE_FINAL_LIB_RELEASE ${DISPLAYIMAGE_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(DISPLAYIMAGE_STATIC_LIB_RELEASE NAMES libDisplayImage.a PATHS "../Lib/Release" "../Win64Lib/Release")
        if(DISPLAYIMAGE_STATIC_LIB_RELEASE)
            set(DISPLAYIMAGE_FINAL_LIB_RELEASE ${DISPLAYIMAGE_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(DISPLAYIMAGE_FINAL_LIB_RELEASE DisplayImage)
        endif()
    endif()

    # --- Dynamic Library Linking for CommonGUIDLL (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(COMMONGUIDLL_SHARED_LIB_RELEASE NAMES CommonGUIDLL PATHS "../Lib/Release" "../Win64Lib/Release")
    if(COMMONGUIDLL_SHARED_LIB_RELEASE)
        set(COMMONGUIDLL_FINAL_LIB_RELEASE ${COMMONGUIDLL_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMMONGUIDLL_STATIC_LIB_RELEASE NAMES libCommonGUIDLL.a PATHS "../Lib/Release" "../Win64Lib/Release")
        if(COMMONGUIDLL_STATIC_LIB_RELEASE)
            set(COMMONGUIDLL_FINAL_LIB_RELEASE ${COMMONGUIDLL_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(COMMONGUIDLL_FINAL_LIB_RELEASE CommonGUIDLL)
        endif()
    endif()

    # --- Dynamic Library Linking for IntegrationLib (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(INTEGRATIONLIB_SHARED_LIB_RELEASE NAMES IntegrationLib PATHS "../Lib/Release" "../Win64Lib/Release")
    if(INTEGRATIONLIB_SHARED_LIB_RELEASE)
        set(INTEGRATIONLIB_FINAL_LIB_RELEASE ${INTEGRATIONLIB_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(INTEGRATIONLIB_STATIC_LIB_RELEASE NAMES libIntegrationLib.a PATHS "../Lib/Release" "../Win64Lib/Release")
        if(INTEGRATIONLIB_STATIC_LIB_RELEASE)
            set(INTEGRATIONLIB_FINAL_LIB_RELEASE ${INTEGRATIONLIB_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(INTEGRATIONLIB_FINAL_LIB_RELEASE IntegrationLib)
        endif()
    endif()

    # --- Dynamic Library Linking for Component (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(COMPONENT_SHARED_LIB_RELEASE NAMES Component PATHS "../Lib/Release" "../Win64Lib/Release")
    if(COMPONENT_SHARED_LIB_RELEASE)
        set(COMPONENT_FINAL_LIB_RELEASE ${COMPONENT_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMPONENT_STATIC_LIB_RELEASE NAMES libComponent.a PATHS "../Lib/Release" "../Win64Lib/Release")
        if(COMPONENT_STATIC_LIB_RELEASE)
            set(COMPONENT_FINAL_LIB_RELEASE ${COMPONENT_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(COMPONENT_FINAL_LIB_RELEASE Component)
        endif()
    endif()

    # --- Dynamic Library Linking for ServiceExecution (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICEEXECUTION_SHARED_LIB_RELEASE NAMES ServiceExecution PATHS "../Lib/Release" "../Win64Lib/Release")
    if(SERVICEEXECUTION_SHARED_LIB_RELEASE)
        set(SERVICEEXECUTION_FINAL_LIB_RELEASE ${SERVICEEXECUTION_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICEEXECUTION_STATIC_LIB_RELEASE NAMES libServiceExecution.a PATHS "../Lib/Release" "../Win64Lib/Release")
        if(SERVICEEXECUTION_STATIC_LIB_RELEASE)
            set(SERVICEEXECUTION_FINAL_LIB_RELEASE ${SERVICEEXECUTION_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICEEXECUTION_FINAL_LIB_RELEASE ServiceExecution)
        endif()
    endif()

    # --- Dynamic Library Linking for ServiceLib (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICELIB_SHARED_LIB_RELEASE NAMES ServiceLib PATHS "../Lib/Release" "../Win64Lib/Release")
    if(SERVICELIB_SHARED_LIB_RELEASE)
        set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICELIB_STATIC_LIB_RELEASE NAMES libServiceLib.a PATHS "../Lib/Release" "../Win64Lib/Release")
        if(SERVICELIB_STATIC_LIB_RELEASE)
            set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICELIB_FINAL_LIB_RELEASE ServiceLib)
        endif()
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:-Wl,--start-group>
        $<$<CONFIG:Release>:${DISPLAYIMAGE_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${COMMONGUIDLL_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${INTEGRATIONLIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${COMPONENT_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${SERVICEEXECUTION_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${SERVICELIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:-Wl,--end-group>
    )
endif()

if(MSVC)
endif()

# --- End of Release ---

if(MSVC)
endif()

# --- End of Template ---

# Avoid "Is a directory" linker error by appending "App" to the output name
# if a directory with the same name as the target already exists in the output path.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}" AND IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}")
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}App")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Network
    Qt6::Core5Compat
    Qt6::Widgets
    Qt6::Gui
    Qt6::Sql
    Qt6::Core
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

