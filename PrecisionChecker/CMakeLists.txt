# CMakeLists.txt generated from PrecisionChecker.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(PrecisionChecker LANGUAGES CXX)

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
    "../GeneralSource/XEntryPointWithoutSequence.cpp"
    "../Open/XShowVersion.cpp"
    "main.cpp"
    "PrecisionChecker.cpp"
    "../GeneralSource/XFocus.cpp"
)

set(PROJECT_HEADERS
    "PrecisionCheckerLib/PrecisionCheckerLib.h"
    "../Open/XFocus.h"
)

set(PROJECT_FORMS
    "PrecisionChecker.ui"
)

# Other resource files (icons, images)
set(PROJECT_OTHER_RESOURCES
    "PrecisionChecker.rc"
)

qt_wrap_ui(PROJECT_SOURCES ${PROJECT_FORMS})

# Define the target
add_executable(${PROJECT_NAME}
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
        "../GeneralSource"
        "./GeneratedFiles"
        "../PrecisionChecker/PrecisionCheckerLib"
        "./GeneratedFiles/"
        "./GeneratedFiles/$(Configuration)"
        "../OpenSource/Component"
        "../OpenSource/DisplayImage"
        "../Open"
        "../OpenSource/DisplayImage/GeneratedFiles"
        "../ServiceLib/ServiceLib"
        "../OpenSource/qwtplot3d/include"
        "../OpenSource/Component/GeneratedFiles"
        "../Integrator/IntegrationLib"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "../Lib/Debug"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            "DisplayImage.lib"
            "IntegrationLib.lib"
            "Component.lib"
            "opengl32.lib"
            "PrecisionCheckerLib.lib"
            "ServiceLib.lib"
            "qwtplot3d.lib"
        >
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            "libDisplayImage.a"
            "libIntegrationLib.a"
            "libComponent.a"
            "libopengl32.a"
            "libPrecisionCheckerLib.a"
            "libServiceLib.a"
            "libqwtplot3d.a"
        >
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
        "./GeneratedFiles"
        "../PrecisionChecker/PrecisionCheckerLib"
        "./GeneratedFiles/"
        "./GeneratedFiles/$(Configuration)"
        "../OpenSource/Component"
        "../OpenSource/DisplayImage"
        "../Open"
        "../OpenSource/DisplayImage/GeneratedFiles"
        "../OpenSource/qwtplot3d/include"
        "../OpenSource/Component/GeneratedFiles"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Intel_SSA>:
        "../Lib/Debug"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Intel_SSA>:
            "DisplayImage.lib"
            "opengl32.lib"
            "Component.lib"
            "PrecisionCheckerLib.lib"
            "ServiceLib.lib"
            "qwtplot3d.lib"
        >
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Intel_SSA>:
            "libDisplayImage.a"
            "libopengl32.a"
            "libComponent.a"
            "libPrecisionCheckerLib.a"
            "libServiceLib.a"
            "libqwtplot3d.a"
        >
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
        "./GeneratedFiles"
        "../PrecisionChecker/PrecisionCheckerLib"
        "./GeneratedFiles/"
        "./GeneratedFiles/$(Configuration)"
        "../OpenSource/Component"
        "../OpenSource/DisplayImage"
        "../Open"
        "../OpenSource/DisplayImage/GeneratedFiles"
        "../OpenSource/qwtplot3d/include"
        "../OpenSource/Component/GeneratedFiles"
        "../Integrator/IntegrationLib"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "../Lib/Release"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            "DisplayImage.lib"
            "ServiceExecution.lib"
            "IntegrationLib.lib"
            "Component.lib"
            "opengl32.lib"
            "PrecisionCheckerLib.lib"
            "ServiceLib.lib"
            "qwtplot3d.lib"
        >
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            "libDisplayImage.a"
            "libServiceExecution.a"
            "libIntegrationLib.a"
            "libComponent.a"
            "libopengl32.a"
            "libPrecisionCheckerLib.a"
            "libServiceLib.a"
            "libqwtplot3d.a"
        >
    )
endif()

if(MSVC)
endif()

# --- End of Release ---

if(MSVC)
endif()

# --- End of Template ---

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

