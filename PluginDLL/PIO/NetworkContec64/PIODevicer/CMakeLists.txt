# CMakeLists.txt generated from PIODevicer.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(PIODevicer LANGUAGES CXX)

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
    "main.cpp"
    "PIODevicer.cpp"
)

set(PROJECT_HEADERS
    "CDio.h"
)

set(PROJECT_FORMS
    "PIODevicer.ui"
)

# Other resource files (icons, images)
set(PROJECT_OTHER_RESOURCES
    "PIODevicer.rc"
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
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../.."
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../.."
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../.."
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../.."
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../.."
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../.."
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "./GeneratedFiles"
        "./GeneratedFiles/"
        "./GeneratedFiles/$(Configuration)"
        "./../../../../Open"
        "./.."
    >
)

if(MSVC)
endif()

# --- End of Debug ---

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../.."
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../.."
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../.."
)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../.."
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../.."
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../.."
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "./GeneratedFiles"
        "./GeneratedFiles/"
        "./GeneratedFiles/$(Configuration)"
        "./../../../../Open"
        "./.."
        "$(OpenAAUseLibrary)/CONTEC/DIO/DIOWDM/Sample/Inc"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "$(OpenAAUseLibrary)/CONTEC/DIO/DIOWDM/Sample/Lib_amd64"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            "CDIO.lib"
        >
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            "libCDIO.a"
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


# =========================================================================
# WARNING: The following MSBuild macros were not resolved during conversion:
#   $(OpenAAUseLibrary)
# Please define them in CMake or add them to the macro replacements list.
# =========================================================================
