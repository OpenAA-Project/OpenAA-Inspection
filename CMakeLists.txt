# CMakeLists.txt generated from Test1.sln
cmake_minimum_required(VERSION 3.16)

project(Test1 LANGUAGES CXX)

# === Global Build Settings ===
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
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
endif()

# === Independent Parallel Builds (Meta-Build) ===
# デフォルトのビルドタイプを Release に設定 (指定されていない場合)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_custom_target(ServiceLib_ServiceLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ServiceLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ServiceLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ServiceLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/ServiceLib sequentially..."
)

add_custom_target(GUI_DisplayTargetImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayTargetImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayTargetImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayTargetImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayTargetImage sequentially..."
)
add_dependencies(GUI_DisplayTargetImage_build ServiceLib_ServiceLib_build)

add_custom_target(GUI_ButtonExit_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExit" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExit/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExit/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonExit sequentially..."
)
add_dependencies(GUI_ButtonExit_build GUI_DisplayTargetImage_build)

add_custom_target(GUI_ButtonAutoMode_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAutoMode" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAutoMode/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAutoMode/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonAutoMode sequentially..."
)
add_dependencies(GUI_ButtonAutoMode_build GUI_ButtonExit_build)

add_custom_target(GUI_CameraSettingButton_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CameraSettingButton" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CameraSettingButton/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CameraSettingButton/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CameraSettingButton sequentially..."
)
add_dependencies(GUI_CameraSettingButton_build GUI_ButtonAutoMode_build)

add_custom_target(InspectionPlayer_InspectionFastPlayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/InspectionPlayer/InspectionFastPlayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/InspectionPlayer/InspectionFastPlayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/InspectionPlayer/InspectionFastPlayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building InspectionPlayer/InspectionFastPlayer sequentially..."
)
add_dependencies(InspectionPlayer_InspectionFastPlayer_build GUI_CameraSettingButton_build)

