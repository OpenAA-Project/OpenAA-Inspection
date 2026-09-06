# CMakeLists.txt generated from CameraXtium-CLHS_PX8.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(CameraXtium-CLHS_PX8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(WIN32)
    add_compile_definitions(WIN32 _WINDOWS)
endif()

if(UNIX)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        # Linux / Raspberry Pi specific settings
    endif()
endif()

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Sql Gui Widgets Network Core5Compat Core)

set(PROJECT_SOURCES
    "../../../../OpenAA-OtherLibrary/Dalsa/featureCtrl.cpp"
    "../../../../OpenAA-OtherLibrary/Dalsa/RunLen.Cpp"
    "../../../OpenSource/Component/mtMeter.cpp"
    "../../../OpenSource/Component/mtTBarGraph.cpp"
    "../../../OpenSource/Component/mtWidgetPosition.cpp"
    "../../../Open/SystemVersion.cpp"
    "camerasetting.cpp"
    "CameraXtiumCLHS_PX8.cpp"
    "CLHS_PX8CommandCreater.cpp"
    "saperaCtrl.cpp"
)

set(PROJECT_HEADERS
    "CameraXtium.h"
    "CLHS_PX8CommandCreater.h"
    "saperaCtrl.h"
    "CameraXtiumCLHS_PX8.h"
    "resource.h"
)

set(PROJECT_FORMS
    "CameraSetting.ui"
)

qt_wrap_ui(PROJECT_SOURCES ${PROJECT_FORMS})

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

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../PluginDLL"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../PluginDLL"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../PluginDLL"
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../PluginDLL"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../PluginDLL"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../PluginDLL"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "./GeneratedFiles"
        "./GeneratedFiles/"
        "."
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            "DisplayImage.lib"
            "Component.lib"
            "ServiceLib.lib"
        >
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            "libDisplayImage.a"
            "libComponent.a"
            "libServiceLib.a"
        >
    )
endif()

if(MSVC)
endif()

# --- End of Debug ---

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_INTEL_SSA "${CMAKE_SOURCE_DIR}/$(Platform)/Intel_SSA"
    LIBRARY_OUTPUT_DIRECTORY_INTEL_SSA "${CMAKE_SOURCE_DIR}/$(Platform)/Intel_SSA"
    RUNTIME_OUTPUT_DIRECTORY_INTEL_SSA "${CMAKE_SOURCE_DIR}/$(Platform)/Intel_SSA"
)

if(CMAKE_BUILD_TYPE STREQUAL "Intel_SSA" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/$(Platform)/Intel_SSA"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/$(Platform)/Intel_SSA"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/$(Platform)/Intel_SSA"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Intel_SSA>:
        "./GeneratedFiles"
        "./GeneratedFiles/"
        "."
    >
)

if(MSVC)
endif()

# --- End of Intel_SSA ---

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
        "./GeneratedFiles"
        "../../../Open"
        "./GeneratedFiles/"
        "../../../OpenSource/Component"
        "."
        "$(OpenAAUseLibrary)/Dalsa"
        "$(SAPERA)/Classes/Basic"
        "$(SAPERA)/Include"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "$(SAPERA)/lib/Win64"
        "../../../Lib/Release"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            "SapClassBasic.lib"
            "corapi.lib"
            "ServiceLib.lib"
        >
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            "libSapClassBasic.a"
            "libcorapi.a"
            "libServiceLib.a"
        >
    )
endif()

if(MSVC)
endif()

# --- End of Release ---

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Sql
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Core5Compat
    Qt6::Core
)

# === Additional Custom Settings ===

target_include_directories(${PROJECT_NAME} PRIVATE
    "/home/megatrade/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/OpenXLSX"
    "/home/megatrade/OpenAA-OtherLibrary/OpenXLSX/OpenXLSX/build/OpenXLSX/"
)


# =========================================================================
# WARNING: The following MSBuild macros were not resolved during conversion:
#   $(OpenAAUseLibrary)
#   $(SAPERA)
# Please define them in CMake or add them to the macro replacements list.
# =========================================================================
