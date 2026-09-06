# CMakeLists.txt generated from PDFWidget.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(PDFWidget LANGUAGES CXX)

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
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

# Find OpenMP
find_package(OpenMP REQUIRED)

set(PROJECT_SOURCES
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/Splash.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashBitmap.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashClip.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashFont.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashFontEngine.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashFontFile.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashFontFileID.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashFTFont.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashFTFontEngine.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashFTFontFile.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashPath.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashPattern.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashScreen.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashState.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashXPath.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/splash/SplashXPathScanner.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf-qt/QtPDFCore.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf-qt/XpdfWidget.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf-qt/XpdfWidgetPrint.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/AcroForm.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Annot.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Array.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/BuiltinFont.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/BuiltinFontTables.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Catalog.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/CharCodeToUnicode.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/CMap.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Decrypt.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Dict.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/DisplayState.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Error.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/FontEncodingTables.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Function.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Gfx.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/GfxFont.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/GfxState.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/GlobalParams.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/HTMLGen.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/ImageOutputDev.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/JArithmeticDecoder.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/JBIG2Stream.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/JPXStream.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Lexer.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Link.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/LocalParams.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/NameToCharCode.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Object.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/OptionalContent.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Outline.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/OutputDev.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Page.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Parser.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/PDF417Barcode.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/PDFCore.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/pdfdetach.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/PDFDoc.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/PDFDocEncoding.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/pdffonts.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/pdfimages.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/pdfinfo.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/pdftohtml.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/pdftopng.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/pdftoppm.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/pdftops.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/pdftotext.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/PreScanOutputDev.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/PSOutputDev.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/PSTokenizer.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/SecurityHandler.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/ShadingImage.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/SplashOutputDev.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Stream.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/TextOutputDev.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/TextString.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/TileCache.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/TileCompositor.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/TileMap.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/UnicodeMap.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/UnicodeRemapping.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/UnicodeTypeTable.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/UTF8.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/WebFont.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/XFAScanner.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/XRef.cc"
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf/Zoox.cc"
)

set(PROJECT_HEADERS
    "../../../../OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf-qt/XpdfWidget.h"
)

# Define the target
add_library(${PROJECT_NAME} STATIC
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
        "PDFWIDGET_LIB"
    >
)

if(MSVC)
endif()

# --- End of Debug ---

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../Lib/Release"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../Lib/Release"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../Lib/Release"
)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../Lib/Release"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../Lib/Release"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../Lib/Release"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/build"
        "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/goo"
        "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/fofi"
        "$ENV{HOME}/OpenAA-OtherLibrary/FreeType/freetype-2.14.3/include"
        "$(LIBPNG)"
        "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/splash"
        "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/"
        "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf-qt"
        "$ENV{HOME}/OpenAA-OtherLibrary/PDF/xpdf-4.06/xpdf"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "PDFWIDGET_LIB"
    >
)

if(MSVC)
endif()

# --- End of Release ---

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
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


# =========================================================================
# WARNING: The following MSBuild macros were not resolved during conversion:
#   $(LIBPNG)
# Please define them in CMake or add them to the macro replacements list.
# =========================================================================
