# CMakeLists.txt generated from InspectionPlayer.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(InspectionPlayer LANGUAGES CXX)

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
find_package(Qt6 REQUIRED COMPONENTS Network Core5Compat Xml Widgets Gui Sql SerialPort Core)

# Find OpenMP
find_package(OpenMP REQUIRED)

set(PROJECT_SOURCES
    "../../Open/XShowVersion.cpp"
    "BootupLogoForm.cpp"
    "ClosingForm.cpp"
    "ErrorMessageDialog.cpp"
    "IDatabaseMessageDialog.cpp"
    "InspectionPlayer.cpp"
    "InspectionPlayerResource.cpp"
    "main.cpp"
    "../XSequenceLocal.cpp"
    "NoComponentDialog.cpp"
    "XExecuteInspect.cpp"
)

set(PROJECT_HEADERS
    "InspectionPlayerResource.h"
    "../../Open/Regulus64Version.h"
    "NoComponentDialog.h"
    "XExecuteInspect.h"
    "ErrorMessageDialog.h"
    "../XSequenceLocal.h"
    "BootupLogoForm.h"
    "IDatabaseMessageDialog.h"
    "InspectionPlayer.h"
    "ClosingForm.h"
)

set(PROJECT_FORMS
    "BootupLogoForm.ui"
    "ClosingForm.ui"
    "IDatabaseMessageDialog.ui"
    "InspectionPlayer.ui"
    "NoComponentDialog.ui"
    "ErrorMessageDialog.ui"
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
        "../../ServiceLib/EditPasswordOnControl"
        "../../EditGUI/EditGUI"
        "../../ServiceLib/CommonGUIDLL"
        "../../GeneralSource/Sequence"
        "../../Hasplib/Hasplib"
        "../../PluginDLL/Camera"
        "../../ServiceLib/ServiceLib/GeneratedFiles"
        "../../OpenSource/DisplayImage"
        "../"
        "../../ServiceLib/ServiceLib"
        "../../ServiceLib/CommonGUIDLL/GeneratedFiles"
        "../../Open"
        "../../OpenSource/Component"
        "../../Integrator/IntegrationLib"
        "./GeneratedFiles/$(Configuration)"
        "../../OpenSource/DisplayImage/GeneratedFiles"
        "./GeneratedFiles"
        "../../EditGUI/EditGUI/GeneratedFiles"
        "./GeneratedFiles/"
        "../../GeneralSource"
        "../../ServiceLib/EditPasswordOnControl/GeneratedFiles"
        "../../Debug"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "PlatformSDK/Lib/AMD64"
        "../../Lib/Debug"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "_DEBUG"
        "QT_THREAD_SUPPORT"
        "UNICODE"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:"DisplayImage.lib">
        $<$<CONFIG:Debug>:"CommonGUIDLL.lib">
        $<$<CONFIG:Debug>:"IntegrationLib.lib">
        $<$<CONFIG:Debug>:"SeqLib.lib">
        $<$<CONFIG:Debug>:"EditPasswordOnControl.lib">
        $<$<CONFIG:Debug>:"Component.lib">
        $<$<CONFIG:Debug>:"ServiceLib.lib">
    )