add_custom_target(PluginDLL_Camera_CameraMVSGigE_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraMVSGigE" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraMVSGigE/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraMVSGigE/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraMVSGigE sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraMVSGigE_build InspectionPlayer_InspectionFastPlayer_build)

add_custom_target(ServiceLib_ServiceForDBLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ServiceForDBLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ServiceForDBLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ServiceForDBLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/ServiceForDBLib sequentially..."
)
add_dependencies(ServiceLib_ServiceForDBLib_build PluginDLL_Camera_CameraMVSGigE_build)

add_custom_target(ResultDLL_ResultXMLV3_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLV3" -B "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLV3/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLV3/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ResultDLL/ResultXMLV3 sequentially..."
)
add_dependencies(ResultDLL_ResultXMLV3_build ServiceLib_ServiceForDBLib_build)

add_custom_target(ServiceLib_NetworkDrive_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/NetworkDrive" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/NetworkDrive/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/NetworkDrive/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/NetworkDrive sequentially..."
)
add_dependencies(ServiceLib_NetworkDrive_build ResultDLL_ResultXMLV3_build)

add_custom_target(Filter_FilterBrightnessLogConvert_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterBrightnessLogConvert" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterBrightnessLogConvert/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterBrightnessLogConvert/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterBrightnessLogConvert sequentially..."
)
add_dependencies(Filter_FilterBrightnessLogConvert_build ServiceLib_NetworkDrive_build)

add_custom_target(Filter_FilterBrightnessThresholdConvert_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterBrightnessThresholdConvert" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterBrightnessThresholdConvert/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterBrightnessThresholdConvert/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterBrightnessThresholdConvert sequentially..."
)
add_dependencies(Filter_FilterBrightnessThresholdConvert_build Filter_FilterBrightnessLogConvert_build)

add_custom_target(Filter_FilterConvertResolution_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterConvertResolution" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterConvertResolution/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterConvertResolution/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterConvertResolution sequentially..."
)
add_dependencies(Filter_FilterConvertResolution_build Filter_FilterBrightnessThresholdConvert_build)

add_custom_target(Filter_FilterDifferencialHV_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterDifferencialHV" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterDifferencialHV/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterDifferencialHV/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterDifferencialHV sequentially..."
)
add_dependencies(Filter_FilterDifferencialHV_build Filter_FilterConvertResolution_build)

add_custom_target(Filter_FilterDynamicBrightness_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterDynamicBrightness" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterDynamicBrightness/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterDynamicBrightness/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterDynamicBrightness sequentially..."
)
add_dependencies(Filter_FilterDynamicBrightness_build Filter_FilterDifferencialHV_build)

add_custom_target(Filter_FilterEdgeEmphasize_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterEdgeEmphasize" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterEdgeEmphasize/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterEdgeEmphasize/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterEdgeEmphasize sequentially..."
)
add_dependencies(Filter_FilterEdgeEmphasize_build Filter_FilterDynamicBrightness_build)

add_custom_target(Filter_FilterEvenOdd_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterEvenOdd" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterEvenOdd/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterEvenOdd/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterEvenOdd sequentially..."
)
add_dependencies(Filter_FilterEvenOdd_build Filter_FilterEdgeEmphasize_build)

add_custom_target(Filter_FilterHorizontalBand_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHorizontalBand" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHorizontalBand/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHorizontalBand/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterHorizontalBand sequentially..."
)
add_dependencies(Filter_FilterHorizontalBand_build Filter_FilterEvenOdd_build)

add_custom_target(Filter_FilterHorizontalLinear_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHorizontalLinear" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHorizontalLinear/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHorizontalLinear/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterHorizontalLinear sequentially..."
)
add_dependencies(Filter_FilterHorizontalLinear_build Filter_FilterHorizontalBand_build)

add_custom_target(Filter_FilterHResolution_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHResolution" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHResolution/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHResolution/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterHResolution sequentially..."
)
add_dependencies(Filter_FilterHResolution_build Filter_FilterHorizontalLinear_build)

add_custom_target(Filter_FilterHSV_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHSV" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHSV/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHSV/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterHSV sequentially..."
)
add_dependencies(Filter_FilterHSV_build Filter_FilterHResolution_build)

add_custom_target(Filter_FilterImageShading_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShading" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShading/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShading/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterImageShading sequentially..."
)
add_dependencies(Filter_FilterImageShading_build Filter_FilterHSV_build)

add_custom_target(Filter_FilterImageShadingArea_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShadingArea" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShadingArea/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShadingArea/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterImageShadingArea sequentially..."
)
add_dependencies(Filter_FilterImageShadingArea_build Filter_FilterImageShading_build)

add_custom_target(Filter_FilterImageShadingDynamic_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShadingDynamic" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShadingDynamic/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShadingDynamic/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterImageShadingDynamic sequentially..."
)
add_dependencies(Filter_FilterImageShadingDynamic_build Filter_FilterImageShadingArea_build)

add_custom_target(Filter_FilterLineShading_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterLineShading" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterLineShading/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterLineShading/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterLineShading sequentially..."
)
add_dependencies(Filter_FilterLineShading_build Filter_FilterImageShadingDynamic_build)

add_custom_target(Filter_FilterMatchColorBandDynamically_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMatchColorBandDynamically" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMatchColorBandDynamically/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMatchColorBandDynamically/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterMatchColorBandDynamically sequentially..."
)
add_dependencies(Filter_FilterMatchColorBandDynamically_build Filter_FilterLineShading_build)

add_custom_target(Filter_FilterMedianSmooth_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMedianSmooth" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMedianSmooth/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMedianSmooth/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterMedianSmooth sequentially..."
)
add_dependencies(Filter_FilterMedianSmooth_build Filter_FilterMatchColorBandDynamically_build)

add_custom_target(Filter_FilterMergeColor_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMergeColor" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMergeColor/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMergeColor/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterMergeColor sequentially..."
)
add_dependencies(Filter_FilterMergeColor_build Filter_FilterMedianSmooth_build)

add_custom_target(Filter_FilterMoveImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMoveImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMoveImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMoveImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterMoveImage sequentially..."
)
add_dependencies(Filter_FilterMoveImage_build Filter_FilterMergeColor_build)

add_custom_target(Filter_FilterMultiConvertBrightness_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMultiConvertBrightness" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMultiConvertBrightness/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMultiConvertBrightness/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterMultiConvertBrightness sequentially..."
)
add_dependencies(Filter_FilterMultiConvertBrightness_build Filter_FilterMoveImage_build)

add_custom_target(Filter_FilterNothing_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterNothing" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterNothing/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterNothing/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterNothing sequentially..."
)
add_dependencies(Filter_FilterNothing_build Filter_FilterMultiConvertBrightness_build)

add_custom_target(Filter_FilterOneLayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterOneLayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterOneLayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterOneLayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterOneLayer sequentially..."
)
add_dependencies(Filter_FilterOneLayer_build Filter_FilterNothing_build)

add_custom_target(Filter_FilterReduceVStripe_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReduceVStripe" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReduceVStripe/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReduceVStripe/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReduceVStripe sequentially..."
)
add_dependencies(Filter_FilterReduceVStripe_build Filter_FilterOneLayer_build)

add_custom_target(Filter_FilterRemoveNoiseLine_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterRemoveNoiseLine" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterRemoveNoiseLine/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterRemoveNoiseLine/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterRemoveNoiseLine sequentially..."
)
add_dependencies(Filter_FilterRemoveNoiseLine_build Filter_FilterReduceVStripe_build)

add_custom_target(Filter_FilterReplaceColor_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReplaceColor" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReplaceColor/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReplaceColor/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReplaceColor sequentially..."
)
add_dependencies(Filter_FilterReplaceColor_build Filter_FilterRemoveNoiseLine_build)

add_custom_target(Filter_FilterReverseCosineRing_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseCosineRing" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseCosineRing/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseCosineRing/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReverseCosineRing sequentially..."
)
add_dependencies(Filter_FilterReverseCosineRing_build Filter_FilterReplaceColor_build)

add_custom_target(Filter_FilterReverseLens_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLens" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLens/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLens/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReverseLens sequentially..."
)
add_dependencies(Filter_FilterReverseLens_build Filter_FilterReverseCosineRing_build)

add_custom_target(Filter_FilterReverseLensOneLayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneLayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneLayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneLayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReverseLensOneLayer sequentially..."
)
add_dependencies(Filter_FilterReverseLensOneLayer_build Filter_FilterReverseLens_build)

add_custom_target(Filter_FilterReverseLensOneSide_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneSide" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneSide/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneSide/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReverseLensOneSide sequentially..."
)
add_dependencies(Filter_FilterReverseLensOneSide_build Filter_FilterReverseLensOneLayer_build)

add_custom_target(Filter_FilterReverseLensOneSide2_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneSide2" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneSide2/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneSide2/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReverseLensOneSide2 sequentially..."
)
add_dependencies(Filter_FilterReverseLensOneSide2_build Filter_FilterReverseLensOneSide_build)

add_custom_target(Filter_FilterReverseLensSomeLayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensSomeLayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensSomeLayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensSomeLayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReverseLensSomeLayer sequentially..."
)
add_dependencies(Filter_FilterReverseLensSomeLayer_build Filter_FilterReverseLensOneSide2_build)

add_custom_target(Filter_FilterRotationMirror_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterRotationMirror" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterRotationMirror/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterRotationMirror/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterRotationMirror sequentially..."
)
add_dependencies(Filter_FilterRotationMirror_build Filter_FilterReverseLensSomeLayer_build)

add_custom_target(Filter_FilterShiftByLayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShiftByLayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShiftByLayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShiftByLayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterShiftByLayer sequentially..."
)
add_dependencies(Filter_FilterShiftByLayer_build Filter_FilterRotationMirror_build)

add_custom_target(Filter_FilterShiftVBand_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShiftVBand" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShiftVBand/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShiftVBand/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterShiftVBand sequentially..."
)
add_dependencies(Filter_FilterShiftVBand_build Filter_FilterShiftByLayer_build)

add_custom_target(Filter_FilterShrinkImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShrinkImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShrinkImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShrinkImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterShrinkImage sequentially..."
)
add_dependencies(Filter_FilterShrinkImage_build Filter_FilterShiftVBand_build)

add_custom_target(Filter_FilterSmoothing_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterSmoothing" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterSmoothing/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterSmoothing/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterSmoothing sequentially..."
)
add_dependencies(Filter_FilterSmoothing_build Filter_FilterShrinkImage_build)

add_custom_target(Filter_FilterSmoothLarge_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterSmoothLarge" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterSmoothLarge/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterSmoothLarge/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterSmoothLarge sequentially..."
)
add_dependencies(Filter_FilterSmoothLarge_build Filter_FilterSmoothing_build)

add_custom_target(Filter_FilterUDColorShift_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterUDColorShift" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterUDColorShift/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterUDColorShift/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterUDColorShift sequentially..."
)
add_dependencies(Filter_FilterUDColorShift_build Filter_FilterSmoothLarge_build)

add_custom_target(Filter_FilterUpsideDown_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterUpsideDown" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterUpsideDown/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterUpsideDown/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterUpsideDown sequentially..."
)
add_dependencies(Filter_FilterUpsideDown_build Filter_FilterUDColorShift_build)

add_custom_target(Filter_FilterVBand_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVBand" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVBand/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVBand/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterVBand sequentially..."
)
add_dependencies(Filter_FilterVBand_build Filter_FilterUpsideDown_build)

add_custom_target(Filter_FilterVBandOneLayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVBandOneLayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVBandOneLayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVBandOneLayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterVBandOneLayer sequentially..."
)
add_dependencies(Filter_FilterVBandOneLayer_build Filter_FilterVBand_build)

add_custom_target(Filter_FilterVerticalLinear_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVerticalLinear" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVerticalLinear/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVerticalLinear/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterVerticalLinear sequentially..."
)
add_dependencies(Filter_FilterVerticalLinear_build Filter_FilterVBandOneLayer_build)

add_custom_target(Filter_FilterVerticalReverse_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVerticalReverse" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVerticalReverse/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVerticalReverse/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterVerticalReverse sequentially..."
)
add_dependencies(Filter_FilterVerticalReverse_build Filter_FilterVerticalLinear_build)

