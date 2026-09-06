# CMakeLists.txt generated from Raster.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(Raster LANGUAGES CXX)

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
find_package(Qt6 REQUIRED COMPONENTS Gui Widgets Sql Core5Compat Network Core)

# Find OpenMP
find_package(OpenMP REQUIRED)

set(PROJECT_SOURCES
    "../../Open/AlgorithmCommon.cpp"
    "../../Open/SystemVersion.cpp"
    "RasterResource.cpp"
    "XLoadPDF.cpp"
    "XRaster.cpp"
    "XRasterAffin.cpp"
    "XRasterCommon.cpp"
    "XRasterItemAbstract.cpp"
    "XRasterLibrary.cpp"
    "XRasterMakeAlgo.cpp"
    "XRasterMakeIMage.cpp"
    "XRasterPaint.cpp"
    "XRasterPDFItem.cpp"
    "XRasterReferenceItem.cpp"
    "XRasterReport.cpp"
    "XRasterTransmitDirectly.cpp"
    "Raster.cpp"
)

set(PROJECT_HEADERS
    "RasterResource.h"
    "raster_global.h"
    "XRaster.h"
    "Raster.h"
    "XRasterLibrary.h"
    "XRasterPacket.h"
    "../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf-qt/XpdfWidget.h"
)

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

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "RASTER_LIB"
    >
)

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
        "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/goo"
        "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/build"
        "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf-qt"
        "../../GUI/PropertyRaster"
        "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/"
        "../../OpenSource/DisplayImage"
        "../../Open"
        "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/splash"
        "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf"
        "../../OpenSource/Component"
    >
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "../../Lib/Release"
        "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release"
        "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "RASTER_LIB"
    >
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:"ServiceForAlgorithm.lib">
        $<$<CONFIG:Release>:"fofi_objs.lib">
        $<$<CONFIG:Release>:"ModelPageItem.lib">
        $<$<CONFIG:Release>:"freetype.lib">
        $<$<CONFIG:Release>:"PDFWidget.lib">
        $<$<CONFIG:Release>:"goo_objs.lib">
        $<$<CONFIG:Release>:"ServiceLib.lib">
        $<$<CONFIG:Release>:"Component.lib">
        $<$<CONFIG:Release>:"xpdf_objs.lib">
        $<$<CONFIG:Release>:"EditPasswordOnControl.lib">
    )
