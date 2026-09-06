# CMakeLists.txt generated from ServiceLib.vcxproj
# WARNING: This is an automatically generated file. Manual edits may be overwritten.
# VCXPROJ-to-CMAKE limitations:
# - MSBuild macros (e.g., $(SolutionDir)) may not be translated correctly.
# - Complex conditions (custom platforms, etc.) are likely ignored.
# - Linked libraries (e.g., system libs, other projects) may be incomplete.

cmake_minimum_required(VERSION 3.16)

project(ServiceLib LANGUAGES CXX)

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
find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets Core5Compat Gui Sql)

# Find OpenMP
find_package(OpenMP REQUIRED)

set(PROJECT_SOURCES
    "../../GeneralSource/X3DCommon.cpp"
    "../../GeneralSource/XAlgorithmWindow.cpp"
    "../../GeneralSource/XAuthentication.cpp"
    "../../GeneralSource/XCameraHandle.cpp"
    "../../GeneralSource/XClipboard.cpp"
    "../../GeneralSource/XColorConvert.cpp"
    "../../GeneralSource/XControlPoints.cpp"
    "../../GeneralSource/XCrossObj.cpp"
    "../../GeneralSource/XCSVGui.cpp"
    "../../GeneralSource/XDataAlgorithmConfirm.cpp"
    "../../GeneralSource/XDataAlgorithmList.cpp"
    "../../GeneralSource/XDataAlgorithmPipe.cpp"
    "../../GeneralSource/XDataAlgorithmThreshold.cpp"
    "../../GeneralSource/XDataComponent.cpp"
    "../../GeneralSource/XDataInLayer2.cpp"
    "../../GeneralSource/XDataInLayerComm.cpp"
    "../../GeneralSource/XDataInLayerForDebug.cpp"
    "../../GeneralSource/XDataInLayerNoOptimized.cpp"
    "../../GeneralSource/XDataInLayerStructor.cpp"
    "../../GeneralSource/XDataInLayerToDisplayImage.cpp"
    "../../GeneralSource/XDateTime.cpp"
    "../../GeneralSource/XDFS.cpp"
    "../../GeneralSource/XDisplayImageOptimized.cpp"
    "../../GeneralSource/XDisplaySimPanel.cpp"
    "../../GeneralSource/XDLLManager.cpp"
    "../../GeneralSource/XDLLType.cpp"
    "../../GeneralSource/XDrawFunc.cpp"
    "../../GeneralSource/XEntryPoint.cpp"
    "../../GeneralSource/XErrorMessage.cpp"
    "../../GeneralSource/XFFT1d.cpp"
    "../../GeneralSource/XFileThread.cpp"
    "../../GeneralSource/XFlexAreaFast.cpp"
    "../../GeneralSource/XFlexAreaHough.cpp"
    "../../GeneralSource/XFlexAreaImageBuffer.cpp"
    "../../GeneralSource/XFloatShort.cpp"
    "../../GeneralSource/XForWindowsLib.cpp"
    "../../GeneralSource/XGeneralFunc2.cpp"
    "../../GeneralSource/XGeneralFuncCore.cpp"
    "../../GeneralSource/XGeneralWidget.cpp"
    "../../GeneralSource/XGUIComponent.cpp"
    "../../GeneralSource/XGUIFormBase.cpp"
    "../../GeneralSource/XGUIPacketGeneral.cpp"
    "../../GeneralSource/XImagePNG.cpp"
    "../../GeneralSource/XImageProcess.cpp"
    "../../GeneralSource/XImageProcess2.cpp"
    "../../GeneralSource/XImageProcess3.cpp"
    "../../GeneralSource/XInterpolation.cpp"
    "../../GeneralSource/XLanguageStockerLoader.cpp"
    "../../GeneralSource/XLevel.cpp"
    "../../GeneralSource/XLineMatching.cpp"
    "../../GeneralSource/XLotInformation.cpp"
    "../../GeneralSource/XMainGUIFormBase.cpp"
    "../../GeneralSource/XManualExecuter.cpp"
    "../../GeneralSource/XMapBuffer.cpp"
    "../../GeneralSource/XMasterData.cpp"
    "../../GeneralSource/XMasterDataInfo.cpp"
    "../../GeneralSource/XMemoryStream.cpp"
    "../../GeneralSource/XMultiLayerColor.cpp"
    "../../GeneralSource/XOpenSaveDialog.cpp"
    "../../GeneralSource/XParameterHelp.cpp"
    "../../GeneralSource/XPointerAsm.cpp"
    "../../GeneralSource/XPrinterDLLBaseClass.cpp"
    "../../GeneralSource/XPrinterManager.cpp"
    "../../GeneralSource/XProcess.cpp"
    "../../GeneralSource/XQuickBuffer.cpp"
    "../../GeneralSource/XRegulation.cpp"
    "../../GeneralSource/XReportedTopic.cpp"
    "../../GeneralSource/XResize.cpp"
    "../../GeneralSource/XResultAnalizer.cpp"
    "../../GeneralSource/XResultCompress.cpp"
    "../../GeneralSource/XRobotClass.cpp"
    "../../GeneralSource/XRobotControl.cpp"
    "../../GeneralSource/XShadowControlInterface.cpp"
    "../../GeneralSource/XShadowTree.cpp"
    "../../GeneralSource/XShareMasterData.cpp"
    "../../GeneralSource/XSort.cpp"
    "../../GeneralSource/XStatistic.cpp"
    "../../GeneralSource/XTransferCommand.cpp"
    "../../GeneralSource/XTransferPacket.cpp"
    "../../GeneralSource/XTransFile.cpp"
    "../../GeneralSource/XTransform.cpp"
    "../../GeneralSource/XTransSocket.cpp"
    "../../GeneralSource/XUndo.cpp"
    "../../Open/XGUILanguage.cpp"
    "../ForWindows/XForWindows.cpp"
    "AlertDialog.cpp"
    "EditItemIDDialog.cpp"
    "EditStatusDialog.cpp"
    "EditTextMessages.cpp"
    "GUITurnUpDownForm.cpp"
    "InputPasswordForm.cpp"
    "LibFolderForm.cpp"
    "LibFolderInputForm.cpp"
    "MessageBoxStringList.cpp"
    "OnProcessingForm.cpp"
    "ParameterHelpDialog.cpp"
    "Regulus64Version.cpp"
    "SelectAlgorithmDialog.cpp"
    "SelectLibFolderDialog.cpp"
    "SelectLibrariesForAnyType.cpp"
    "SelectLibraryForm.cpp"
    "SelectLibraryOneDialog.cpp"
    "SelectMasterNoDialog.cpp"
    "SelectOneLibratyForAnyTypeForm.cpp"
    "SelectPhasePageLayerDialog.cpp"
    "SelectTabTop.cpp"
    "SelectThresholdLevelDialog.cpp"
    "SelectThresholdParentLevelDialog.cpp"
    "SelectTransferHostDialog.cpp"
    "ServiceLib.cpp"
    "ServiceLibResource.cpp"
    "SetThresholdLevelForm.cpp"
    "ShowLoadingDLLForm.cpp"
    "../../GeneralSource/XAffin.cpp"
    "../../GeneralSource/XAlgorithmBase.cpp"
    "../../GeneralSource/XAlgorithmLibNGType.cpp"
    "../../GeneralSource/XAlgorithmLibrary.cpp"
    "../../GeneralSource/XAnyData.cpp"
    "../../GeneralSource/XArrangementFromFile.cpp"
    "../../GeneralSource/XBitImageProcessor.cpp"
    "../../GeneralSource/XBoolList.cpp"
    "../../GeneralSource/XBsearch.cpp"
    "../../GeneralSource/XCameraClass.cpp"
    "../../GeneralSource/XColorSpace.cpp"
    "../../GeneralSource/XCritialFunc.cpp"
    "../../GeneralSource/XCSV.cpp"
    "../../GeneralSource/XDataAlgorithm.cpp"
    "../../GeneralSource/XDataBase.cpp"
    "../../GeneralSource/XDatabaseLoader.cpp"
    "../../GeneralSource/XDataInExecuter.cpp"
    "../../GeneralSource/XDataInLayer.cpp"
    "../../GeneralSource/XDataInLayerCommander.cpp"
    "../../GeneralSource/XDataInLayerImage.cpp"
    "../../GeneralSource/XDirectCommPacket.cpp"
    "../../GeneralSource/XDisplayBitImage.cpp"
    "../../GeneralSource/XDLLOnly.cpp"
    "../../GeneralSource/XDot.cpp"
    "../../GeneralSource/XDoubleClass.cpp"
    "../../GeneralSource/XDualIntList.cpp"
    "../../GeneralSource/XErrorCode.cpp"
    "../../GeneralSource/XExecuteInspectBase.cpp"
    "../../GeneralSource/XFifoClass.cpp"
    "../../GeneralSource/XFileRegistry.cpp"
    "../../GeneralSource/XFilterClass.cpp"
    "../../GeneralSource/XFilterManager.cpp"
    "../../GeneralSource/XFlexArea.cpp"
    "../../GeneralSource/XFlexAreaImage.cpp"
    "../../GeneralSource/XFlexAreaNoOptimize.cpp"
    "../../GeneralSource/XFormOperator.cpp"
    "../../GeneralSource/XGeneralDialog.cpp"
    "../../GeneralSource/XGeneralFunc.cpp"
    "../../GeneralSource/XGeneralStocker.cpp"
    "../../GeneralSource/XGUICommon.cpp"
    "../../GeneralSource/XGUIPacketForDLL.cpp"
    "../../GeneralSource/XHistgramByParam.cpp"
    "../../GeneralSource/XImageBufferFunctions.cpp"
    "../../GeneralSource/XImageStocker.cpp"
    "../../GeneralSource/XIntClass.cpp"
    "../../GeneralSource/XLanguageClass.cpp"
    "../../GeneralSource/XLearningRegist.cpp"
    "../../GeneralSource/XLearningRule.cpp"
    "../../GeneralSource/XLibraryType.cpp"
    "../../GeneralSource/XLightClass.cpp"
    "../../GeneralSource/XLogo.cpp"
    "../../GeneralSource/XLogOut.cpp"
    "../../GeneralSource/XMacroExecuter.cpp"
    "../../GeneralSource/XMainSchemeMemory.cpp"
    "../../GeneralSource/XMultiEquSolve.cpp"
    "../../GeneralSource/XOutlineOffset.cpp"
    "../../GeneralSource/XParamBase.cpp"
    "../../GeneralSource/XParamDatabase.cpp"
    "../../GeneralSource/XParamGlobal.cpp"
    "../../GeneralSource/XPassword.cpp"
    "../../GeneralSource/XPieceArchitect.cpp"
    "../../GeneralSource/XPieceArchitect2.cpp"
    "../../GeneralSource/XPointer.cpp"
    "../../GeneralSource/XPSpline.cpp"
    "../../GeneralSource/XRememberer.cpp"
    "../../GeneralSource/XResult.cpp"
    "../../GeneralSource/XResultDLLManager.cpp"
    "../../GeneralSource/XServiceForLayers.cpp"
    "../../GeneralSource/XStatusController.cpp"
    "../../GeneralSource/XStrTo.cpp"
    "../../GeneralSource/XSyncGUI.cpp"
    "../../GeneralSource/XTransfer.cpp"
    "../../GeneralSource/XTreeLines.cpp"
    "../../GeneralSource/XtunnelItemfunc.cpp"
    "../../GeneralSource/XVector.cpp"
    "../../GeneralSource/XWriteResultThread.cpp"
    "../../GeneralSource/XYCross.cpp"
    "XNormal.cpp"
)

