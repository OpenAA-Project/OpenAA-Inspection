# CMakeLists.txt generated from AreaFilter.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(AreaFilter LANGUAGES CXX)

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
    "../../Open/AlgorithmCommon.cpp"
    "AdjustAreaFilterForm.cpp"
    "AreaFilter.cpp"
    "../../Open/SystemVersion.cpp"
    "XAreaFilter.cpp"
    "XAreaFilterItemDifferential.cpp"
    "XAreaFilterItemHorizontalEmphasize.cpp"
    "XAreaFilterItemLineEmphasize.cpp"
    "XAreaFilterItemLineLargeEnflat.cpp"
    "XAreaFilterItemPatternInverted.cpp"
    "XAreaFilterItemVerticalEmphasize.cpp"
    "XAreaFilterPacket.cpp"
)

set(PROJECT_HEADERS
    "AreaFilter.h"
    "areafilter_global.h"
    "../../Open/XAlgorithmDLL.h"
    "XAreaFilter.h"
    "XAreaFilterPacket.h"
    "../../Open/XDLLOnly.h"
    "../../Open/XDLLType.h"
    "AdjustAreaFilterForm.h"
)

set(PROJECT_FORMS
    "AdjustAreaFilterForm.ui"
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

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Algorithm"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Algorithm"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Algorithm"
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Algorithm"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Algorithm"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Algorithm"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "../DynamicMaskingPI"
        "../../ServiceLib/ServiceLib/GeneratedFiles"
        "../../OpenSource/DisplayImage"
        "../../ServiceLib/ServiceLib"
        "../../Open"
        "../../OpenSource/Component"
        "./GeneratedFiles/$(Configuration)"
        "../../OpenSource/DisplayImage/GeneratedFiles"
        "./GeneratedFiles"
        "../../OpenSource/Component/GeneratedFiles"
        "./GeneratedFiles/"
        "../../GeneralSource"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "../../Lib/Debug"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "QT_THREAD_SUPPORT"
        "AREAFILTER_LIB"
        "UNICODE"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:"DisplayImage.lib">
        $<$<CONFIG:Debug>:"EditPasswordOnControl.lib">
        $<$<CONFIG:Debug>:"Component.lib">
        $<$<CONFIG:Debug>:"ModelPageLayerItem.lib">
        $<$<CONFIG:Debug>:"ServiceLib.lib">
    )