elseif(UNIX)
    # --- Dynamic Library Linking for ServiceForAlgorithm (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICEFORALGORITHM_SHARED_LIB_RELEASE NAMES ServiceForAlgorithm PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
    if(SERVICEFORALGORITHM_SHARED_LIB_RELEASE)
        set(SERVICEFORALGORITHM_FINAL_LIB_RELEASE ${SERVICEFORALGORITHM_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICEFORALGORITHM_STATIC_LIB_RELEASE NAMES libServiceForAlgorithm.a PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
        if(SERVICEFORALGORITHM_STATIC_LIB_RELEASE)
            set(SERVICEFORALGORITHM_FINAL_LIB_RELEASE ${SERVICEFORALGORITHM_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICEFORALGORITHM_FINAL_LIB_RELEASE ServiceForAlgorithm)
        endif()
    endif()

    # --- Dynamic Library Linking for fofi_objs (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(FOFI_OBJS_SHARED_LIB_RELEASE NAMES fofi_objs PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
    if(FOFI_OBJS_SHARED_LIB_RELEASE)
        set(FOFI_OBJS_FINAL_LIB_RELEASE ${FOFI_OBJS_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(FOFI_OBJS_STATIC_LIB_RELEASE NAMES libfofi_objs.a PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
        if(FOFI_OBJS_STATIC_LIB_RELEASE)
            set(FOFI_OBJS_FINAL_LIB_RELEASE ${FOFI_OBJS_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(FOFI_OBJS_FINAL_LIB_RELEASE fofi_objs)
        endif()
    endif()

    # --- Dynamic Library Linking for ModelPageItem (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(MODELPAGEITEM_SHARED_LIB_RELEASE NAMES ModelPageItem PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
    if(MODELPAGEITEM_SHARED_LIB_RELEASE)
        set(MODELPAGEITEM_FINAL_LIB_RELEASE ${MODELPAGEITEM_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(MODELPAGEITEM_STATIC_LIB_RELEASE NAMES libModelPageItem.a PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
        if(MODELPAGEITEM_STATIC_LIB_RELEASE)
            set(MODELPAGEITEM_FINAL_LIB_RELEASE ${MODELPAGEITEM_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(MODELPAGEITEM_FINAL_LIB_RELEASE ModelPageItem)
        endif()
    endif()

    # --- Dynamic Library Linking for freetype (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(FREETYPE_SHARED_LIB_RELEASE NAMES freetype PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
    if(FREETYPE_SHARED_LIB_RELEASE)
        set(FREETYPE_FINAL_LIB_RELEASE ${FREETYPE_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(FREETYPE_STATIC_LIB_RELEASE NAMES libfreetype.a PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
        if(FREETYPE_STATIC_LIB_RELEASE)
            set(FREETYPE_FINAL_LIB_RELEASE ${FREETYPE_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(FREETYPE_FINAL_LIB_RELEASE freetype)
        endif()
    endif()

    # --- Dynamic Library Linking for PDFWidget (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(PDFWIDGET_SHARED_LIB_RELEASE NAMES PDFWidget PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
    if(PDFWIDGET_SHARED_LIB_RELEASE)
        set(PDFWIDGET_FINAL_LIB_RELEASE ${PDFWIDGET_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(PDFWIDGET_STATIC_LIB_RELEASE NAMES libPDFWidget.a PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
        if(PDFWIDGET_STATIC_LIB_RELEASE)
            set(PDFWIDGET_FINAL_LIB_RELEASE ${PDFWIDGET_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(PDFWIDGET_FINAL_LIB_RELEASE PDFWidget)
        endif()
    endif()

    # --- Dynamic Library Linking for goo_objs (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(GOO_OBJS_SHARED_LIB_RELEASE NAMES goo_objs PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
    if(GOO_OBJS_SHARED_LIB_RELEASE)
        set(GOO_OBJS_FINAL_LIB_RELEASE ${GOO_OBJS_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(GOO_OBJS_STATIC_LIB_RELEASE NAMES libgoo_objs.a PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
        if(GOO_OBJS_STATIC_LIB_RELEASE)
            set(GOO_OBJS_FINAL_LIB_RELEASE ${GOO_OBJS_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(GOO_OBJS_FINAL_LIB_RELEASE goo_objs)
        endif()
    endif()

    # --- Dynamic Library Linking for ServiceLib (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(SERVICELIB_SHARED_LIB_RELEASE NAMES ServiceLib PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
    if(SERVICELIB_SHARED_LIB_RELEASE)
        set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(SERVICELIB_STATIC_LIB_RELEASE NAMES libServiceLib.a PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
        if(SERVICELIB_STATIC_LIB_RELEASE)
            set(SERVICELIB_FINAL_LIB_RELEASE ${SERVICELIB_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(SERVICELIB_FINAL_LIB_RELEASE ServiceLib)
        endif()
    endif()

    # --- Dynamic Library Linking for Component (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(COMPONENT_SHARED_LIB_RELEASE NAMES Component PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
    if(COMPONENT_SHARED_LIB_RELEASE)
        set(COMPONENT_FINAL_LIB_RELEASE ${COMPONENT_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(COMPONENT_STATIC_LIB_RELEASE NAMES libComponent.a PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
        if(COMPONENT_STATIC_LIB_RELEASE)
            set(COMPONENT_FINAL_LIB_RELEASE ${COMPONENT_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(COMPONENT_FINAL_LIB_RELEASE Component)
        endif()
    endif()

    # --- Dynamic Library Linking for xpdf_objs (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(XPDF_OBJS_SHARED_LIB_RELEASE NAMES xpdf_objs PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
    if(XPDF_OBJS_SHARED_LIB_RELEASE)
        set(XPDF_OBJS_FINAL_LIB_RELEASE ${XPDF_OBJS_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(XPDF_OBJS_STATIC_LIB_RELEASE NAMES libxpdf_objs.a PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
        if(XPDF_OBJS_STATIC_LIB_RELEASE)
            set(XPDF_OBJS_FINAL_LIB_RELEASE ${XPDF_OBJS_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(XPDF_OBJS_FINAL_LIB_RELEASE xpdf_objs)
        endif()
    endif()

    # --- Dynamic Library Linking for EditPasswordOnControl (Release) ---
    # 1. First, search for the shared library (.so)
    find_library(EDITPASSWORDONCONTROL_SHARED_LIB_RELEASE NAMES EditPasswordOnControl PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
    if(EDITPASSWORDONCONTROL_SHARED_LIB_RELEASE)
        set(EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE ${EDITPASSWORDONCONTROL_SHARED_LIB_RELEASE})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(EDITPASSWORDONCONTROL_STATIC_LIB_RELEASE NAMES libEditPasswordOnControl.a PATHS "../../Lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/lib/Release" "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/build/Release")
        if(EDITPASSWORDONCONTROL_STATIC_LIB_RELEASE)
            set(EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE ${EDITPASSWORDONCONTROL_STATIC_LIB_RELEASE})
        else()
            # Fallback if not found (e.g. system library)
            set(EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE EditPasswordOnControl)
        endif()
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:-Wl,--start-group>
        $<$<CONFIG:Release>:${SERVICEFORALGORITHM_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${FOFI_OBJS_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${MODELPAGEITEM_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${FREETYPE_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${PDFWIDGET_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${GOO_OBJS_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${SERVICELIB_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${COMPONENT_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${XPDF_OBJS_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:${EDITPASSWORDONCONTROL_FINAL_LIB_RELEASE}>
        $<$<CONFIG:Release>:-Wl,--end-group>
    )
endif()

if(MSVC)
endif()

# --- End of Release ---

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Gui
    Qt6::Widgets
    Qt6::Sql
    Qt6::Core5Compat
    Qt6::Network
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

    # --- Dynamic Library Linking for fontconfig ---
    # 1. First, search for the shared library (.so)
    find_library(FONTCONFIG_SHARED_LIB NAMES fontconfig PATHS "/usr/local/lib/" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/" "$ENV{HOME}/OpenAA6/Lib/Release")

    if(FONTCONFIG_SHARED_LIB)
        message(STATUS "Found Shared Library: ${FONTCONFIG_SHARED_LIB}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${FONTCONFIG_SHARED_LIB})
    else()
        # 2. If not found, search for the static library (.a)
        find_library(FONTCONFIG_STATIC_LIB NAMES libfontconfig.a PATHS "/usr/local/lib/" "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/" "$ENV{HOME}/OpenAA6/Lib/Release")
        if(FONTCONFIG_STATIC_LIB)
            message(STATUS "Found Static Library: ${FONTCONFIG_STATIC_LIB}")
            target_link_libraries(${PROJECT_NAME} PRIVATE ${FONTCONFIG_STATIC_LIB})
        else()
            message(WARNING "Library fontconfig not found!")
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