set(PROJECT_HEADERS
    "../../GeneralSource/XAlgorithmInterfaceDLL.h"
    "../../GeneralSource/XAuthenticationInside.h"
    "../../GeneralSource/XDataInLayerCmdLocal.h"
    "../../GeneralSource/XGUIInterfaceDLL.h"
    "../../GeneralSource/XLightInterfaceDLL.h"
    "../../GeneralSource/XMatrix.h"
    "../../GeneralSource/XResultInterfaceDLL.h"
    "../../GeneralSource/XShadowControlInterface.h"
    "../../Open/NListComp.h"
    "../../Open/Regulus64System.h"
    "../../Open/X3DCommon.h"
    "../../Open/XAlgorithmCommon.h"
    "../../Open/XAllocationLibByColor.h"
    "../../Open/XAuthentication.h"
    "../../Open/XBsearch.h"
    "../../Open/XColorConvert.h"
    "../../Open/XControlPoints.h"
    "../../Open/XDataAlgorithmConfirm.h"
    "../../Open/XDataAlgorithmList.h"
    "../../Open/XDataAlgorithmPipe.h"
    "../../Open/XDataAlgorithmThreshold.h"
    "../../Open/XDataComponent.h"
    "../../Open/XDataInLayerCommander.h"
    "../../Open/XDataInLayerToDisplayImage.h"
    "../../Open/XDateTime.h"
    "../../Open/XDFS.h"
    "../../Open/XDLLManager.h"
    "../../Open/XDrawFunc.h"
    "../../Open/XEntryPoint.h"
    "../../Open/XErrorMessage.h"
    "../../Open/XExcelStringList.h"
    "../../Open/XFileThread.h"
    "../../Open/XFilterInstance.h"
    "../../Open/XFlexAreaHough.h"
    "../../Open/XFlexAreaImageBuffer.h"
    "../../Open/XFloatShort.h"
    "../../Open/XGeneralFuncCore.h"
    "../../Open/XGeneralStockerClass.h"
    "../../Open/XGUIDirectMessage.h"
    "../../Open/XGUILanguage.h"
    "../../Open/XGUIPacketGeneral.h"
    "../../Open/XHaspLib.h"
    "../../Open/XHistgramByParamTemplate.h"
    "../../Open/XImageExpand.h"
    "../../Open/XImagePNG.h"
    "../../Open/XImagePngDef.h"
    "../../Open/XLanguageStockerLoader.h"
    "../../Open/XLearningServerComm.h"
    "../../Open/XLevel.h"
    "../../Open/XLineMatching.h"
    "../../Open/XMacro.h"
    "../../Open/XManualExecuter.h"
    "../../Open/XMapBuffer.h"
    "../../Open/XMasterData.h"
    "../../Open/XMemoryStream.h"
    "../../Open/XMLGeneralFunc.h"
    "../../Open/XMultiLayerColor.h"
    "../../Open/XOpenAA.h"
    "../../Open/XParameterHelp.h"
    "../../Open/XPrinterDLLBaseClass.h"
    "../../Open/XPrinterManager.h"
    "../../Open/XPSpline.h"
    "../../Open/XQuickBuffer.h"
    "../../Open/XRegulation.h"
    "../../Open/XResize.h"
    "../../Open/XResultAnalizer.h"
    "../../Open/XResultDLLManager.h"
    "../../Open/XRobotControl.h"
    "../../Open/XShadowTree.h"
    "../../Open/XShareMasterData.h"
    "../../Open/XStandardCommand.h"
    "../../Open/XStatistic.h"
    "../../Open/XTransform.h"
    "XNormal.h"
    "../../Open/NList.h"
    "../../Open/XLotInformation.h"
    "../../Open/XReportedTopic.h"
    "../../Open/XStandardPropertyForm.h"
    "../../Open/XUndo.h"
    "../../Open/XUndoBase.h"
    "../../Open/XUnicodeGeneralFunc.h"
    "ServiceLib.h"
    "servicelib_global.h"
    "ServiceLibResource.h"
    "../../Open/swap.h"
    "../../Open/XAlgorithmLibNGType.h"
    "../../Open/XAlgorithmLibrary.h"
    "../../Open/XAnyData.h"
    "../../Open/XArrangementDLL.h"
    "../../Open/XArrangementFromFile.h"
    "../../Open/XBitImageProcessor.h"
    "../../Open/XBoolList.h"
    "../../Open/XCameraCommon.h"
    "../../Open/XColorSpace.h"
    "../../Open/XComplex.h"
    "../../Open/XCriticalFunc.h"
    "../../Open/XCrossObj.h"
    "../../Open/XCSV.h"
    "../../Open/XDataAlgorithm.h"
    "../../Open/XDatabase.h"
    "../../Open/XDatabaseLoader.h"
    "../../Open/XDatabaseType.h"
    "../../Open/XDirectCommPacket.h"
    "../../Open/XDisplayBitImage.h"
    "../../Open/XDot.h"
    "../../Open/XDoubleClass.h"
    "../../Open/XDualIntList.h"
    "../../Open/XFFT1d.h"
    "../../Open/XFifoClass.h"
    "../../Open/XFileRegistry.h"
    "../../Open/XFilterClass.h"
    "../../GeneralSource/XFilterManager.h"
    "../../Open/XFlexAreaImage.h"
    "../../Open/XFormOperator.h"
    "../../Open/XGeneralStocker.h"
    "../../Open/XHistgramByParam.h"
    "../../Open/XImageBufferFunctions.h"
    "../../Open/XImageProcess.h"
    "../../Open/XImageStocker.h"
    "../../Open/XIntClass.h"
    "../../Open/XInterpolation.h"
    "../../Open/XLanguageClass.h"
    "../../Open/XLearningInPage.h"
    "../../Open/XLearningRegist.h"
    "../../GeneralSource/XLearningRegistPacket.h"
    "../../Open/XLearningRule.h"
    "../../Open/XLibraryType.h"
    "../../GeneralSource/XLinearSolve.h"
    "../../Open/XLogo.h"
    "../../Open/XMacroExecuter.h"
    "../../Open/XMacroFunction.h"
    "../../Open/XMultiEquSolve.h"
    "../../GeneralSource/XNetworkDrive.h"
    "../../Open/XOutlineOffset.h"
    "../../Open/XParamDatabase.h"
    "../../Open/XPieceArchitect.h"
    "../../Open/XPointer.h"
    "../../Open/XRememberer.h"
    "../../Open/XServiceForLayers.h"
    "../../Open/XTreeLines.h"
    "../../Open/XtunnelItemfunc.h"
    "../../Open/XTypeDef.h"
    "../../Open/XVector.h"
    "../../GeneralSource/XCameraInterfaceDLL.h"
    "../../GeneralSource/XTransferInterface.h"
    "../../Open/XDataInLayer.h"
    "../../Open/XAlgorithmWindow.h"
    "../../Open/XCameraClass.h"
    "../../Open/XCameraHandle.h"
    "../../Open/XGeneralDialog.h"
    "../../Open/XGeneralWidget.h"
    "../../Open/XGUIComponent.h"
    "../../Open/XGUIFormBase.h"
    "../../Open/XMainSchemeMemory.h"
    "../../Open/XPassword.h"
    "../../Open/XProcess.h"
    "../../Open/XRobotClass.h"
    "../../Open/XTransFile.h"
    "../../Open/XTransSocket.h"
    "AlertDialog.h"
    "EditStatusDialog.h"
    "EditTextMessages.h"
    "GUITurnUpDownForm.h"
    "InputPasswordForm.h"
    "MessageBoxStringList.h"
    "OnProcessingForm.h"
    "ParameterHelpDialog.h"
    "ShowLoadingDLLForm.h"
    "../../Open/XStatusController.h"
    "../../Open/XSyncGUI.h"
    "../../Open/XWriteResultThread.h"
    "../../Open/XTransfer.h"
    "SelectTransferHostDialog.h"
    "SetThresholdLevelForm.h"
    "LibFolderForm.h"
    "LibFolderInputForm.h"
    "SelectLibFolderDialog.h"
    "SelectLibrariesForAnyType.h"
    "SelectLibraryForm.h"
    "SelectLibraryOneDialog.h"
    "SelectPhasePageLayerDialog.h"
    "SelectTabTop.h"
    "SelectThresholdParentLevelDialog.h"
    "SelectThresholdLevelDialog.h"
    "SelectAlgorithmDialog.h"
    "SelectMasterNoDialog.h"
    "EditItemIDDialog.h"
    "SelectOneLibratyForAnyTypeForm.h"
    "../../Open/XAlgorithmBase.h"
    "../../Open/XExecuteInspectBase.h"
    "../../Open/XGeneralFunc.h"
    "../../Open/XLightClass.h"
    "../../Open/XLogOut.h"
    "../../Open/XDLLType.h"
    "../../Open/XErrorCode.h"
    "../../Open/XFlexArea.h"
    "../../Open/XGUIPacketForDLL.h"
    "../../Open/XParamBase.h"
    "../../Open/XParamGlobal.h"
    "../../Open/XResult.h"
    "../../Open/XYCross.h"
)