elseif(UNIX)
    # --- Dynamic Library Linking for DisplayImage (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(DISPLAYIMAGE_SHARED_LIB_DEBUG NAMES DisplayImage PATHS "../../Lib/Debug")
    if(DISPLAYIMAGE_SHARED_LIB_DEBUG)
        set(DISPLAYIMAGE_FINAL_LIB_DEBUG ${DISPLAYIMAGE_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(DISPLAYIMAGE_STATIC_LIB_DEBUG NAMES libDisplayImage.a PATHS "../../Lib/Debug")
        if(DISPLAYIMAGE_STATIC_LIB_DEBUG)
            set(DISPLAYIMAGE_FINAL_LIB_DEBUG ${DISPLAYIMAGE_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(DISPLAYIMAGE_FINAL_LIB_DEBUG DisplayImage)
        endif()
    endif()

    # --- Dynamic Library Linking for EditPasswordOnControl (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(EDITPASSWORDONCONTROL_SHARED_LIB_DEBUG NAMES EditPasswordOnControl PATHS "../../Lib/Debug")
    if(EDITPASSWORDONCONTROL_SHARED_LIB_DEBUG)
        set(EDITPASSWORDONCONTROL_FINAL_LIB_DEBUG ${EDITPASSWORDONCONTROL_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(EDITPASSWORDONCONTROL_STATIC_LIB_DEBUG NAMES libEditPasswordOnControl.a PATHS "../../Lib/Debug")
        if(EDITPASSWORDONCONTROL_STATIC_LIB_DEBUG)
            set(EDITPASSWORDONCONTROL_FINAL_LIB_DEBUG ${EDITPASSWORDONCONTROL_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(EDITPASSWORDONCONTROL_FINAL_LIB_DEBUG EditPasswordOnControl)
        endif()
    endif()

    # --- Dynamic Library Linking for Component (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(COMPONENT_SHARED_LIB_DEBUG NAMES Component PATHS "../../Lib/Debug")
    if(COMPONENT_SHARED_LIB_DEBUG)
        set(COMPONENT_FINAL_LIB_DEBUG ${COMPONENT_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMPONENT_STATIC_LIB_DEBUG NAMES libComponent.a PATHS "../../Lib/Debug")
        if(COMPONENT_STATIC_LIB_DEBUG)
            set(COMPONENT_FINAL_LIB_DEBUG ${COMPONENT_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(COMPONENT_FINAL_LIB_DEBUG Component)
        endif()
    endif()

    # --- Dynamic Library Linking for ModelPageLayerItem (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(MODELPAGELAYERITEM_SHARED_LIB_DEBUG NAMES ModelPageLayerItem PATHS "../../Lib/Debug")
    if(MODELPAGELAYERITEM_SHARED_LIB_DEBUG)
        set(MODELPAGELAYERITEM_FINAL_LIB_DEBUG ${MODELPAGELAYERITEM_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(MODELPAGELAYERITEM_STATIC_LIB_DEBUG NAMES libModelPageLayerItem.a PATHS "../../Lib/Debug")
        if(MODELPAGELAYERITEM_STATIC_LIB_DEBUG)
            set(MODELPAGELAYERITEM_FINAL_LIB_DEBUG ${MODELPAGELAYERITEM_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(MODELPAGELAYERITEM_FINAL_LIB_DEBUG ModelPageLayerItem)
        endif()
    endif()

    # --- Dynamic Library Linking for ServiceLib (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICELIB_SHARED_LIB_DEBUG NAMES ServiceLib PATHS "../../Lib/Debug")
    if(SERVICELIB_SHARED_LIB_DEBUG)
        set(SERVICELIB_FINAL_LIB_DEBUG ${SERVICELIB_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICELIB_STATIC_LIB_DEBUG NAMES libServiceLib.a PATHS "../../Lib/Debug")
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
        $<$<CONFIG:Debug>:${EDITPASSWORDONCONTROL_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${COMPONENT_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${MODELPAGELAYERITEM_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${SERVICELIB_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:-Wl,--end-group>
    )
endif()

if(MSVC)
endif()

# --- End of Debug ---

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../Algorithm"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../Algorithm"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../Algorithm"
)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Algorithm"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Algorithm"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Algorithm"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "../DynamicMaskingPI"
        "../../OpenSource/DisplayImage"
        "../../Open"
        "../../OpenSource/Component"
        "./GeneratedFiles/$(Configuration)"
        "./GeneratedFiles"
        "./GeneratedFiles/"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "../../Lib/Release"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "NDEBUG"
        "QT_NO_DEBUG"
        "QT_THREAD_SUPPORT"
        "AREAFILTER_LIB"
        "UNICODE"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:"ServiceForAlgorithm.lib">
        $<$<CONFIG:Release>:"EditPasswordOnControl.lib">
        $<$<CONFIG:Release>:"Component.lib">
        $<$<CONFIG:Release>:"ModelPageLayerItem.lib">
        $<$<CONFIG:Release>:"ServiceLib.lib">
    )
elseif(UNIX)
    # --- Dynamic Library Linking for ServiceForAlgorithm (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICEFORALGORITHM_SHARED_LIB_RELEASE NAMES ServiceForAlgorithm PATHS "../../Lib/Release")
    if(SERVICEFORALGORITHM_SHARED_LIB_RELEASE)
        set(SERVICEFORALGORITHM_FINAL_LIB_RELEASE ${SERVICEFORALGORITHM_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICEFORALGORITHM_STATIC_LIB_RELEASE NAMES libServiceForAlgorithm.a PATHS "../../Lib/Release")
        if(SERVICEFORALGORITHM_STATIC_LIB_RELEASE)
            set(SERVICEFORALGORITHM_FINAL_LIB_RELEASE ${SERVICEFORALGORITHM_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICEFORALGORITHM_FINAL_LIB_RELEASE ServiceForAlgorithm)
        endif()
    endif()

    # --- Dynamic Library Linking for EditPasswordOnControl (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(EDITPASSWORDONCONTROL_SHARED_LIB_RELEASE NAMES EditPasswordOnControl PATHS "../../Lib/Release")
    if(EDITPASSWORDONCONTROL_SHARED_LIB_RELEASE)
        set(EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE ${EDITPASSWORDONCONTROL_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(EDITPASSWORDONCONTROL_STATIC_LIB_RELEASE NAMES libEditPasswordOnControl.a PATHS "../../Lib/Release")
        if(EDITPASSWORDONCONTROL_STATIC_LIB_RELEASE)
            set(EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE ${EDITPASSWORDONCONTROL_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE EditPasswordOnControl)
        endif()
    endif()

    # --- Dynamic Library Linking for Component (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(COMPONENT_SHARED_LIB_RELEASE NAMES Component PATHS "../../Lib/Release")
    if(COMPONENT_SHARED_LIB_RELEASE)
        set(COMPONENT_FINAL_LIB_RELEASE ${COMPONENT_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMPONENT_STATIC_LIB_RELEASE NAMES libComponent.a PATHS "../../Lib/Release")
        if(COMPONENT_STATIC_LIB_RELEASE)
            set(COMPONENT_FINAL_LIB_RELEASE ${COMPONENT_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(COMPONENT_FINAL_LIB_RELEASE Component)
        endif()
    endif()

    # --- Dynamic Library Linking for ModelPageLayerItem (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(MODELPAGELAYERITEM_SHARED_LIB_RELEASE NAMES ModelPageLayerItem PATHS "../../Lib/Release")
    if(MODELPAGELAYERITEM_SHARED_LIB_RELEASE)
        set(MODELPAGELAYERITEM_FINAL_LIB_RELEASE ${MODELPAGELAYERITEM_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(MODELPAGELAYERITEM_STATIC_LIB_RELEASE NAMES libModelPageLayerItem.a PATHS "../../Lib/Release")
        if(MODELPAGELAYERITEM_STATIC_LIB_RELEASE)
            set(MODELPAGELAYERITEM_FINAL_LIB_RELEASE ${MODELPAGELAYERITEM_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(MODELPAGELAYERITEM_FINAL_LIB_RELEASE ModelPageLayerItem)
        endif()
    endif()

    # --- Dynamic Library Linking for ServiceLib (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICELIB_SHARED_LIB_RELEASE NAMES ServiceLib PATHS "../../Lib/Release")
    if(SERVICELIB_SHARED_LIB_RELEASE)
        set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICELIB_STATIC_LIB_RELEASE NAMES libServiceLib.a PATHS "../../Lib/Release")
        if(SERVICELIB_STATIC_LIB_RELEASE)
            set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICELIB_FINAL_LIB_RELEASE ServiceLib)
        endif()
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:-Wl,--start-group>
        $<$<CONFIG:Release>:${SERVICEFORALGORITHM_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${COMPONENT_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${MODELPAGELAYERITEM_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${SERVICELIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:-Wl,--end-group>
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