elseif(UNIX)
    # --- Dynamic Library Linking for DisplayImage (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(DISPLAYIMAGE_SHARED_LIB_DEBUG NAMES DisplayImage PATHS "PlatformSDK/Lib/AMD64" "../../Lib/Debug")
    if(DISPLAYIMAGE_SHARED_LIB_DEBUG)
        set(DISPLAYIMAGE_FINAL_LIB_DEBUG ${DISPLAYIMAGE_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(DISPLAYIMAGE_STATIC_LIB_DEBUG NAMES libDisplayImage.a PATHS "PlatformSDK/Lib/AMD64" "../../Lib/Debug")
        if(DISPLAYIMAGE_STATIC_LIB_DEBUG)
            set(DISPLAYIMAGE_FINAL_LIB_DEBUG ${DISPLAYIMAGE_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(DISPLAYIMAGE_FINAL_LIB_DEBUG DisplayImage)
        endif()
    endif()

    # --- Dynamic Library Linking for CommonGUIDLL (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(COMMONGUIDLL_SHARED_LIB_DEBUG NAMES CommonGUIDLL PATHS "PlatformSDK/Lib/AMD64" "../../Lib/Debug")
    if(COMMONGUIDLL_SHARED_LIB_DEBUG)
        set(COMMONGUIDLL_FINAL_LIB_DEBUG ${COMMONGUIDLL_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMMONGUIDLL_STATIC_LIB_DEBUG NAMES libCommonGUIDLL.a PATHS "PlatformSDK/Lib/AMD64" "../../Lib/Debug")
        if(COMMONGUIDLL_STATIC_LIB_DEBUG)
            set(COMMONGUIDLL_FINAL_LIB_DEBUG ${COMMONGUIDLL_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(COMMONGUIDLL_FINAL_LIB_DEBUG CommonGUIDLL)
        endif()
    endif()

    # --- Dynamic Library Linking for IntegrationLib (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(INTEGRATIONLIB_SHARED_LIB_DEBUG NAMES IntegrationLib PATHS "PlatformSDK/Lib/AMD64" "../../Lib/Debug")
    if(INTEGRATIONLIB_SHARED_LIB_DEBUG)
        set(INTEGRATIONLIB_FINAL_LIB_DEBUG ${INTEGRATIONLIB_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(INTEGRATIONLIB_STATIC_LIB_DEBUG NAMES libIntegrationLib.a PATHS "PlatformSDK/Lib/AMD64" "../../Lib/Debug")
        if(INTEGRATIONLIB_STATIC_LIB_DEBUG)
            set(INTEGRATIONLIB_FINAL_LIB_DEBUG ${INTEGRATIONLIB_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(INTEGRATIONLIB_FINAL_LIB_DEBUG IntegrationLib)
        endif()
    endif()

    # --- Dynamic Library Linking for SeqLib (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(SEQLIB_SHARED_LIB_DEBUG NAMES SeqLib PATHS "PlatformSDK/Lib/AMD64" "../../Lib/Debug")
    if(SEQLIB_SHARED_LIB_DEBUG)
        set(SEQLIB_FINAL_LIB_DEBUG ${SEQLIB_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SEQLIB_STATIC_LIB_DEBUG NAMES libSeqLib.a PATHS "PlatformSDK/Lib/AMD64" "../../Lib/Debug")
        if(SEQLIB_STATIC_LIB_DEBUG)
            set(SEQLIB_FINAL_LIB_DEBUG ${SEQLIB_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(SEQLIB_FINAL_LIB_DEBUG SeqLib)
        endif()
    endif()

    # --- Dynamic Library Linking for EditPasswordOnControl (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(EDITPASSWORDONCONTROL_SHARED_LIB_DEBUG NAMES EditPasswordOnControl PATHS "PlatformSDK/Lib/AMD64" "../../Lib/Debug")
    if(EDITPASSWORDONCONTROL_SHARED_LIB_DEBUG)
        set(EDITPASSWORDONCONTROL_FINAL_LIB_DEBUG ${EDITPASSWORDONCONTROL_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(EDITPASSWORDONCONTROL_STATIC_LIB_DEBUG NAMES libEditPasswordOnControl.a PATHS "PlatformSDK/Lib/AMD64" "../../Lib/Debug")
        if(EDITPASSWORDONCONTROL_STATIC_LIB_DEBUG)
            set(EDITPASSWORDONCONTROL_FINAL_LIB_DEBUG ${EDITPASSWORDONCONTROL_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(EDITPASSWORDONCONTROL_FINAL_LIB_DEBUG EditPasswordOnControl)
        endif()
    endif()

    # --- Dynamic Library Linking for Component (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(COMPONENT_SHARED_LIB_DEBUG NAMES Component PATHS "PlatformSDK/Lib/AMD64" "../../Lib/Debug")
    if(COMPONENT_SHARED_LIB_DEBUG)
        set(COMPONENT_FINAL_LIB_DEBUG ${COMPONENT_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMPONENT_STATIC_LIB_DEBUG NAMES libComponent.a PATHS "PlatformSDK/Lib/AMD64" "../../Lib/Debug")
        if(COMPONENT_STATIC_LIB_DEBUG)
            set(COMPONENT_FINAL_LIB_DEBUG ${COMPONENT_STATIC_LIB_DEBUG})
        else()
            # Fallback if not found (e.g. system library)
            set(COMPONENT_FINAL_LIB_DEBUG Component)
        endif()
    endif()

    # --- Dynamic Library Linking for ServiceLib (Debug) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICELIB_SHARED_LIB_DEBUG NAMES ServiceLib PATHS "PlatformSDK/Lib/AMD64" "../../Lib/Debug")
    if(SERVICELIB_SHARED_LIB_DEBUG)
        set(SERVICELIB_FINAL_LIB_DEBUG ${SERVICELIB_SHARED_LIB_DEBUG})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICELIB_STATIC_LIB_DEBUG NAMES libServiceLib.a PATHS "PlatformSDK/Lib/AMD64" "../../Lib/Debug")
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
        $<$<CONFIG:Debug>:${COMMONGUIDLL_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${INTEGRATIONLIB_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${SEQLIB_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${EDITPASSWORDONCONTROL_FINAL_LIB_DEBUG}>
        $<$<CONFIG:Debug>:${COMPONENT_FINAL_LIB_DEBUG}>
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
        "../../ServiceLib/EditPasswordOnControl"
        "../../ServiceLib/CommonGUIDLL"
        "../../Hasplib/Hasplib"
        "../../PluginDLL/Camera"
        "../../OpenSource/DisplayImage"
        "../"
        "./"
        "../../Open"
        "../../OpenSource/Component"
        "../../Integrator/IntegrationLib"
        "./GeneratedFiles/$(Configuration)"
        "./GeneratedFiles"
        "./GeneratedFiles/"
        "../../ServiceLib/EditPasswordOnControl/GeneratedFiles"
        "../../Debug"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "../../Lib/Release"
        "PlatformSDK/Lib/AMD64"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "NDEBUG"
        "QT_NO_DEBUG"
        "QT_THREAD_SUPPORT"
        "UNICODE"
        "_HASP_ENABLE"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:"CommonGUIDLL.lib">
        $<$<CONFIG:Release>:"ServiceExecutionPlayer.lib">
        $<$<CONFIG:Release>:"IntegrationLib.lib">
        $<$<CONFIG:Release>:"SeqLib.lib">
        $<$<CONFIG:Release>:"EditPasswordOnControl.lib">
        $<$<CONFIG:Release>:"ServiceLib.lib">
    )
elseif(UNIX)
    # --- Dynamic Library Linking for CommonGUIDLL (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(COMMONGUIDLL_SHARED_LIB_RELEASE NAMES CommonGUIDLL PATHS "../../Lib/Release" "PlatformSDK/Lib/AMD64")
    if(COMMONGUIDLL_SHARED_LIB_RELEASE)
        set(COMMONGUIDLL_FINAL_LIB_RELEASE ${COMMONGUIDLL_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMMONGUIDLL_STATIC_LIB_RELEASE NAMES libCommonGUIDLL.a PATHS "../../Lib/Release" "PlatformSDK/Lib/AMD64")
        if(COMMONGUIDLL_STATIC_LIB_RELEASE)
            set(COMMONGUIDLL_FINAL_LIB_RELEASE ${COMMONGUIDLL_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(COMMONGUIDLL_FINAL_LIB_RELEASE CommonGUIDLL)
        endif()
    endif()

    # --- Dynamic Library Linking for ServiceExecutionPlayer (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICEEXECUTIONPLAYER_SHARED_LIB_RELEASE NAMES ServiceExecutionPlayer PATHS "../../Lib/Release" "PlatformSDK/Lib/AMD64")
    if(SERVICEEXECUTIONPLAYER_SHARED_LIB_RELEASE)
        set(SERVICEEXECUTIONPLAYER_FINAL_LIB_RELEASE ${SERVICEEXECUTIONPLAYER_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICEEXECUTIONPLAYER_STATIC_LIB_RELEASE NAMES libServiceExecutionPlayer.a PATHS "../../Lib/Release" "PlatformSDK/Lib/AMD64")
        if(SERVICEEXECUTIONPLAYER_STATIC_LIB_RELEASE)
            set(SERVICEEXECUTIONPLAYER_FINAL_LIB_RELEASE ${SERVICEEXECUTIONPLAYER_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICEEXECUTIONPLAYER_FINAL_LIB_RELEASE ServiceExecutionPlayer)
        endif()
    endif()

    # --- Dynamic Library Linking for IntegrationLib (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(INTEGRATIONLIB_SHARED_LIB_RELEASE NAMES IntegrationLib PATHS "../../Lib/Release" "PlatformSDK/Lib/AMD64")
    if(INTEGRATIONLIB_SHARED_LIB_RELEASE)
        set(INTEGRATIONLIB_FINAL_LIB_RELEASE ${INTEGRATIONLIB_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(INTEGRATIONLIB_STATIC_LIB_RELEASE NAMES libIntegrationLib.a PATHS "../../Lib/Release" "PlatformSDK/Lib/AMD64")
        if(INTEGRATIONLIB_STATIC_LIB_RELEASE)
            set(INTEGRATIONLIB_FINAL_LIB_RELEASE ${INTEGRATIONLIB_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(INTEGRATIONLIB_FINAL_LIB_RELEASE IntegrationLib)
        endif()
    endif()

    # --- Dynamic Library Linking for SeqLib (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(SEQLIB_SHARED_LIB_RELEASE NAMES SeqLib PATHS "../../Lib/Release" "PlatformSDK/Lib/AMD64")
    if(SEQLIB_SHARED_LIB_RELEASE)
        set(SEQLIB_FINAL_LIB_RELEASE ${SEQLIB_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SEQLIB_STATIC_LIB_RELEASE NAMES libSeqLib.a PATHS "../../Lib/Release" "PlatformSDK/Lib/AMD64")
        if(SEQLIB_STATIC_LIB_RELEASE)
            set(SEQLIB_FINAL_LIB_RELEASE ${SEQLIB_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(SEQLIB_FINAL_LIB_RELEASE SeqLib)
        endif()
    endif()

    # --- Dynamic Library Linking for EditPasswordOnControl (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(EDITPASSWORDONCONTROL_SHARED_LIB_RELEASE NAMES EditPasswordOnControl PATHS "../../Lib/Release" "PlatformSDK/Lib/AMD64")
    if(EDITPASSWORDONCONTROL_SHARED_LIB_RELEASE)
        set(EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE ${EDITPASSWORDONCONTROL_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(EDITPASSWORDONCONTROL_STATIC_LIB_RELEASE NAMES libEditPasswordOnControl.a PATHS "../../Lib/Release" "PlatformSDK/Lib/AMD64")
        if(EDITPASSWORDONCONTROL_STATIC_LIB_RELEASE)
            set(EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE ${EDITPASSWORDONCONTROL_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE EditPasswordOnControl)
        endif()
    endif()

    # --- Dynamic Library Linking for ServiceLib (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICELIB_SHARED_LIB_RELEASE NAMES ServiceLib PATHS "../../Lib/Release" "PlatformSDK/Lib/AMD64")
    if(SERVICELIB_SHARED_LIB_RELEASE)
        set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICELIB_STATIC_LIB_RELEASE NAMES libServiceLib.a PATHS "../../Lib/Release" "PlatformSDK/Lib/AMD64")
        if(SERVICELIB_STATIC_LIB_RELEASE)
            set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICELIB_FINAL_LIB_RELEASE ServiceLib)
        endif()
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:-Wl,--start-group>
        $<$<CONFIG:Release>:${COMMONGUIDLL_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${SERVICEEXECUTIONPLAYER_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${INTEGRATIONLIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${SEQLIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE}>
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

# Avoid "Is a directory" linker error by appending "App" to the output name
# if a directory with the same name as the target already exists in the output path.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../${PROJECT_NAME}" AND IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../${PROJECT_NAME}")
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}App")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Network
    Qt6::Core5Compat
    Qt6::Xml
    Qt6::Widgets
    Qt6::Gui
    Qt6::Sql
    Qt6::SerialPort
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