set(PROJECT_FORMS
    "AlertDialog.ui"
    "EditItemIDDialog.ui"
    "EditStatusDialog.ui"
    "EditTextMessages.ui"
    "GUITurnUpDownForm.ui"
    "InputPasswordForm.ui"
    "LibFolderForm.ui"
    "LibFolderInputForm.ui"
    "MessageBoxStringList.ui"
    "OnProcessingForm.ui"
    "ParameterHelpDialog.ui"
    "SelectAlgorithmDialog.ui"
    "SelectLibFolderDialog.ui"
    "SelectLibrariesForAnyType.ui"
    "SelectLibraryForm.ui"
    "SelectLibraryOneDialog.ui"
    "SelectMasterNoDialog.ui"
    "SelectOneLibratyForAnyTypeForm.ui"
    "SelectPhasePageLayerDialog.ui"
    "SelectTabTop.ui"
    "SelectThresholdLevelDialog.ui"
    "SelectThresholdParentLevelDialog.ui"
    "SelectTransferHostDialog.ui"
    "SetThresholdLevelForm.ui"
    "ShowLoadingDLLForm.ui"
)

set(PROJECT_RESOURCES
    "ServiceLib.qrc"
)

# Define the target
add_library(${PROJECT_NAME} STATIC
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
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Debug"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Debug"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Debug"
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Debug"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Debug"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Debug"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "../../GUI/ImagePanelTools/GeneratedFiles"
        "../../EditGUI/EditGUILib/GeneratedFiles"
        "./GeneratedFiles/"
        "../../Open"
        "./"
        "../../EditGUI/EditGUI"
        "./GeneratedFiles/$(Configuration)"
        "../../OpenSource/DisplayImage/GeneratedFiles"
        "../../OpenSource/eigen"
        "../../GUI/ImageControlTools"
        "../../Integrator/IntegrationLib"
        "../../OpenSource/LibPNG"
        "../../GUI/ImagePanelTools"
        "./GeneratedFiles"
        "../../ServiceLib/ServiceLib"
        "../../GeneralSource"
        "../../OpenSource/DisplayImage"
        "../../GUI/ImageControlTools/GeneratedFiles"
        "../../OpenSource/Component"
        "../../EditGUI/EditGUI/GeneratedFiles"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:
        "UNICODE"
        "SERVICELIB_LIB"
        "QT_THREAD_SUPPORT"
    >
)

