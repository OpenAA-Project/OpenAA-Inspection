# CMakeLists.txt generated from Proofreader.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(Proofreader LANGUAGES CXX)

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
    "../Open/XShowVersion.cpp"
    "main.cpp"
    "ProofGraph.cpp"
    "proofreader.cpp"
    "WhiteBalanceForm.cpp"
    "../GeneralSource/XGUIGlobal.cpp"
)

set(PROJECT_HEADERS
    "../Open/XDLLType.h"
    "../Open/XTypeDef.h"
    "GeneratedFiles/ui_ProofGraph.h"
    "GeneratedFiles/ui_WhiteBalanceForm.h"
)

set(PROJECT_FORMS
    "ProofGraph.ui"
    "proofreader.ui"
    "WhiteBalanceForm.ui"
)

set(PROJECT_RESOURCES
    "proofreader.qrc"
)

set(PROJECT_SOURCES_DEBUG
    "GeneratedFiles/Debug/moc_ProofGraph.cpp"
    "GeneratedFiles/Debug/moc_WhiteBalanceForm.cpp"
)

set(PROJECT_SOURCES_RELEASE
    "GeneratedFiles/Release/moc_ProofGraph.cpp"
    "GeneratedFiles/Release/moc_WhiteBalanceForm.cpp"
)

qt_wrap_ui(PROJECT_SOURCES ${PROJECT_FORMS})
qt_add_resources(PROJECT_SOURCES ${PROJECT_RESOURCES})

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
        "../EditGUI/EditGUI"
        "../GeneralSource"
        "./GeneratedFiles"
        "../ServiceLib/CommonGUIDLL"
        "./GeneratedFiles/"
        "./GeneratedFiles/$(Configuration)"
        "../OpenSource/Component"
        "$(HALCONROOT)/include"
        "../EditGUI/EditGUI/GeneratedFiles"
        "../Open"
        "../OpenSource/DisplayImage"
        "../ServiceLib/ServiceLib/GeneratedFiles"
        "$(HALCONROOT)/include/cpp"
        "../OpenSource/DisplayImage/GeneratedFiles"
        "../ServiceLib/ServiceLib"
        "../ServiceLib/CommonGUIDLL/GeneratedFiles"
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
            "ServiceLib.lib"
        >
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            "libDisplayImage.a"
            "libIntegrationLib.a"
            "libComponent.a"
            "libServiceLib.a"
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
        "../EditGUI/EditGUI"
        "../GeneralSource"
        "./GeneratedFiles"
        "../ServiceLib/CommonGUIDLL"
        "./GeneratedFiles/"
        "./GeneratedFiles/$(Configuration)"
        "../OpenSource/Component"
        "$(HALCONROOT)/include"
        "../EditGUI/EditGUI/GeneratedFiles"
        "$(HALCONROOT)/include/cpp"
        "../Open"
        "../OpenSource/DisplayImage"
        "../ServiceLib/ServiceLib/GeneratedFiles"
        "../OpenSource/DisplayImage/GeneratedFiles"
        "../ServiceLib/ServiceLib"
        "../ServiceLib/CommonGUIDLL/GeneratedFiles"
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
            "Component.lib"
            "ServiceLib.lib"
        >
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Intel_SSA>:
            "libDisplayImage.a"
            "libComponent.a"
            "libServiceLib.a"
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
        "../EditGUI/EditGUI"
        "../GeneralSource"
        "./GeneratedFiles"
        "./GeneratedFiles/"
        "./GeneratedFiles/$(Configuration)"
        "../OpenSource/Component"
        "../EditGUI/EditGUI/GeneratedFiles"
        "../Open"
        "../OpenSource/DisplayImage"
        "../ServiceLib/ServiceLib/GeneratedFiles"
        "../OpenSource/DisplayImage/GeneratedFiles"
        "../ServiceLib/ServiceLib"
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
            "ServiceExecutionEditor.lib"
            "IntegrationLib.lib"
            "Component.lib"
            "ServiceLib.lib"
        >
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            "libDisplayImage.a"
            "libServiceExecutionEditor.a"
            "libIntegrationLib.a"
            "libComponent.a"
            "libServiceLib.a"
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
#   $(HALCONROOT)
# Please define them in CMake or add them to the macro replacements list.
# =========================================================================