if(MSVC)
endif()

# --- End of Debug ---

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR NOT CMAKE_BUILD_TYPE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Release"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "./GeneratedFiles/"
        "../../../OpenAA-OtherLibrary/LibPNG/lpng1653"
        "../../Open"
        "./"
        "../../EditGUI/EditGUI"
        "./GeneratedFiles/$(Configuration)"
        "../../Integrator/IntegrationLib"
        "../ServiceForAlgorithm"
        "./GeneratedFiles"
        "../../ServiceLib/ServiceLib"
        "../../OpenSource/DisplayImage"
        "../../GeneralSource"
        "../../../OpenAA-OtherLibrary/eigen/eigen-5.0.0/Eigen"
        "../../OpenSource/Component"
    >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        "UNICODE"
        "NO_INLINE_ASSEMBLER"
        "SERVICELIB_LIB"
        "QT_NO_DEBUG"
        "NDEBUG"
        "QT_THREAD_SUPPORT"
    >
)

if(MSVC)
endif()

# --- End of Release ---

target_include_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Template>:
        "./GeneratedFiles/"
        "./GeneratedFiles"
    >
)

if(MSVC)
endif()

# --- End of Template ---

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::Widgets
    Qt6::Core5Compat
    Qt6::Gui
    Qt6::Sql
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
    -O0
    -g
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

