# CMakeLists.txt generated from MainAfterInitial.sln
cmake_minimum_required(VERSION 3.16)

project(MainAfterInitial LANGUAGES CXX)

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

add_custom_target(GUI_MaskingImagePanel_SelectLibraryInMask_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MaskingImagePanel/SelectLibraryInMask" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MaskingImagePanel/SelectLibraryInMask/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MaskingImagePanel/SelectLibraryInMask/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/MaskingImagePanel/SelectLibraryInMask sequentially..."
)

add_custom_target(GUI_LearningLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LearningLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LearningLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LearningLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/LearningLib sequentially..."
)
add_dependencies(GUI_LearningLib_build GUI_MaskingImagePanel_SelectLibraryInMask_build)

add_custom_target(PluginDLL_PIO_NetworkSIOClientLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkSIOClientLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkSIOClientLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkSIOClientLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/NetworkSIOClientLib sequentially..."
)
add_dependencies(PluginDLL_PIO_NetworkSIOClientLib_build GUI_LearningLib_build)

add_custom_target(PluginDLL_PIO_NetworkPIOLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkPIOLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkPIOLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkPIOLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/NetworkPIOLib sequentially..."
)
add_dependencies(PluginDLL_PIO_NetworkPIOLib_build PluginDLL_PIO_NetworkSIOClientLib_build)

add_custom_target(PluginDLL_PIO_SharedPIOLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/SharedPIOLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/SharedPIOLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/SharedPIOLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/SharedPIOLib sequentially..."
)
add_dependencies(PluginDLL_PIO_SharedPIOLib_build PluginDLL_PIO_NetworkPIOLib_build)

add_custom_target(Algorithm_ReviewStructure_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ReviewStructure" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ReviewStructure/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ReviewStructure/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/ReviewStructure sequentially..."
)
add_dependencies(Algorithm_ReviewStructure_build PluginDLL_PIO_SharedPIOLib_build)

add_custom_target(Algorithm_BlockInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/BlockInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/BlockInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/BlockInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/BlockInspection sequentially..."
)
add_dependencies(Algorithm_BlockInspection_build Algorithm_ReviewStructure_build)

add_custom_target(Algorithm_Masking_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Masking" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Masking/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Masking/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/Masking sequentially..."
)
add_dependencies(Algorithm_Masking_build Algorithm_BlockInspection_build)

add_custom_target(Algorithm_Alignment_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Alignment" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Alignment/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Alignment/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/Alignment sequentially..."
)
add_dependencies(Algorithm_Alignment_build Algorithm_Masking_build)

add_custom_target(Algorithm_ColorBlockInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ColorBlockInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ColorBlockInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ColorBlockInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/ColorBlockInspection sequentially..."
)
add_dependencies(Algorithm_ColorBlockInspection_build Algorithm_Alignment_build)

add_custom_target(Algorithm_PieceArchitect_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PieceArchitect" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PieceArchitect/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PieceArchitect/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/PieceArchitect sequentially..."
)
add_dependencies(Algorithm_PieceArchitect_build Algorithm_ColorBlockInspection_build)

add_custom_target(Algorithm_OutlineInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/OutlineInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/OutlineInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/OutlineInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/OutlineInspection sequentially..."
)
add_dependencies(Algorithm_OutlineInspection_build Algorithm_PieceArchitect_build)

add_custom_target(Algorithm_ImageProcessor_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ImageProcessor" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ImageProcessor/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ImageProcessor/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/ImageProcessor sequentially..."
)
add_dependencies(Algorithm_ImageProcessor_build Algorithm_OutlineInspection_build)

add_custom_target(Algorithm_Naming_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Naming" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Naming/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Naming/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/Naming sequentially..."
)
add_dependencies(Algorithm_Naming_build Algorithm_ImageProcessor_build)

add_custom_target(Algorithm_TrueColorBlock_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/TrueColorBlock" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/TrueColorBlock/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/TrueColorBlock/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/TrueColorBlock sequentially..."
)
add_dependencies(Algorithm_TrueColorBlock_build Algorithm_Naming_build)

add_custom_target(Algorithm_MaskingPI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MaskingPI" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MaskingPI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MaskingPI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/MaskingPI sequentially..."
)
add_dependencies(Algorithm_MaskingPI_build Algorithm_TrueColorBlock_build)

add_custom_target(Algorithm_StatisticImager_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/StatisticImager" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/StatisticImager/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/StatisticImager/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/StatisticImager sequentially..."
)
add_dependencies(Algorithm_StatisticImager_build Algorithm_MaskingPI_build)

add_custom_target(Algorithm_AutoAlignment_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoAlignment" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoAlignment/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoAlignment/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/AutoAlignment sequentially..."
)
add_dependencies(Algorithm_AutoAlignment_build Algorithm_StatisticImager_build)

add_custom_target(Algorithm_AreaFilter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AreaFilter" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AreaFilter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AreaFilter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/AreaFilter sequentially..."
)
add_dependencies(Algorithm_AreaFilter_build Algorithm_AutoAlignment_build)

add_custom_target(Algorithm_AutoMaskingPI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoMaskingPI" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoMaskingPI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoMaskingPI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/AutoMaskingPI sequentially..."
)
add_dependencies(Algorithm_AutoMaskingPI_build Algorithm_AreaFilter_build)

add_custom_target(Algorithm_AutoSaveImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoSaveImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoSaveImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoSaveImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/AutoSaveImage sequentially..."
)
add_dependencies(Algorithm_AutoSaveImage_build Algorithm_AutoMaskingPI_build)

add_custom_target(Algorithm_StatisticBlock_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/StatisticBlock" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/StatisticBlock/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/StatisticBlock/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/StatisticBlock sequentially..."
)
add_dependencies(Algorithm_StatisticBlock_build Algorithm_AutoSaveImage_build)

add_custom_target(Algorithm_Learning_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Learning" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Learning/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Learning/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/Learning sequentially..."
)
add_dependencies(Algorithm_Learning_build Algorithm_StatisticBlock_build)

add_custom_target(Algorithm_DynamicMaskingPI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DynamicMaskingPI" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DynamicMaskingPI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DynamicMaskingPI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/DynamicMaskingPI sequentially..."
)
add_dependencies(Algorithm_DynamicMaskingPI_build Algorithm_Learning_build)

add_custom_target(Algorithm_MeasureHole_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MeasureHole" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MeasureHole/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MeasureHole/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/MeasureHole sequentially..."
)
add_dependencies(Algorithm_MeasureHole_build Algorithm_DynamicMaskingPI_build)

add_custom_target(Algorithm_MeasureLineMove_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MeasureLineMove" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MeasureLineMove/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MeasureLineMove/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/MeasureLineMove sequentially..."
)
add_dependencies(Algorithm_MeasureLineMove_build Algorithm_MeasureHole_build)

add_custom_target(Algorithm_EulerRing_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/EulerRing" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/EulerRing/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/EulerRing/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/EulerRing sequentially..."
)
add_dependencies(Algorithm_EulerRing_build Algorithm_MeasureLineMove_build)

add_custom_target(Algorithm_MeasureHolePos_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MeasureHolePos" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MeasureHolePos/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MeasureHolePos/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/MeasureHolePos sequentially..."
)
add_dependencies(Algorithm_MeasureHolePos_build Algorithm_EulerRing_build)

add_custom_target(Algorithm_AreaShader_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AreaShader" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AreaShader/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AreaShader/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/AreaShader sequentially..."
)
add_dependencies(Algorithm_AreaShader_build Algorithm_MeasureHolePos_build)

add_custom_target(Algorithm_ImageChecker_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ImageChecker" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ImageChecker/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ImageChecker/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/ImageChecker sequentially..."
)
add_dependencies(Algorithm_ImageChecker_build Algorithm_AreaShader_build)

add_custom_target(Algorithm_SpotReducer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/SpotReducer" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/SpotReducer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/SpotReducer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/SpotReducer sequentially..."
)
add_dependencies(Algorithm_SpotReducer_build Algorithm_ImageChecker_build)

add_custom_target(Algorithm_MatchingAlignment_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MatchingAlignment" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MatchingAlignment/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MatchingAlignment/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/MatchingAlignment sequentially..."
)
add_dependencies(Algorithm_MatchingAlignment_build Algorithm_SpotReducer_build)

add_custom_target(Algorithm_AutoPCBHoleAligner_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoPCBHoleAligner" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoPCBHoleAligner/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoPCBHoleAligner/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/AutoPCBHoleAligner sequentially..."
)
add_dependencies(Algorithm_AutoPCBHoleAligner_build Algorithm_MatchingAlignment_build)

add_custom_target(Algorithm_ZAxisRegulation_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ZAxisRegulation" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ZAxisRegulation/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ZAxisRegulation/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/ZAxisRegulation sequentially..."
)
add_dependencies(Algorithm_ZAxisRegulation_build Algorithm_AutoPCBHoleAligner_build)

add_custom_target(Algorithm_DotRegulation_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DotRegulation" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DotRegulation/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DotRegulation/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/DotRegulation sequentially..."
)
add_dependencies(Algorithm_DotRegulation_build Algorithm_ZAxisRegulation_build)

add_custom_target(Algorithm_AutoClassify_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoClassify" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoClassify/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AutoClassify/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/AutoClassify sequentially..."
)
add_dependencies(Algorithm_AutoClassify_build Algorithm_DotRegulation_build)

add_custom_target(Algorithm_CategorizedShader_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CategorizedShader" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CategorizedShader/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CategorizedShader/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/CategorizedShader sequentially..."
)
add_dependencies(Algorithm_CategorizedShader_build Algorithm_AutoClassify_build)

add_custom_target(Algorithm_VCutInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/VCutInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/VCutInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/VCutInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/VCutInspection sequentially..."
)
add_dependencies(Algorithm_VCutInspection_build Algorithm_CategorizedShader_build)

add_custom_target(Algorithm_CacheTargetImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CacheTargetImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CacheTargetImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CacheTargetImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/CacheTargetImage sequentially..."
)
add_dependencies(Algorithm_CacheTargetImage_build Algorithm_VCutInspection_build)

add_custom_target(Algorithm_LineEnhancer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LineEnhancer" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LineEnhancer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LineEnhancer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/LineEnhancer sequentially..."
)
add_dependencies(Algorithm_LineEnhancer_build Algorithm_CacheTargetImage_build)

add_custom_target(Algorithm_ARArrange_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ARArrange" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ARArrange/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ARArrange/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/ARArrange sequentially..."
)
add_dependencies(Algorithm_ARArrange_build Algorithm_LineEnhancer_build)

add_custom_target(Algorithm_DynamicClassify_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DynamicClassify" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DynamicClassify/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DynamicClassify/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/DynamicClassify sequentially..."
)
add_dependencies(Algorithm_DynamicClassify_build Algorithm_ARArrange_build)

add_custom_target(Algorithm_PieceForReview_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PieceForReview" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PieceForReview/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PieceForReview/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/PieceForReview sequentially..."
)
add_dependencies(Algorithm_PieceForReview_build Algorithm_DynamicClassify_build)

add_custom_target(Algorithm_PieceReviewSide_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PieceReviewSide" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PieceReviewSide/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PieceReviewSide/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/PieceReviewSide sequentially..."
)
add_dependencies(Algorithm_PieceReviewSide_build Algorithm_PieceForReview_build)

add_custom_target(Algorithm_LineEnhancer1L_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LineEnhancer1L" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LineEnhancer1L/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LineEnhancer1L/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/LineEnhancer1L sequentially..."
)
add_dependencies(Algorithm_LineEnhancer1L_build Algorithm_PieceReviewSide_build)

add_custom_target(Algorithm_OCRInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/OCRInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/OCRInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/OCRInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/OCRInspection sequentially..."
)
add_dependencies(Algorithm_OCRInspection_build Algorithm_LineEnhancer1L_build)

add_custom_target(Algorithm_ResultImportance_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ResultImportance" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ResultImportance/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ResultImportance/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/ResultImportance sequentially..."
)
add_dependencies(Algorithm_ResultImportance_build Algorithm_OCRInspection_build)

add_custom_target(Algorithm_TreeMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/TreeMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/TreeMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/TreeMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/TreeMaster sequentially..."
)
add_dependencies(Algorithm_TreeMaster_build Algorithm_ResultImportance_build)

add_custom_target(Algorithm_BuslineInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/BuslineInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/BuslineInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/BuslineInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/BuslineInspection sequentially..."
)
add_dependencies(Algorithm_BuslineInspection_build Algorithm_TreeMaster_build)

add_custom_target(Algorithm_MakeDifferencialImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MakeDifferencialImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MakeDifferencialImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MakeDifferencialImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/MakeDifferencialImage sequentially..."
)
add_dependencies(Algorithm_MakeDifferencialImage_build Algorithm_BuslineInspection_build)

add_custom_target(Algorithm_ResultBinder_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ResultBinder" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ResultBinder/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ResultBinder/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/ResultBinder sequentially..."
)
add_dependencies(Algorithm_ResultBinder_build Algorithm_MakeDifferencialImage_build)

add_custom_target(Algorithm_AlignmentLarge_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentLarge" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentLarge/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentLarge/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/AlignmentLarge sequentially..."
)
add_dependencies(Algorithm_AlignmentLarge_build Algorithm_ResultBinder_build)

add_custom_target(Algorithm_BCRInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/BCRInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/BCRInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/BCRInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/BCRInspection sequentially..."
)
add_dependencies(Algorithm_BCRInspection_build Algorithm_AlignmentLarge_build)

add_custom_target(Algorithm_PieceDef_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PieceDef" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PieceDef/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PieceDef/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/PieceDef sequentially..."
)
add_dependencies(Algorithm_PieceDef_build Algorithm_BCRInspection_build)

add_custom_target(Algorithm_CheckBrightness_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CheckBrightness" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CheckBrightness/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CheckBrightness/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/CheckBrightness sequentially..."
)
add_dependencies(Algorithm_CheckBrightness_build Algorithm_PieceDef_build)

add_custom_target(Algorithm_GerberFast_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/GerberFast" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/GerberFast/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/GerberFast/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/GerberFast sequentially..."
)
add_dependencies(Algorithm_GerberFast_build Algorithm_CheckBrightness_build)

add_custom_target(Algorithm_VIAInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/VIAInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/VIAInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/VIAInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/VIAInspection sequentially..."
)
add_dependencies(Algorithm_VIAInspection_build Algorithm_GerberFast_build)

add_custom_target(Algorithm_CheckEveryday_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CheckEveryday" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CheckEveryday/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CheckEveryday/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/CheckEveryday sequentially..."
)
add_dependencies(Algorithm_CheckEveryday_build Algorithm_VIAInspection_build)

add_custom_target(Algorithm_MultiFileMap_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MultiFileMap" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MultiFileMap/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MultiFileMap/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/MultiFileMap sequentially..."
)
add_dependencies(Algorithm_MultiFileMap_build Algorithm_CheckEveryday_build)

add_custom_target(Algorithm_ThinMetal_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ThinMetal" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ThinMetal/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ThinMetal/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/ThinMetal sequentially..."
)
add_dependencies(Algorithm_ThinMetal_build Algorithm_MultiFileMap_build)

add_custom_target(PluginDLL_Camera_DummyCamera_DummyCamera_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/DummyCamera/DummyCamera" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/DummyCamera/DummyCamera/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/DummyCamera/DummyCamera/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/DummyCamera/DummyCamera sequentially..."
)
add_dependencies(PluginDLL_Camera_DummyCamera_DummyCamera_build Algorithm_ThinMetal_build)

add_custom_target(PluginDLL_Camera_CameraProvider_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraProvider" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraProvider/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraProvider/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraProvider sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraProvider_build PluginDLL_Camera_DummyCamera_DummyCamera_build)

add_custom_target(PluginDLL_Camera_CameraProvider_CameraFromProvider_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraProvider/CameraFromProvider" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraProvider/CameraFromProvider/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraProvider/CameraFromProvider/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraProvider/CameraFromProvider sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraProvider_CameraFromProvider_build PluginDLL_Camera_CameraProvider_build)

add_custom_target(Filter_FilterSmoothing_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterSmoothing" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterSmoothing/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterSmoothing/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterSmoothing sequentially..."
)
add_dependencies(Filter_FilterSmoothing_build PluginDLL_Camera_CameraProvider_CameraFromProvider_build)

add_custom_target(Filter_FilterEdgeEmphasize_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterEdgeEmphasize" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterEdgeEmphasize/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterEdgeEmphasize/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterEdgeEmphasize sequentially..."
)
add_dependencies(Filter_FilterEdgeEmphasize_build Filter_FilterSmoothing_build)

add_custom_target(Filter_FilterMedianSmooth_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMedianSmooth" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMedianSmooth/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMedianSmooth/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterMedianSmooth sequentially..."
)
add_dependencies(Filter_FilterMedianSmooth_build Filter_FilterEdgeEmphasize_build)

add_custom_target(Filter_FilterReverseLens_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLens" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLens/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLens/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReverseLens sequentially..."
)
add_dependencies(Filter_FilterReverseLens_build Filter_FilterMedianSmooth_build)

add_custom_target(Filter_FilterShrinkImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShrinkImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShrinkImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShrinkImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterShrinkImage sequentially..."
)
add_dependencies(Filter_FilterShrinkImage_build Filter_FilterReverseLens_build)

add_custom_target(Filter_FilterOneLayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterOneLayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterOneLayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterOneLayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterOneLayer sequentially..."
)
add_dependencies(Filter_FilterOneLayer_build Filter_FilterShrinkImage_build)

add_custom_target(Filter_FilterHSV_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHSV" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHSV/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHSV/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterHSV sequentially..."
)
add_dependencies(Filter_FilterHSV_build Filter_FilterOneLayer_build)

add_custom_target(Filter_FilterNothing_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterNothing" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterNothing/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterNothing/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterNothing sequentially..."
)
add_dependencies(Filter_FilterNothing_build Filter_FilterHSV_build)

add_custom_target(Filter_FilterMoveImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMoveImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMoveImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMoveImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterMoveImage sequentially..."
)
add_dependencies(Filter_FilterMoveImage_build Filter_FilterNothing_build)

add_custom_target(Filter_FilterReverseLensOneSide_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneSide" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneSide/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneSide/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReverseLensOneSide sequentially..."
)
add_dependencies(Filter_FilterReverseLensOneSide_build Filter_FilterMoveImage_build)

add_custom_target(Filter_FilterReverseCosineRing_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseCosineRing" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseCosineRing/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseCosineRing/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReverseCosineRing sequentially..."
)
add_dependencies(Filter_FilterReverseCosineRing_build Filter_FilterReverseLensOneSide_build)

add_custom_target(Filter_FilterUpsideDown_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterUpsideDown" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterUpsideDown/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterUpsideDown/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterUpsideDown sequentially..."
)
add_dependencies(Filter_FilterUpsideDown_build Filter_FilterReverseCosineRing_build)

add_custom_target(Filter_FilterSmoothLarge_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterSmoothLarge" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterSmoothLarge/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterSmoothLarge/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterSmoothLarge sequentially..."
)
add_dependencies(Filter_FilterSmoothLarge_build Filter_FilterUpsideDown_build)

add_custom_target(Filter_FilterReverseLensOneLayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneLayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneLayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneLayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReverseLensOneLayer sequentially..."
)
add_dependencies(Filter_FilterReverseLensOneLayer_build Filter_FilterSmoothLarge_build)

add_custom_target(Filter_FilterUDColorShift_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterUDColorShift" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterUDColorShift/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterUDColorShift/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterUDColorShift sequentially..."
)
add_dependencies(Filter_FilterUDColorShift_build Filter_FilterReverseLensOneLayer_build)

add_custom_target(Filter_FilterReverseLensSomeLayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensSomeLayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensSomeLayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensSomeLayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReverseLensSomeLayer sequentially..."
)
add_dependencies(Filter_FilterReverseLensSomeLayer_build Filter_FilterUDColorShift_build)

add_custom_target(Filter_FilterImageShading_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShading" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShading/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShading/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterImageShading sequentially..."
)
add_dependencies(Filter_FilterImageShading_build Filter_FilterReverseLensSomeLayer_build)

add_custom_target(Filter_FilterReverseLensOneSide2_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneSide2" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneSide2/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReverseLensOneSide2/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReverseLensOneSide2 sequentially..."
)
add_dependencies(Filter_FilterReverseLensOneSide2_build Filter_FilterImageShading_build)

add_custom_target(Filter_FilterEvenOdd_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterEvenOdd" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterEvenOdd/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterEvenOdd/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterEvenOdd sequentially..."
)
add_dependencies(Filter_FilterEvenOdd_build Filter_FilterReverseLensOneSide2_build)

add_custom_target(Filter_FilterMultiConvertBrightness_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMultiConvertBrightness" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMultiConvertBrightness/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMultiConvertBrightness/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterMultiConvertBrightness sequentially..."
)
add_dependencies(Filter_FilterMultiConvertBrightness_build Filter_FilterEvenOdd_build)

add_custom_target(Filter_FilterRotationMirror_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterRotationMirror" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterRotationMirror/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterRotationMirror/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterRotationMirror sequentially..."
)
add_dependencies(Filter_FilterRotationMirror_build Filter_FilterMultiConvertBrightness_build)

add_custom_target(Filter_FilterHResolution_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHResolution" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHResolution/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHResolution/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterHResolution sequentially..."
)
add_dependencies(Filter_FilterHResolution_build Filter_FilterRotationMirror_build)

add_custom_target(Filter_FilterVBand_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVBand" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVBand/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVBand/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterVBand sequentially..."
)
add_dependencies(Filter_FilterVBand_build Filter_FilterHResolution_build)

add_custom_target(Filter_FilterHorizontalLinear_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHorizontalLinear" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHorizontalLinear/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHorizontalLinear/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterHorizontalLinear sequentially..."
)
add_dependencies(Filter_FilterHorizontalLinear_build Filter_FilterVBand_build)

add_custom_target(Filter_FilterHorizontalBand_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHorizontalBand" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHorizontalBand/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterHorizontalBand/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterHorizontalBand sequentially..."
)
add_dependencies(Filter_FilterHorizontalBand_build Filter_FilterHorizontalLinear_build)

add_custom_target(Filter_FilterVerticalLinear_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVerticalLinear" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVerticalLinear/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVerticalLinear/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterVerticalLinear sequentially..."
)
add_dependencies(Filter_FilterVerticalLinear_build Filter_FilterHorizontalBand_build)

add_custom_target(Filter_FilterVerticalReverse_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVerticalReverse" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVerticalReverse/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVerticalReverse/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterVerticalReverse sequentially..."
)
add_dependencies(Filter_FilterVerticalReverse_build Filter_FilterVerticalLinear_build)

add_custom_target(GUI_ButtonSaveMasterData_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveMasterData" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveMasterData/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveMasterData/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSaveMasterData sequentially..."
)
add_dependencies(GUI_ButtonSaveMasterData_build Filter_FilterVerticalReverse_build)

add_custom_target(GUI_ButtonLoadMasterData_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMasterData" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMasterData/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMasterData/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLoadMasterData sequentially..."
)
add_dependencies(GUI_ButtonLoadMasterData_build GUI_ButtonSaveMasterData_build)

add_custom_target(GUI_AlignmentImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AlignmentImagePanel sequentially..."
)
add_dependencies(GUI_AlignmentImagePanel_build GUI_ButtonLoadMasterData_build)

add_custom_target(GUI_ButtonSequence_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSequence" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSequence/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSequence/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSequence sequentially..."
)
add_dependencies(GUI_ButtonSequence_build GUI_AlignmentImagePanel_build)

add_custom_target(GUI_ButtonSettingParameters_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSettingParameters" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSettingParameters/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSettingParameters/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSettingParameters sequentially..."
)
add_dependencies(GUI_ButtonSettingParameters_build GUI_ButtonSequence_build)

add_custom_target(GUI_CameraSettingButton_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CameraSettingButton" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CameraSettingButton/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CameraSettingButton/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CameraSettingButton sequentially..."
)
add_dependencies(GUI_CameraSettingButton_build GUI_ButtonSettingParameters_build)

add_custom_target(GUI_DisplayGrayLower_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayGrayLower" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayGrayLower/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayGrayLower/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayGrayLower sequentially..."
)
add_dependencies(GUI_DisplayGrayLower_build GUI_CameraSettingButton_build)

add_custom_target(GUI_DisplayGrayUpper_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayGrayUpper" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayGrayUpper/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayGrayUpper/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayGrayUpper sequentially..."
)
add_dependencies(GUI_DisplayGrayUpper_build GUI_DisplayGrayLower_build)

add_custom_target(GUI_DisplayMasterImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayMasterImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayMasterImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayMasterImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayMasterImage sequentially..."
)
add_dependencies(GUI_DisplayMasterImage_build GUI_DisplayGrayUpper_build)

add_custom_target(GUI_DisplayNGList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayNGList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayNGList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayNGList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayNGList sequentially..."
)
add_dependencies(GUI_DisplayNGList_build GUI_DisplayMasterImage_build)

add_custom_target(GUI_DisplayTargetImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayTargetImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayTargetImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayTargetImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayTargetImage sequentially..."
)
add_dependencies(GUI_DisplayTargetImage_build GUI_DisplayNGList_build)

add_custom_target(GUI_GeneralDisplayWholeImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralDisplayWholeImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralDisplayWholeImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralDisplayWholeImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/GeneralDisplayWholeImage sequentially..."
)
add_dependencies(GUI_GeneralDisplayWholeImage_build GUI_DisplayTargetImage_build)

add_custom_target(GUI_GeneralLabel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralLabel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralLabel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralLabel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/GeneralLabel sequentially..."
)
add_dependencies(GUI_GeneralLabel_build GUI_GeneralDisplayWholeImage_build)

add_custom_target(GUI_GeneralTabSheet_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralTabSheet" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralTabSheet/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralTabSheet/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/GeneralTabSheet sequentially..."
)
add_dependencies(GUI_GeneralTabSheet_build GUI_GeneralLabel_build)

add_custom_target(GUI_ListboxAlgorithm_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxAlgorithm" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxAlgorithm/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxAlgorithm/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ListboxAlgorithm sequentially..."
)
add_dependencies(GUI_ListboxAlgorithm_build GUI_GeneralTabSheet_build)

add_custom_target(GUI_LoadImageMasterButton_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageMasterButton" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageMasterButton/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageMasterButton/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/LoadImageMasterButton sequentially..."
)
add_dependencies(GUI_LoadImageMasterButton_build GUI_ListboxAlgorithm_build)

add_custom_target(GUI_PropertyAlignment_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignment" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignment/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignment/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyAlignment sequentially..."
)
add_dependencies(GUI_PropertyAlignment_build GUI_LoadImageMasterButton_build)

add_custom_target(GUI_SaveImageMasterButton_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveImageMasterButton" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveImageMasterButton/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveImageMasterButton/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SaveImageMasterButton sequentially..."
)
add_dependencies(GUI_SaveImageMasterButton_build GUI_PropertyAlignment_build)

add_custom_target(GUI_StartCaptureButton_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartCaptureButton" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartCaptureButton/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartCaptureButton/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/StartCaptureButton sequentially..."
)
add_dependencies(GUI_StartCaptureButton_build GUI_SaveImageMasterButton_build)

add_custom_target(GUI_ButtonUpdateMasterData_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonUpdateMasterData" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonUpdateMasterData/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonUpdateMasterData/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonUpdateMasterData sequentially..."
)
add_dependencies(GUI_ButtonUpdateMasterData_build GUI_StartCaptureButton_build)

add_custom_target(GUI_BlockImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/BlockImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/BlockImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/BlockImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/BlockImagePanel sequentially..."
)
add_dependencies(GUI_BlockImagePanel_build GUI_ButtonUpdateMasterData_build)

add_custom_target(GUI_MaskingImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MaskingImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MaskingImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MaskingImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/MaskingImagePanel sequentially..."
)
add_dependencies(GUI_MaskingImagePanel_build GUI_BlockImagePanel_build)

add_custom_target(GUI_ButtonSaveAlgorithm_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveAlgorithm" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveAlgorithm/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveAlgorithm/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSaveAlgorithm sequentially..."
)
add_dependencies(GUI_ButtonSaveAlgorithm_build GUI_MaskingImagePanel_build)

add_custom_target(GUI_ButtonLoadAlgorithm_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadAlgorithm" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadAlgorithm/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadAlgorithm/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLoadAlgorithm sequentially..."
)
add_dependencies(GUI_ButtonLoadAlgorithm_build GUI_ButtonSaveAlgorithm_build)

add_custom_target(GUI_ImageControlTools_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImageControlTools" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImageControlTools/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImageControlTools/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ImageControlTools sequentially..."
)
add_dependencies(GUI_ImageControlTools_build GUI_ButtonLoadAlgorithm_build)

add_custom_target(GUI_StartInspectionButton_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartInspectionButton" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartInspectionButton/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartInspectionButton/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/StartInspectionButton sequentially..."
)
add_dependencies(GUI_StartInspectionButton_build GUI_ImageControlTools_build)

add_custom_target(GUI_LoadImageTargetButton_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageTargetButton" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageTargetButton/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageTargetButton/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/LoadImageTargetButton sequentially..."
)
add_dependencies(GUI_LoadImageTargetButton_build GUI_StartInspectionButton_build)

add_custom_target(GUI_StartProcessAgainButton_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartProcessAgainButton" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartProcessAgainButton/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartProcessAgainButton/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/StartProcessAgainButton sequentially..."
)
add_dependencies(GUI_StartProcessAgainButton_build GUI_LoadImageTargetButton_build)

add_custom_target(GUI_ListboxAlgorithmCount_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxAlgorithmCount" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxAlgorithmCount/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxAlgorithmCount/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ListboxAlgorithmCount sequentially..."
)
add_dependencies(GUI_ListboxAlgorithmCount_build GUI_StartProcessAgainButton_build)

add_custom_target(GUI_ButtonExit_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExit" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExit/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExit/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonExit sequentially..."
)
add_dependencies(GUI_ButtonExit_build GUI_ListboxAlgorithmCount_build)

add_custom_target(GUI_TargetImageControlTools_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/TargetImageControlTools" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/TargetImageControlTools/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/TargetImageControlTools/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/TargetImageControlTools sequentially..."
)
add_dependencies(GUI_TargetImageControlTools_build GUI_ButtonExit_build)

add_custom_target(GUI_ShowNGCount_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowNGCount" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowNGCount/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowNGCount/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowNGCount sequentially..."
)
add_dependencies(GUI_ShowNGCount_build GUI_TargetImageControlTools_build)

add_custom_target(GUI_SaveImageTargetButton_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveImageTargetButton" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveImageTargetButton/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveImageTargetButton/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SaveImageTargetButton sequentially..."
)
add_dependencies(GUI_SaveImageTargetButton_build GUI_ShowNGCount_build)

add_custom_target(GUI_ColorBlockImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ColorBlockImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ColorBlockImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ColorBlockImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ColorBlockImagePanel sequentially..."
)
add_dependencies(GUI_ColorBlockImagePanel_build GUI_SaveImageTargetButton_build)

add_custom_target(GUI_PixelImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PixelImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PixelImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PixelImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PixelImagePanel sequentially..."
)
add_dependencies(GUI_PixelImagePanel_build GUI_ColorBlockImagePanel_build)

add_custom_target(GUI_PropertyPixel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPixel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPixel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPixel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyPixel sequentially..."
)
add_dependencies(GUI_PropertyPixel_build GUI_PixelImagePanel_build)

add_custom_target(GUI_GeneralTabWizard_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralTabWizard" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralTabWizard/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralTabWizard/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/GeneralTabWizard sequentially..."
)
add_dependencies(GUI_GeneralTabWizard_build GUI_PropertyPixel_build)

add_custom_target(GUI_PanelOkNg_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelOkNg" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelOkNg/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelOkNg/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PanelOkNg sequentially..."
)
add_dependencies(GUI_PanelOkNg_build GUI_GeneralTabWizard_build)

add_custom_target(GUI_ButtonRepeatMode_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonRepeatMode" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonRepeatMode/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonRepeatMode/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonRepeatMode sequentially..."
)
add_dependencies(GUI_ButtonRepeatMode_build GUI_PanelOkNg_build)

add_custom_target(GUI_ButtonAutoMode_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAutoMode" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAutoMode/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAutoMode/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonAutoMode sequentially..."
)
add_dependencies(GUI_ButtonAutoMode_build GUI_ButtonRepeatMode_build)

add_custom_target(GUI_ListHistory_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListHistory" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListHistory/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListHistory/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ListHistory sequentially..."
)
add_dependencies(GUI_ListHistory_build GUI_ButtonAutoMode_build)

add_custom_target(GUI_ShowMasterNames_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMasterNames" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMasterNames/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMasterNames/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowMasterNames sequentially..."
)
add_dependencies(GUI_ShowMasterNames_build GUI_ListHistory_build)

add_custom_target(GUI_ButtonSetTactTime_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSetTactTime" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSetTactTime/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSetTactTime/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSetTactTime sequentially..."
)
add_dependencies(GUI_ButtonSetTactTime_build GUI_ShowMasterNames_build)

add_custom_target(GUI_GeneralTabWizardNext_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralTabWizardNext" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralTabWizardNext/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralTabWizardNext/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/GeneralTabWizardNext sequentially..."
)
add_dependencies(GUI_GeneralTabWizardNext_build GUI_ButtonSetTactTime_build)

add_custom_target(GUI_ButtonInspectionID_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonInspectionID" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonInspectionID/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonInspectionID/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonInspectionID sequentially..."
)
add_dependencies(GUI_ButtonInspectionID_build GUI_GeneralTabWizardNext_build)

add_custom_target(GUI_LabelForMeasuring_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LabelForMeasuring" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LabelForMeasuring/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LabelForMeasuring/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/LabelForMeasuring sequentially..."
)
add_dependencies(GUI_LabelForMeasuring_build GUI_ButtonInspectionID_build)

add_custom_target(GUI_PiecePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PiecePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PiecePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PiecePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PiecePanel sequentially..."
)
add_dependencies(GUI_PiecePanel_build GUI_LabelForMeasuring_build)

add_custom_target(GUI_ButtonMonoBitmapForAlgorithm_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonMonoBitmapForAlgorithm" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonMonoBitmapForAlgorithm/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonMonoBitmapForAlgorithm/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonMonoBitmapForAlgorithm sequentially..."
)
add_dependencies(GUI_ButtonMonoBitmapForAlgorithm_build GUI_PiecePanel_build)

add_custom_target(GUI_ShowStockedResult_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowStockedResult" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowStockedResult/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowStockedResult/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowStockedResult sequentially..."
)
add_dependencies(GUI_ShowStockedResult_build GUI_ButtonMonoBitmapForAlgorithm_build)

add_custom_target(GUI_ButtonReDrawAll_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonReDrawAll" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonReDrawAll/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonReDrawAll/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonReDrawAll sequentially..."
)
add_dependencies(GUI_ButtonReDrawAll_build GUI_ShowStockedResult_build)

add_custom_target(GUI_ButtonCopyrightVersion_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCopyrightVersion" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCopyrightVersion/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCopyrightVersion/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonCopyrightVersion sequentially..."
)
add_dependencies(GUI_ButtonCopyrightVersion_build GUI_ButtonReDrawAll_build)

add_custom_target(GUI_ButtonCalcFinalization_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCalcFinalization" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCalcFinalization/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCalcFinalization/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonCalcFinalization sequentially..."
)
add_dependencies(GUI_ButtonCalcFinalization_build GUI_ButtonCopyrightVersion_build)

add_custom_target(GUI_OutlineImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/OutlineImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/OutlineImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/OutlineImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/OutlineImagePanel sequentially..."
)
add_dependencies(GUI_OutlineImagePanel_build GUI_ButtonCalcFinalization_build)

add_custom_target(GUI_ChangeDrawTurn_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeDrawTurn" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeDrawTurn/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeDrawTurn/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ChangeDrawTurn sequentially..."
)
add_dependencies(GUI_ChangeDrawTurn_build GUI_OutlineImagePanel_build)

add_custom_target(GUI_LoadImageFor32Regulus_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageFor32Regulus" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageFor32Regulus/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageFor32Regulus/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/LoadImageFor32Regulus sequentially..."
)
add_dependencies(GUI_LoadImageFor32Regulus_build GUI_ChangeDrawTurn_build)

add_custom_target(GUI_ButtonSelectLightDB_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectLightDB" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectLightDB/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectLightDB/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSelectLightDB sequentially..."
)
add_dependencies(GUI_ButtonSelectLightDB_build GUI_LoadImageFor32Regulus_build)

add_custom_target(GUI_NamingImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/NamingImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/NamingImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/NamingImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/NamingImagePanel sequentially..."
)
add_dependencies(GUI_NamingImagePanel_build GUI_ButtonSelectLightDB_build)

add_custom_target(GUI_PropertyNaming_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyNaming" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyNaming/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyNaming/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyNaming sequentially..."
)
add_dependencies(GUI_PropertyNaming_build GUI_NamingImagePanel_build)

add_custom_target(GUI_ShowStrategicNumber_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowStrategicNumber" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowStrategicNumber/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowStrategicNumber/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowStrategicNumber sequentially..."
)
add_dependencies(GUI_ShowStrategicNumber_build GUI_PropertyNaming_build)

add_custom_target(GUI_ButtonChangeOverlap_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonChangeOverlap" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonChangeOverlap/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonChangeOverlap/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonChangeOverlap sequentially..."
)
add_dependencies(GUI_ButtonChangeOverlap_build GUI_ShowStrategicNumber_build)

add_custom_target(GUI_MaskingImagePanelPI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MaskingImagePanelPI" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MaskingImagePanelPI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MaskingImagePanelPI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/MaskingImagePanelPI sequentially..."
)
add_dependencies(GUI_MaskingImagePanelPI_build GUI_ButtonChangeOverlap_build)

add_custom_target(GUI_PropertyMaskingPI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMaskingPI" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMaskingPI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMaskingPI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyMaskingPI sequentially..."
)
add_dependencies(GUI_PropertyMaskingPI_build GUI_MaskingImagePanelPI_build)

add_custom_target(GUI_TrueColorBlockImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/TrueColorBlockImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/TrueColorBlockImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/TrueColorBlockImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/TrueColorBlockImagePanel sequentially..."
)
add_dependencies(GUI_TrueColorBlockImagePanel_build GUI_PropertyMaskingPI_build)

add_custom_target(GUI_ButtonSetRailWidth_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSetRailWidth" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSetRailWidth/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSetRailWidth/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSetRailWidth sequentially..."
)
add_dependencies(GUI_ButtonSetRailWidth_build GUI_TrueColorBlockImagePanel_build)

add_custom_target(GUI_StartStatisticScanButton_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartStatisticScanButton" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartStatisticScanButton/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartStatisticScanButton/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/StartStatisticScanButton sequentially..."
)
add_dependencies(GUI_StartStatisticScanButton_build GUI_ButtonSetRailWidth_build)

add_custom_target(GUI_ButtonLoadBmpJpg_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadBmpJpg" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadBmpJpg/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadBmpJpg/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLoadBmpJpg sequentially..."
)
add_dependencies(GUI_ButtonLoadBmpJpg_build GUI_StartStatisticScanButton_build)

add_custom_target(GUI_ListboxErrorMessage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxErrorMessage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxErrorMessage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxErrorMessage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ListboxErrorMessage sequentially..."
)
add_dependencies(GUI_ListboxErrorMessage_build GUI_ButtonLoadBmpJpg_build)

add_custom_target(GUI_ListboxAlgorithmItemProperty_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxAlgorithmItemProperty" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxAlgorithmItemProperty/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxAlgorithmItemProperty/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ListboxAlgorithmItemProperty sequentially..."
)
add_dependencies(GUI_ListboxAlgorithmItemProperty_build GUI_ListboxErrorMessage_build)

add_custom_target(GUI_ImageProcessorPanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImageProcessorPanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImageProcessorPanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImageProcessorPanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ImageProcessorPanel sequentially..."
)
add_dependencies(GUI_ImageProcessorPanel_build GUI_ListboxAlgorithmItemProperty_build)

add_custom_target(GUI_PropertyImageProcessor_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyImageProcessor" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyImageProcessor/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyImageProcessor/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyImageProcessor sequentially..."
)
add_dependencies(GUI_PropertyImageProcessor_build GUI_ImageProcessorPanel_build)

add_custom_target(GUI_DesktopMachineMenu_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DesktopMachineMenu" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DesktopMachineMenu/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DesktopMachineMenu/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DesktopMachineMenu sequentially..."
)
add_dependencies(GUI_DesktopMachineMenu_build GUI_PropertyImageProcessor_build)

add_custom_target(GUI_ButtonToShowOtherGUI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToShowOtherGUI" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToShowOtherGUI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToShowOtherGUI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonToShowOtherGUI sequentially..."
)
add_dependencies(GUI_ButtonToShowOtherGUI_build GUI_DesktopMachineMenu_build)

add_custom_target(GUI_ButtonWhichImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonWhichImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonWhichImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonWhichImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonWhichImage sequentially..."
)
add_dependencies(GUI_ButtonWhichImage_build GUI_ButtonToShowOtherGUI_build)

add_custom_target(GUI_AutoAlignmentImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoAlignmentImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoAlignmentImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoAlignmentImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AutoAlignmentImagePanel sequentially..."
)
add_dependencies(GUI_AutoAlignmentImagePanel_build GUI_ButtonWhichImage_build)

add_custom_target(GUI_ButtonCloseOnly_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCloseOnly" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCloseOnly/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCloseOnly/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonCloseOnly sequentially..."
)
add_dependencies(GUI_ButtonCloseOnly_build GUI_AutoAlignmentImagePanel_build)

add_custom_target(GUI_PixelInspectionNGList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PixelInspectionNGList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PixelInspectionNGList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PixelInspectionNGList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PixelInspectionNGList sequentially..."
)
add_dependencies(GUI_PixelInspectionNGList_build GUI_ButtonCloseOnly_build)

add_custom_target(GUI_ButtonEditFilterBank_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonEditFilterBank" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonEditFilterBank/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonEditFilterBank/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonEditFilterBank sequentially..."
)
add_dependencies(GUI_ButtonEditFilterBank_build GUI_PixelInspectionNGList_build)

add_custom_target(GUI_ButtonExecuteFilterImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExecuteFilterImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExecuteFilterImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExecuteFilterImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonExecuteFilterImage sequentially..."
)
add_dependencies(GUI_ButtonExecuteFilterImage_build GUI_ButtonEditFilterBank_build)

add_custom_target(GUI_AreaFilterImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AreaFilterImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AreaFilterImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AreaFilterImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AreaFilterImagePanel sequentially..."
)
add_dependencies(GUI_AreaFilterImagePanel_build GUI_ButtonExecuteFilterImage_build)

add_custom_target(GUI_PropertyAreaFilter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAreaFilter" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAreaFilter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAreaFilter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyAreaFilter sequentially..."
)
add_dependencies(GUI_PropertyAreaFilter_build GUI_AreaFilterImagePanel_build)

add_custom_target(GUI_ButtonExecuteAreaFilter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExecuteAreaFilter" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExecuteAreaFilter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExecuteAreaFilter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonExecuteAreaFilter sequentially..."
)
add_dependencies(GUI_ButtonExecuteAreaFilter_build GUI_PropertyAreaFilter_build)

add_custom_target(GUI_PieceLevelIndicator_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceLevelIndicator" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceLevelIndicator/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceLevelIndicator/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PieceLevelIndicator sequentially..."
)
add_dependencies(GUI_PieceLevelIndicator_build GUI_ButtonExecuteAreaFilter_build)

add_custom_target(GUI_AutoMaskingPIImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoMaskingPIImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoMaskingPIImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoMaskingPIImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AutoMaskingPIImagePanel sequentially..."
)
add_dependencies(GUI_AutoMaskingPIImagePanel_build GUI_PieceLevelIndicator_build)

add_custom_target(GUI_GraphicPanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GraphicPanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GraphicPanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GraphicPanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/GraphicPanel sequentially..."
)
add_dependencies(GUI_GraphicPanel_build GUI_AutoMaskingPIImagePanel_build)

add_custom_target(GUI_ShowPointerMessage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowPointerMessage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowPointerMessage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowPointerMessage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowPointerMessage sequentially..."
)
add_dependencies(GUI_ShowPointerMessage_build GUI_GraphicPanel_build)

add_custom_target(GUI_GeneralHairLine_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralHairLine" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralHairLine/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralHairLine/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/GeneralHairLine sequentially..."
)
add_dependencies(GUI_GeneralHairLine_build GUI_ShowPointerMessage_build)

add_custom_target(GUI_SaveNewMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveNewMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveNewMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveNewMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SaveNewMaster sequentially..."
)
add_dependencies(GUI_SaveNewMaster_build GUI_GeneralHairLine_build)

add_custom_target(GUI_ButtonSelectMachine_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectMachine" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectMachine/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectMachine/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSelectMachine sequentially..."
)
add_dependencies(GUI_ButtonSelectMachine_build GUI_SaveNewMaster_build)

add_custom_target(GUI_PanelSaveImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelSaveImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelSaveImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelSaveImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PanelSaveImage sequentially..."
)
add_dependencies(GUI_PanelSaveImage_build GUI_ButtonSelectMachine_build)

add_custom_target(GUI_SaveAlgorithmWithMachine_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveAlgorithmWithMachine" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveAlgorithmWithMachine/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveAlgorithmWithMachine/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SaveAlgorithmWithMachine sequentially..."
)
add_dependencies(GUI_SaveAlgorithmWithMachine_build GUI_PanelSaveImage_build)

add_custom_target(GUI_LoadAlgorithmWithMachine_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadAlgorithmWithMachine" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadAlgorithmWithMachine/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadAlgorithmWithMachine/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/LoadAlgorithmWithMachine sequentially..."
)
add_dependencies(GUI_LoadAlgorithmWithMachine_build GUI_SaveAlgorithmWithMachine_build)

add_custom_target(GUI_PropertyStatisticBlock_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyStatisticBlock" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyStatisticBlock/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyStatisticBlock/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyStatisticBlock sequentially..."
)
add_dependencies(GUI_PropertyStatisticBlock_build GUI_LoadAlgorithmWithMachine_build)

add_custom_target(GUI_StatisticBlockImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StatisticBlockImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StatisticBlockImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StatisticBlockImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/StatisticBlockImagePanel sequentially..."
)
add_dependencies(GUI_StatisticBlockImagePanel_build GUI_PropertyStatisticBlock_build)

add_custom_target(GUI_CompressImageList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CompressImageList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CompressImageList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CompressImageList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CompressImageList sequentially..."
)
add_dependencies(GUI_CompressImageList_build GUI_StatisticBlockImagePanel_build)

add_custom_target(GUI_LearningImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LearningImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LearningImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LearningImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/LearningImagePanel sequentially..."
)
add_dependencies(GUI_LearningImagePanel_build GUI_CompressImageList_build)

add_custom_target(GUI_PropertyLearning_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyLearning" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyLearning/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyLearning/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyLearning sequentially..."
)
add_dependencies(GUI_PropertyLearning_build GUI_LearningImagePanel_build)

add_custom_target(GUI_PropertyDynamicMaskingPI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDynamicMaskingPI" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDynamicMaskingPI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDynamicMaskingPI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyDynamicMaskingPI sequentially..."
)
add_dependencies(GUI_PropertyDynamicMaskingPI_build GUI_PropertyLearning_build)

add_custom_target(GUI_DynamicMaskingPIImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DynamicMaskingPIImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DynamicMaskingPIImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DynamicMaskingPIImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DynamicMaskingPIImagePanel sequentially..."
)
add_dependencies(GUI_DynamicMaskingPIImagePanel_build GUI_PropertyDynamicMaskingPI_build)

add_custom_target(GUI_ButtonLearningSaveMode_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLearningSaveMode" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLearningSaveMode/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLearningSaveMode/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLearningSaveMode sequentially..."
)
add_dependencies(GUI_ButtonLearningSaveMode_build GUI_DynamicMaskingPIImagePanel_build)

add_custom_target(GUI_NGNamingList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/NGNamingList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/NGNamingList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/NGNamingList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/NGNamingList sequentially..."
)
add_dependencies(GUI_NGNamingList_build GUI_ButtonLearningSaveMode_build)

add_custom_target(GUI_EulerRingImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/EulerRingImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/EulerRingImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/EulerRingImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/EulerRingImagePanel sequentially..."
)
add_dependencies(GUI_EulerRingImagePanel_build GUI_NGNamingList_build)

add_custom_target(GUI_PropertyEulerRing_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyEulerRing" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyEulerRing/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyEulerRing/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyEulerRing sequentially..."
)
add_dependencies(GUI_PropertyEulerRing_build GUI_EulerRingImagePanel_build)

add_custom_target(GUI_ButtonToShowDialogOnGeneralStocker_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToShowDialogOnGeneralStocker" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToShowDialogOnGeneralStocker/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToShowDialogOnGeneralStocker/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonToShowDialogOnGeneralStocker sequentially..."
)
add_dependencies(GUI_ButtonToShowDialogOnGeneralStocker_build GUI_PropertyEulerRing_build)

add_custom_target(GUI_AreaShaderImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AreaShaderImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AreaShaderImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AreaShaderImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AreaShaderImagePanel sequentially..."
)
add_dependencies(GUI_AreaShaderImagePanel_build GUI_ButtonToShowDialogOnGeneralStocker_build)

add_custom_target(GUI_PropertyAreaShader_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAreaShader" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAreaShader/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAreaShader/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyAreaShader sequentially..."
)
add_dependencies(GUI_PropertyAreaShader_build GUI_AreaShaderImagePanel_build)

add_custom_target(GUI_AutoSaveImageViewList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageViewList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageViewList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageViewList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AutoSaveImageViewList sequentially..."
)
add_dependencies(GUI_AutoSaveImageViewList_build GUI_PropertyAreaShader_build)

add_custom_target(GUI_AutoSaveImageViewPanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageViewPanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageViewPanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageViewPanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AutoSaveImageViewPanel sequentially..."
)
add_dependencies(GUI_AutoSaveImageViewPanel_build GUI_AutoSaveImageViewList_build)

add_custom_target(GUI_ListboxProcessTime_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxProcessTime" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxProcessTime/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxProcessTime/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ListboxProcessTime sequentially..."
)
add_dependencies(GUI_ListboxProcessTime_build GUI_AutoSaveImageViewPanel_build)

add_custom_target(GUI_ManualDesktopMachineMenu_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ManualDesktopMachineMenu" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ManualDesktopMachineMenu/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ManualDesktopMachineMenu/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ManualDesktopMachineMenu sequentially..."
)
add_dependencies(GUI_ManualDesktopMachineMenu_build GUI_ListboxProcessTime_build)

add_custom_target(GUI_ManualPropertyPixel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ManualPropertyPixel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ManualPropertyPixel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ManualPropertyPixel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ManualPropertyPixel sequentially..."
)
add_dependencies(GUI_ManualPropertyPixel_build GUI_ManualDesktopMachineMenu_build)

add_custom_target(GUI_ManualPixelImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ManualPixelImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ManualPixelImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ManualPixelImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ManualPixelImagePanel sequentially..."
)
add_dependencies(GUI_ManualPixelImagePanel_build GUI_ManualPropertyPixel_build)

add_custom_target(GUI_ManualPixelInspectionNGList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ManualPixelInspectionNGList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ManualPixelInspectionNGList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ManualPixelInspectionNGList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ManualPixelInspectionNGList sequentially..."
)
add_dependencies(GUI_ManualPixelInspectionNGList_build GUI_ManualPixelImagePanel_build)

add_custom_target(GUI_ButtonStartLearning_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonStartLearning" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonStartLearning/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonStartLearning/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonStartLearning sequentially..."
)
add_dependencies(GUI_ButtonStartLearning_build GUI_ManualPixelInspectionNGList_build)

add_custom_target(GUI_ButtonLoadPWAFile_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadPWAFile" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadPWAFile/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadPWAFile/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLoadPWAFile sequentially..."
)
add_dependencies(GUI_ButtonLoadPWAFile_build GUI_ButtonStartLearning_build)

add_custom_target(GUI_ButtonSavePWAFile_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSavePWAFile" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSavePWAFile/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSavePWAFile/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSavePWAFile sequentially..."
)
add_dependencies(GUI_ButtonSavePWAFile_build GUI_ButtonLoadPWAFile_build)

add_custom_target(GUI_ButtonSelectMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSelectMaster sequentially..."
)
add_dependencies(GUI_ButtonSelectMaster_build GUI_ButtonSavePWAFile_build)

add_custom_target(GUI_ButtonSelectDatabase_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectDatabase" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectDatabase/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectDatabase/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSelectDatabase sequentially..."
)
add_dependencies(GUI_ButtonSelectDatabase_build GUI_ButtonSelectMaster_build)

add_custom_target(GUI_ButtonShutdown_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShutdown" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShutdown/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShutdown/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonShutdown sequentially..."
)
add_dependencies(GUI_ButtonShutdown_build GUI_ButtonSelectDatabase_build)

add_custom_target(GUI_ImageCheckerPanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImageCheckerPanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImageCheckerPanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImageCheckerPanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ImageCheckerPanel sequentially..."
)
add_dependencies(GUI_ImageCheckerPanel_build GUI_ButtonShutdown_build)

add_custom_target(GUI_PropertyImageChecker_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyImageChecker" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyImageChecker/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyImageChecker/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyImageChecker sequentially..."
)
add_dependencies(GUI_PropertyImageChecker_build GUI_ImageCheckerPanel_build)

add_custom_target(GUI_ShowResultImageChecker_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultImageChecker" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultImageChecker/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultImageChecker/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowResultImageChecker sequentially..."
)
add_dependencies(GUI_ShowResultImageChecker_build GUI_PropertyImageChecker_build)

add_custom_target(GUI_ShowInspectionNumber_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowInspectionNumber" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowInspectionNumber/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowInspectionNumber/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowInspectionNumber sequentially..."
)
add_dependencies(GUI_ShowInspectionNumber_build GUI_ShowResultImageChecker_build)

add_custom_target(GUI_SendMessenger_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SendMessenger" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SendMessenger/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SendMessenger/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SendMessenger sequentially..."
)
add_dependencies(GUI_SendMessenger_build GUI_ShowInspectionNumber_build)

add_custom_target(GUI_SpotReducerImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SpotReducerImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SpotReducerImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SpotReducerImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SpotReducerImagePanel sequentially..."
)
add_dependencies(GUI_SpotReducerImagePanel_build GUI_SendMessenger_build)

add_custom_target(GUI_PropertySpotReducer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertySpotReducer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertySpotReducer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertySpotReducer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertySpotReducer sequentially..."
)
add_dependencies(GUI_PropertySpotReducer_build GUI_SpotReducerImagePanel_build)

add_custom_target(GUI_ChangeCameraSettingInvisible_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeCameraSettingInvisible" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeCameraSettingInvisible/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeCameraSettingInvisible/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ChangeCameraSettingInvisible sequentially..."
)
add_dependencies(GUI_ChangeCameraSettingInvisible_build GUI_PropertySpotReducer_build)

add_custom_target(GUI_ButtonShrinkImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShrinkImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShrinkImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShrinkImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonShrinkImage sequentially..."
)
add_dependencies(GUI_ButtonShrinkImage_build GUI_ChangeCameraSettingInvisible_build)

add_custom_target(GUI_MatchingAlignmentImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MatchingAlignmentImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MatchingAlignmentImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MatchingAlignmentImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/MatchingAlignmentImagePanel sequentially..."
)
add_dependencies(GUI_MatchingAlignmentImagePanel_build GUI_ButtonShrinkImage_build)

add_custom_target(GUI_PropertyMatchingAlignment_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMatchingAlignment" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMatchingAlignment/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMatchingAlignment/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyMatchingAlignment sequentially..."
)
add_dependencies(GUI_PropertyMatchingAlignment_build GUI_MatchingAlignmentImagePanel_build)

add_custom_target(GUI_MatrixCellList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MatrixCellList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MatrixCellList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MatrixCellList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/MatrixCellList sequentially..."
)
add_dependencies(GUI_MatrixCellList_build GUI_PropertyMatchingAlignment_build)

add_custom_target(GUI_ButtonLoadMonoBmpInAnyPageLayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMonoBmpInAnyPageLayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMonoBmpInAnyPageLayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMonoBmpInAnyPageLayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLoadMonoBmpInAnyPageLayer sequentially..."
)
add_dependencies(GUI_ButtonLoadMonoBmpInAnyPageLayer_build GUI_MatrixCellList_build)

add_custom_target(GUI_ExecuteMacroList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExecuteMacroList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExecuteMacroList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExecuteMacroList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ExecuteMacroList sequentially..."
)
add_dependencies(GUI_ExecuteMacroList_build GUI_ButtonLoadMonoBmpInAnyPageLayer_build)

add_custom_target(GUI_ButtonSaveResultWithAll_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveResultWithAll" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveResultWithAll/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveResultWithAll/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSaveResultWithAll sequentially..."
)
add_dependencies(GUI_ButtonSaveResultWithAll_build GUI_ExecuteMacroList_build)

add_custom_target(GUI_ButtonLoadResultWithAll_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadResultWithAll" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadResultWithAll/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadResultWithAll/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLoadResultWithAll sequentially..."
)
add_dependencies(GUI_ButtonLoadResultWithAll_build GUI_ButtonSaveResultWithAll_build)

add_custom_target(GUI_ChangeCameraSetting_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeCameraSetting" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeCameraSetting/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeCameraSetting/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ChangeCameraSetting sequentially..."
)
add_dependencies(GUI_ChangeCameraSetting_build GUI_ButtonLoadResultWithAll_build)

add_custom_target(GUI_ButtonSaveMatrixCell_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveMatrixCell" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveMatrixCell/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveMatrixCell/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSaveMatrixCell sequentially..."
)
add_dependencies(GUI_ButtonSaveMatrixCell_build GUI_ChangeCameraSetting_build)

add_custom_target(GUI_ButtonLoadMatrixCell_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMatrixCell" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMatrixCell/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMatrixCell/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLoadMatrixCell sequentially..."
)
add_dependencies(GUI_ButtonLoadMatrixCell_build GUI_ButtonSaveMatrixCell_build)

add_custom_target(GUI_ButtonSetMachine_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSetMachine" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSetMachine/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSetMachine/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSetMachine sequentially..."
)
add_dependencies(GUI_ButtonSetMachine_build GUI_ButtonLoadMatrixCell_build)

add_custom_target(GUI_AutoSaveImageSelectLot_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageSelectLot" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageSelectLot/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageSelectLot/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AutoSaveImageSelectLot sequentially..."
)
add_dependencies(GUI_AutoSaveImageSelectLot_build GUI_ButtonSetMachine_build)

add_custom_target(GUI_ButtonToSaveCopiedItemDirectly_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToSaveCopiedItemDirectly" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToSaveCopiedItemDirectly/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToSaveCopiedItemDirectly/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonToSaveCopiedItemDirectly sequentially..."
)
add_dependencies(GUI_ButtonToSaveCopiedItemDirectly_build GUI_AutoSaveImageSelectLot_build)

add_custom_target(GUI_CheckProgramRunInvisible_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckProgramRunInvisible" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckProgramRunInvisible/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckProgramRunInvisible/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CheckProgramRunInvisible sequentially..."
)
add_dependencies(GUI_CheckProgramRunInvisible_build GUI_ButtonToSaveCopiedItemDirectly_build)

add_custom_target(GUI_ButtonChangeCurrentPhase_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonChangeCurrentPhase" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonChangeCurrentPhase/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonChangeCurrentPhase/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonChangeCurrentPhase sequentially..."
)
add_dependencies(GUI_ButtonChangeCurrentPhase_build GUI_CheckProgramRunInvisible_build)

add_custom_target(GUI_GeneralMenu_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralMenu" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralMenu/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralMenu/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/GeneralMenu sequentially..."
)
add_dependencies(GUI_GeneralMenu_build GUI_ButtonChangeCurrentPhase_build)

add_custom_target(GUI_AutoPCBHoleAlignerImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoPCBHoleAlignerImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoPCBHoleAlignerImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoPCBHoleAlignerImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AutoPCBHoleAlignerImagePanel sequentially..."
)
add_dependencies(GUI_AutoPCBHoleAlignerImagePanel_build GUI_GeneralMenu_build)

add_custom_target(GUI_PropertyAutoPCBHoleAligner_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAutoPCBHoleAligner" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAutoPCBHoleAligner/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAutoPCBHoleAligner/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyAutoPCBHoleAligner sequentially..."
)
add_dependencies(GUI_PropertyAutoPCBHoleAligner_build GUI_AutoPCBHoleAlignerImagePanel_build)

add_custom_target(GUI_StacksToSwitchMasterTarget_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StacksToSwitchMasterTarget" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StacksToSwitchMasterTarget/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StacksToSwitchMasterTarget/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/StacksToSwitchMasterTarget sequentially..."
)
add_dependencies(GUI_StacksToSwitchMasterTarget_build GUI_PropertyAutoPCBHoleAligner_build)

add_custom_target(GUI_SlaveIndicatorInvisible_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SlaveIndicatorInvisible" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SlaveIndicatorInvisible/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SlaveIndicatorInvisible/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SlaveIndicatorInvisible sequentially..."
)
add_dependencies(GUI_SlaveIndicatorInvisible_build GUI_StacksToSwitchMasterTarget_build)

add_custom_target(GUI_ListboxGUITime_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxGUITime" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxGUITime/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxGUITime/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ListboxGUITime sequentially..."
)
add_dependencies(GUI_ListboxGUITime_build GUI_SlaveIndicatorInvisible_build)

add_custom_target(GUI_ButtonLearningOK_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLearningOK" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLearningOK/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLearningOK/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLearningOK sequentially..."
)
add_dependencies(GUI_ButtonLearningOK_build GUI_ListboxGUITime_build)

add_custom_target(GUI_ButtonLearningNG_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLearningNG" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLearningNG/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLearningNG/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLearningNG sequentially..."
)
add_dependencies(GUI_ButtonLearningNG_build GUI_ButtonLearningOK_build)

add_custom_target(GUI_DisplayStatus_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayStatus" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayStatus/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayStatus/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayStatus sequentially..."
)
add_dependencies(GUI_DisplayStatus_build GUI_ButtonLearningNG_build)

add_custom_target(GUI_ShowCurrentOpinion_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCurrentOpinion" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCurrentOpinion/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCurrentOpinion/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowCurrentOpinion sequentially..."
)
add_dependencies(GUI_ShowCurrentOpinion_build GUI_DisplayStatus_build)

add_custom_target(GUI_ButtonSaveAllOpinions_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveAllOpinions" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveAllOpinions/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveAllOpinions/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSaveAllOpinions sequentially..."
)
add_dependencies(GUI_ButtonSaveAllOpinions_build GUI_ShowCurrentOpinion_build)

add_custom_target(GUI_ButtonCalcAlignment_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCalcAlignment" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCalcAlignment/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCalcAlignment/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonCalcAlignment sequentially..."
)
add_dependencies(GUI_ButtonCalcAlignment_build GUI_ButtonSaveAllOpinions_build)

add_custom_target(GUI_ButtonCopyLibrary_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCopyLibrary" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCopyLibrary/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCopyLibrary/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonCopyLibrary sequentially..."
)
add_dependencies(GUI_ButtonCopyLibrary_build GUI_ButtonCalcAlignment_build)

add_custom_target(GUI_GeneralDividedPanels_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralDividedPanels" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralDividedPanels/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralDividedPanels/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/GeneralDividedPanels sequentially..."
)
add_dependencies(GUI_GeneralDividedPanels_build GUI_ButtonCopyLibrary_build)

add_custom_target(GUI_GeneralPanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralPanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralPanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralPanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/GeneralPanel sequentially..."
)
add_dependencies(GUI_GeneralPanel_build GUI_GeneralDividedPanels_build)

add_custom_target(GUI_ListboxUncoveredArea_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxUncoveredArea" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxUncoveredArea/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListboxUncoveredArea/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ListboxUncoveredArea sequentially..."
)
add_dependencies(GUI_ListboxUncoveredArea_build GUI_GeneralPanel_build)

add_custom_target(GUI_ButtonClearStockedResult_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonClearStockedResult" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonClearStockedResult/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonClearStockedResult/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonClearStockedResult sequentially..."
)
add_dependencies(GUI_ButtonClearStockedResult_build GUI_ListboxUncoveredArea_build)

add_custom_target(GUI_ExpandMainInTab_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExpandMainInTab" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExpandMainInTab/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExpandMainInTab/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ExpandMainInTab sequentially..."
)
add_dependencies(GUI_ExpandMainInTab_build GUI_ButtonClearStockedResult_build)

add_custom_target(GUI_ButtonAppendAlgorithm_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAppendAlgorithm" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAppendAlgorithm/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAppendAlgorithm/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonAppendAlgorithm sequentially..."
)
add_dependencies(GUI_ButtonAppendAlgorithm_build GUI_ExpandMainInTab_build)

add_custom_target(GUI_ButtonSetZ_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSetZ" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSetZ/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSetZ/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSetZ sequentially..."
)
add_dependencies(GUI_ButtonSetZ_build GUI_ButtonAppendAlgorithm_build)

add_custom_target(GUI_RemoteControlForServer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RemoteControlForServer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RemoteControlForServer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RemoteControlForServer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/RemoteControlForServer sequentially..."
)
add_dependencies(GUI_RemoteControlForServer_build GUI_ButtonSetZ_build)

add_custom_target(GUI_DisplayServer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayServer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayServer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayServer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayServer sequentially..."
)
add_dependencies(GUI_DisplayServer_build GUI_RemoteControlForServer_build)

add_custom_target(GUI_PropertyOutline_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyOutline" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyOutline/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyOutline/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyOutline sequentially..."
)
add_dependencies(GUI_PropertyOutline_build GUI_DisplayServer_build)

add_custom_target(GUI_PropertyMasking_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMasking" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMasking/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMasking/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyMasking sequentially..."
)
add_dependencies(GUI_PropertyMasking_build GUI_PropertyOutline_build)

add_custom_target(GUI_ButtonLoadOutlineOffset_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadOutlineOffset" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadOutlineOffset/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadOutlineOffset/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLoadOutlineOffset sequentially..."
)
add_dependencies(GUI_ButtonLoadOutlineOffset_build GUI_PropertyMasking_build)

add_custom_target(GUI_ButtonMoveAll_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonMoveAll" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonMoveAll/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonMoveAll/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonMoveAll sequentially..."
)
add_dependencies(GUI_ButtonMoveAll_build GUI_ButtonLoadOutlineOffset_build)

add_custom_target(GUI_PropertyColorBlock_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyColorBlock" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyColorBlock/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyColorBlock/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyColorBlock sequentially..."
)
add_dependencies(GUI_PropertyColorBlock_build GUI_ButtonMoveAll_build)

add_custom_target(GUI_PropertyTrueColorBlock_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyTrueColorBlock" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyTrueColorBlock/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyTrueColorBlock/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyTrueColorBlock sequentially..."
)
add_dependencies(GUI_PropertyTrueColorBlock_build GUI_PropertyColorBlock_build)

add_custom_target(GUI_PropertyAutoMaskingPI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAutoMaskingPI" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAutoMaskingPI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAutoMaskingPI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyAutoMaskingPI sequentially..."
)
add_dependencies(GUI_PropertyAutoMaskingPI_build GUI_PropertyTrueColorBlock_build)

add_custom_target(GUI_PropertyAutoAlignment_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAutoAlignment" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAutoAlignment/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAutoAlignment/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyAutoAlignment sequentially..."
)
add_dependencies(GUI_PropertyAutoAlignment_build GUI_PropertyAutoMaskingPI_build)

add_custom_target(GUI_ButtonSelectLearningTargetImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectLearningTargetImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectLearningTargetImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectLearningTargetImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSelectLearningTargetImage sequentially..."
)
add_dependencies(GUI_ButtonSelectLearningTargetImage_build GUI_PropertyAutoAlignment_build)

add_custom_target(GUI_ButtonShowLightForm_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowLightForm" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowLightForm/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowLightForm/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonShowLightForm sequentially..."
)
add_dependencies(GUI_ButtonShowLightForm_build GUI_ButtonSelectLearningTargetImage_build)

add_custom_target(GUI_PropertyStatisticImager_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyStatisticImager" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyStatisticImager/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyStatisticImager/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyStatisticImager sequentially..."
)
add_dependencies(GUI_PropertyStatisticImager_build GUI_ButtonShowLightForm_build)

add_custom_target(GUI_StatisticImagerImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StatisticImagerImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StatisticImagerImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StatisticImagerImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/StatisticImagerImagePanel sequentially..."
)
add_dependencies(GUI_StatisticImagerImagePanel_build GUI_PropertyStatisticImager_build)

add_custom_target(GUI_PieceProperty_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceProperty" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceProperty/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceProperty/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PieceProperty sequentially..."
)
add_dependencies(GUI_PieceProperty_build GUI_StatisticImagerImagePanel_build)

add_custom_target(GUI_GeneralGroup_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralGroup" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralGroup/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralGroup/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/GeneralGroup sequentially..."
)
add_dependencies(GUI_GeneralGroup_build GUI_PieceProperty_build)

add_custom_target(GUI_PropertyBlock_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyBlock" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyBlock/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyBlock/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyBlock sequentially..."
)
add_dependencies(GUI_PropertyBlock_build GUI_GeneralGroup_build)

add_custom_target(GUI_ButtonLoadMasterDataWithoutMachine_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMasterDataWithoutMachine" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMasterDataWithoutMachine/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMasterDataWithoutMachine/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLoadMasterDataWithoutMachine sequentially..."
)
add_dependencies(GUI_ButtonLoadMasterDataWithoutMachine_build GUI_PropertyBlock_build)

add_custom_target(GUI_AutoSaveImageListForSearch_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageListForSearch" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageListForSearch/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageListForSearch/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AutoSaveImageListForSearch sequentially..."
)
add_dependencies(GUI_AutoSaveImageListForSearch_build GUI_ButtonLoadMasterDataWithoutMachine_build)

add_custom_target(GUI_AutoSaveImageButtonSave_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageButtonSave" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageButtonSave/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageButtonSave/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AutoSaveImageButtonSave sequentially..."
)
add_dependencies(GUI_AutoSaveImageButtonSave_build GUI_AutoSaveImageListForSearch_build)

add_custom_target(GUI_AutoSaveImageButtonAuto_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageButtonAuto" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageButtonAuto/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AutoSaveImageButtonAuto/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AutoSaveImageButtonAuto sequentially..."
)
add_dependencies(GUI_AutoSaveImageButtonAuto_build GUI_AutoSaveImageButtonSave_build)

add_custom_target(GUI_ButtonCopyImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCopyImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCopyImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCopyImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonCopyImage sequentially..."
)
add_dependencies(GUI_ButtonCopyImage_build GUI_AutoSaveImageButtonAuto_build)

add_custom_target(GUI_StartInspectionWithoutCapture_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartInspectionWithoutCapture" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartInspectionWithoutCapture/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartInspectionWithoutCapture/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/StartInspectionWithoutCapture sequentially..."
)
add_dependencies(GUI_StartInspectionWithoutCapture_build GUI_ButtonCopyImage_build)

add_custom_target(GUI_VCutImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/VCutImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/VCutImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/VCutImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/VCutImagePanel sequentially..."
)
add_dependencies(GUI_VCutImagePanel_build GUI_StartInspectionWithoutCapture_build)

add_custom_target(GUI_VCutProperty_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/VCutProperty" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/VCutProperty/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/VCutProperty/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/VCutProperty sequentially..."
)
add_dependencies(GUI_VCutProperty_build GUI_VCutImagePanel_build)

add_custom_target(GUI_ListCachTargetImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListCachTargetImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListCachTargetImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListCachTargetImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ListCachTargetImage sequentially..."
)
add_dependencies(GUI_ListCachTargetImage_build GUI_VCutProperty_build)

add_custom_target(GUI_LineEnhancerImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LineEnhancerImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LineEnhancerImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LineEnhancerImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/LineEnhancerImagePanel sequentially..."
)
add_dependencies(GUI_LineEnhancerImagePanel_build GUI_ListCachTargetImage_build)

add_custom_target(GUI_PropertyLineEnhancer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyLineEnhancer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyLineEnhancer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyLineEnhancer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyLineEnhancer sequentially..."
)
add_dependencies(GUI_PropertyLineEnhancer_build GUI_LineEnhancerImagePanel_build)

add_custom_target(GUI_DynamicClassifyImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DynamicClassifyImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DynamicClassifyImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DynamicClassifyImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DynamicClassifyImagePanel sequentially..."
)
add_dependencies(GUI_DynamicClassifyImagePanel_build GUI_PropertyLineEnhancer_build)

add_custom_target(GUI_PropertyDynamicClassify_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDynamicClassify" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDynamicClassify/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDynamicClassify/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyDynamicClassify sequentially..."
)
add_dependencies(GUI_PropertyDynamicClassify_build GUI_DynamicClassifyImagePanel_build)

add_custom_target(GUI_ARArrangeImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ARArrangeImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ARArrangeImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ARArrangeImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ARArrangeImagePanel sequentially..."
)
add_dependencies(GUI_ARArrangeImagePanel_build GUI_PropertyDynamicClassify_build)

add_custom_target(GUI_PropertyARArrange_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyARArrange" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyARArrange/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyARArrange/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyARArrange sequentially..."
)
add_dependencies(GUI_PropertyARArrange_build GUI_ARArrangeImagePanel_build)

add_custom_target(GUI_DisplayPointingMessage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayPointingMessage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayPointingMessage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayPointingMessage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayPointingMessage sequentially..."
)
add_dependencies(GUI_DisplayPointingMessage_build GUI_PropertyARArrange_build)

add_custom_target(GUI_ProgressOnIdle_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ProgressOnIdle" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ProgressOnIdle/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ProgressOnIdle/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ProgressOnIdle sequentially..."
)
add_dependencies(GUI_ProgressOnIdle_build GUI_DisplayPointingMessage_build)

add_custom_target(GUI_DisplayRealtimeGraph_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayRealtimeGraph" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayRealtimeGraph/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayRealtimeGraph/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayRealtimeGraph sequentially..."
)
add_dependencies(GUI_DisplayRealtimeGraph_build GUI_ProgressOnIdle_build)

add_custom_target(GUI_PropertyRealtimeGraph_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRealtimeGraph" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRealtimeGraph/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRealtimeGraph/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyRealtimeGraph sequentially..."
)
add_dependencies(GUI_PropertyRealtimeGraph_build GUI_DisplayRealtimeGraph_build)

add_custom_target(GUI_RealtimeGraphMeasure1_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RealtimeGraphMeasure1" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RealtimeGraphMeasure1/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RealtimeGraphMeasure1/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/RealtimeGraphMeasure1 sequentially..."
)
add_dependencies(GUI_RealtimeGraphMeasure1_build GUI_PropertyRealtimeGraph_build)

add_custom_target(GUI_ShowMinMaxButton_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMinMaxButton" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMinMaxButton/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMinMaxButton/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowMinMaxButton sequentially..."
)
add_dependencies(GUI_ShowMinMaxButton_build GUI_RealtimeGraphMeasure1_build)

add_custom_target(GUI_ButtonSwitchDelayedView_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSwitchDelayedView" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSwitchDelayedView/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSwitchDelayedView/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSwitchDelayedView sequentially..."
)
add_dependencies(GUI_ButtonSwitchDelayedView_build GUI_ShowMinMaxButton_build)

add_custom_target(GUI_ExecuteVisualizer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExecuteVisualizer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExecuteVisualizer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExecuteVisualizer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ExecuteVisualizer sequentially..."
)
add_dependencies(GUI_ExecuteVisualizer_build GUI_ButtonSwitchDelayedView_build)

add_custom_target(GUI_ShowTopBottomSideInfo_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowTopBottomSideInfo" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowTopBottomSideInfo/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowTopBottomSideInfo/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowTopBottomSideInfo sequentially..."
)
add_dependencies(GUI_ShowTopBottomSideInfo_build GUI_ExecuteVisualizer_build)

add_custom_target(GUI_PieceForReviewImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceForReviewImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceForReviewImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceForReviewImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PieceForReviewImagePanel sequentially..."
)
add_dependencies(GUI_PieceForReviewImagePanel_build GUI_ShowTopBottomSideInfo_build)

add_custom_target(GUI_PropertyPieceForReview_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPieceForReview" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPieceForReview/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPieceForReview/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyPieceForReview sequentially..."
)
add_dependencies(GUI_PropertyPieceForReview_build GUI_PieceForReviewImagePanel_build)

add_custom_target(GUI_LineEnhancer1LImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LineEnhancer1LImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LineEnhancer1LImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LineEnhancer1LImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/LineEnhancer1LImagePanel sequentially..."
)
add_dependencies(GUI_LineEnhancer1LImagePanel_build GUI_PropertyPieceForReview_build)

add_custom_target(GUI_PropertyLineEnhancer1L_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyLineEnhancer1L" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyLineEnhancer1L/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyLineEnhancer1L/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyLineEnhancer1L sequentially..."
)
add_dependencies(GUI_PropertyLineEnhancer1L_build GUI_LineEnhancer1LImagePanel_build)

add_custom_target(GUI_DisplayLibFolder_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayLibFolder" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayLibFolder/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayLibFolder/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayLibFolder sequentially..."
)
add_dependencies(GUI_DisplayLibFolder_build GUI_PropertyLineEnhancer1L_build)

add_custom_target(GUI_ButtonSelectLot_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectLot" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectLot/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectLot/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSelectLot sequentially..."
)
add_dependencies(GUI_ButtonSelectLot_build GUI_DisplayLibFolder_build)

add_custom_target(GUI_ShowHistgramTotal_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowHistgramTotal" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowHistgramTotal/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowHistgramTotal/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowHistgramTotal sequentially..."
)
add_dependencies(GUI_ShowHistgramTotal_build GUI_ButtonSelectLot_build)

add_custom_target(GUI_ButtonSaveHistogramData_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveHistogramData" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveHistogramData/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveHistogramData/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSaveHistogramData sequentially..."
)
add_dependencies(GUI_ButtonSaveHistogramData_build GUI_ShowHistgramTotal_build)

add_custom_target(GUI_ButtonLoadHistogramData_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadHistogramData" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadHistogramData/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadHistogramData/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLoadHistogramData sequentially..."
)
add_dependencies(GUI_ButtonLoadHistogramData_build GUI_ButtonSaveHistogramData_build)

add_custom_target(GUI_ButtonClearHistogram_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonClearHistogram" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonClearHistogram/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonClearHistogram/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonClearHistogram sequentially..."
)
add_dependencies(GUI_ButtonClearHistogram_build GUI_ButtonLoadHistogramData_build)

add_custom_target(GUI_LoadImageInAnyPage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageInAnyPage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageInAnyPage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageInAnyPage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/LoadImageInAnyPage sequentially..."
)
add_dependencies(GUI_LoadImageInAnyPage_build GUI_ButtonClearHistogram_build)

add_custom_target(GUI_ButtonRewindInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonRewindInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonRewindInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonRewindInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonRewindInspection sequentially..."
)
add_dependencies(GUI_ButtonRewindInspection_build GUI_LoadImageInAnyPage_build)

add_custom_target(GUI_DisplayScanPhaseNumber_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayScanPhaseNumber" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayScanPhaseNumber/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayScanPhaseNumber/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayScanPhaseNumber sequentially..."
)
add_dependencies(GUI_DisplayScanPhaseNumber_build GUI_ButtonRewindInspection_build)

add_custom_target(GUI_ResultImportanceImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ResultImportanceImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ResultImportanceImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ResultImportanceImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ResultImportanceImagePanel sequentially..."
)
add_dependencies(GUI_ResultImportanceImagePanel_build GUI_DisplayScanPhaseNumber_build)

add_custom_target(GUI_PropertyResultImportance_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyResultImportance" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyResultImportance/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyResultImportance/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyResultImportance sequentially..."
)
add_dependencies(GUI_PropertyResultImportance_build GUI_ResultImportanceImagePanel_build)

add_custom_target(GUI_PieceListReviewSide_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceListReviewSide" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceListReviewSide/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceListReviewSide/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PieceListReviewSide sequentially..."
)
add_dependencies(GUI_PieceListReviewSide_build GUI_PropertyResultImportance_build)

add_custom_target(GUI_ShowPieceResultList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowPieceResultList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowPieceResultList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowPieceResultList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowPieceResultList sequentially..."
)
add_dependencies(GUI_ShowPieceResultList_build GUI_PieceListReviewSide_build)

add_custom_target(GUI_ButtonImageTransformer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonImageTransformer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonImageTransformer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonImageTransformer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonImageTransformer sequentially..."
)
add_dependencies(GUI_ButtonImageTransformer_build GUI_ShowPieceResultList_build)

add_custom_target(GUI_MeasureHoleImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MeasureHoleImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MeasureHoleImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MeasureHoleImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/MeasureHoleImagePanel sequentially..."
)
add_dependencies(GUI_MeasureHoleImagePanel_build GUI_ButtonImageTransformer_build)

add_custom_target(GUI_PropertyMeasureHole_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMeasureHole" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMeasureHole/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMeasureHole/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyMeasureHole sequentially..."
)
add_dependencies(GUI_PropertyMeasureHole_build GUI_MeasureHoleImagePanel_build)

add_custom_target(GUI_MeasureLineMoveImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MeasureLineMoveImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MeasureLineMoveImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MeasureLineMoveImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/MeasureLineMoveImagePanel sequentially..."
)
add_dependencies(GUI_MeasureLineMoveImagePanel_build GUI_PropertyMeasureHole_build)

add_custom_target(GUI_PropertyMeasureLineMove_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMeasureLineMove" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMeasureLineMove/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMeasureLineMove/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyMeasureLineMove sequentially..."
)
add_dependencies(GUI_PropertyMeasureLineMove_build GUI_MeasureLineMoveImagePanel_build)

add_custom_target(GUI_MeasureHolePosImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MeasureHolePosImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MeasureHolePosImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MeasureHolePosImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/MeasureHolePosImagePanel sequentially..."
)
add_dependencies(GUI_MeasureHolePosImagePanel_build GUI_PropertyMeasureLineMove_build)

add_custom_target(GUI_PropertyMeasureHolePos_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMeasureHolePos" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMeasureHolePos/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMeasureHolePos/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyMeasureHolePos sequentially..."
)
add_dependencies(GUI_PropertyMeasureHolePos_build GUI_MeasureHolePosImagePanel_build)

add_custom_target(GUI_ImagePanelTools_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImagePanelTools" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImagePanelTools/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImagePanelTools/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ImagePanelTools sequentially..."
)
add_dependencies(GUI_ImagePanelTools_build GUI_PropertyMeasureHolePos_build)

add_custom_target(GUI_ButtonShowPlayerInside_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowPlayerInside" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowPlayerInside/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowPlayerInside/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonShowPlayerInside sequentially..."
)
add_dependencies(GUI_ButtonShowPlayerInside_build GUI_ImagePanelTools_build)

add_custom_target(GUI_MeasureShowGrid_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MeasureShowGrid" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MeasureShowGrid/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MeasureShowGrid/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/MeasureShowGrid sequentially..."
)
add_dependencies(GUI_MeasureShowGrid_build GUI_ButtonShowPlayerInside_build)

add_custom_target(GUI_TreeMasterImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/TreeMasterImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/TreeMasterImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/TreeMasterImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/TreeMasterImagePanel sequentially..."
)
add_dependencies(GUI_TreeMasterImagePanel_build GUI_MeasureShowGrid_build)

add_custom_target(GUI_PropertyTreeMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyTreeMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyTreeMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyTreeMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyTreeMaster sequentially..."
)
add_dependencies(GUI_PropertyTreeMaster_build GUI_TreeMasterImagePanel_build)

add_custom_target(GUI_TreeMasterShowResultList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/TreeMasterShowResultList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/TreeMasterShowResultList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/TreeMasterShowResultList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/TreeMasterShowResultList sequentially..."
)
add_dependencies(GUI_TreeMasterShowResultList_build GUI_PropertyTreeMaster_build)

add_custom_target(GUI_ButtonForMarkingON_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonForMarkingON" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonForMarkingON/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonForMarkingON/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonForMarkingON sequentially..."
)
add_dependencies(GUI_ButtonForMarkingON_build GUI_TreeMasterShowResultList_build)

add_custom_target(GUI_ShowOldNGNaming_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowOldNGNaming" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowOldNGNaming/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowOldNGNaming/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowOldNGNaming sequentially..."
)
add_dependencies(GUI_ShowOldNGNaming_build GUI_ButtonForMarkingON_build)

add_custom_target(GUI_DisplayOldImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayOldImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayOldImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayOldImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayOldImagePanel sequentially..."
)
add_dependencies(GUI_DisplayOldImagePanel_build GUI_ShowOldNGNaming_build)

add_custom_target(GUI_SetMechanicalOffset_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetMechanicalOffset" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetMechanicalOffset/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetMechanicalOffset/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SetMechanicalOffset sequentially..."
)
add_dependencies(GUI_SetMechanicalOffset_build GUI_DisplayOldImagePanel_build)

add_custom_target(GUI_ButtonAnyMode_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAnyMode" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAnyMode/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAnyMode/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonAnyMode sequentially..."
)
add_dependencies(GUI_ButtonAnyMode_build GUI_SetMechanicalOffset_build)

add_custom_target(GUI_ShowResultAlarm_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultAlarm" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultAlarm/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultAlarm/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowResultAlarm sequentially..."
)
add_dependencies(GUI_ShowResultAlarm_build GUI_ButtonAnyMode_build)

add_custom_target(GUI_ShowSeqMessage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowSeqMessage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowSeqMessage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowSeqMessage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowSeqMessage sequentially..."
)
add_dependencies(GUI_ShowSeqMessage_build GUI_ShowResultAlarm_build)

add_custom_target(GUI_BuslineImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/BuslineImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/BuslineImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/BuslineImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/BuslineImagePanel sequentially..."
)
add_dependencies(GUI_BuslineImagePanel_build GUI_ShowSeqMessage_build)

add_custom_target(GUI_PropertyBusline_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyBusline" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyBusline/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyBusline/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyBusline sequentially..."
)
add_dependencies(GUI_PropertyBusline_build GUI_BuslineImagePanel_build)

add_custom_target(GUI_WindUpImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/WindUpImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/WindUpImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/WindUpImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/WindUpImage sequentially..."
)
add_dependencies(GUI_WindUpImage_build GUI_PropertyBusline_build)

add_custom_target(GUI_AlignmentLargeImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentLargeImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentLargeImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentLargeImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AlignmentLargeImagePanel sequentially..."
)
add_dependencies(GUI_AlignmentLargeImagePanel_build GUI_WindUpImage_build)

add_custom_target(GUI_PropertyAlignmentLarge_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentLarge" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentLarge/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentLarge/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyAlignmentLarge sequentially..."
)
add_dependencies(GUI_PropertyAlignmentLarge_build GUI_AlignmentLargeImagePanel_build)

add_custom_target(GUI_PropertyResultBinder_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyResultBinder" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyResultBinder/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyResultBinder/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyResultBinder sequentially..."
)
add_dependencies(GUI_PropertyResultBinder_build GUI_PropertyAlignmentLarge_build)

add_custom_target(GUI_BCRImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/BCRImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/BCRImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/BCRImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/BCRImagePanel sequentially..."
)
add_dependencies(GUI_BCRImagePanel_build GUI_PropertyResultBinder_build)

add_custom_target(GUI_PropertyBCR_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyBCR" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyBCR/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyBCR/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyBCR sequentially..."
)
add_dependencies(GUI_PropertyBCR_build GUI_BCRImagePanel_build)

add_custom_target(GUI_ShowBarCode_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowBarCode" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowBarCode/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowBarCode/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowBarCode sequentially..."
)
add_dependencies(GUI_ShowBarCode_build GUI_PropertyBCR_build)

add_custom_target(GUI_ShowTotalNGNaming_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowTotalNGNaming" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowTotalNGNaming/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowTotalNGNaming/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowTotalNGNaming sequentially..."
)
add_dependencies(GUI_ShowTotalNGNaming_build GUI_ShowBarCode_build)

add_custom_target(GUI_SetSpetialValue_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetSpetialValue" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetSpetialValue/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetSpetialValue/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SetSpetialValue sequentially..."
)
add_dependencies(GUI_SetSpetialValue_build GUI_ShowTotalNGNaming_build)

add_custom_target(GUI_ButtonFilterUpsideDown_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonFilterUpsideDown" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonFilterUpsideDown/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonFilterUpsideDown/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonFilterUpsideDown sequentially..."
)
add_dependencies(GUI_ButtonFilterUpsideDown_build GUI_SetSpetialValue_build)

add_custom_target(GUI_ButtonLightON_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLightON" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLightON/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLightON/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLightON sequentially..."
)
add_dependencies(GUI_ButtonLightON_build GUI_ButtonFilterUpsideDown_build)

add_custom_target(GUI_ShowSumTimer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowSumTimer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowSumTimer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowSumTimer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowSumTimer sequentially..."
)
add_dependencies(GUI_ShowSumTimer_build GUI_ButtonLightON_build)

add_custom_target(GUI_ButtonPasswordEnabler_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonPasswordEnabler" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonPasswordEnabler/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonPasswordEnabler/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonPasswordEnabler sequentially..."
)
add_dependencies(GUI_ButtonPasswordEnabler_build GUI_ShowSumTimer_build)

add_custom_target(GUI_ButtonFilterUDColorShift_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonFilterUDColorShift" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonFilterUDColorShift/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonFilterUDColorShift/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonFilterUDColorShift sequentially..."
)
add_dependencies(GUI_ButtonFilterUDColorShift_build GUI_ButtonPasswordEnabler_build)

add_custom_target(GUI_FixedImageSize_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/FixedImageSize" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/FixedImageSize/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/FixedImageSize/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/FixedImageSize sequentially..."
)
add_dependencies(GUI_FixedImageSize_build GUI_ButtonFilterUDColorShift_build)

add_custom_target(GUI_ButtonPasswordOpener_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonPasswordOpener" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonPasswordOpener/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonPasswordOpener/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonPasswordOpener sequentially..."
)
add_dependencies(GUI_ButtonPasswordOpener_build GUI_FixedImageSize_build)

add_custom_target(GUI_PieceDefImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceDefImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceDefImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PieceDefImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PieceDefImagePanel sequentially..."
)
add_dependencies(GUI_PieceDefImagePanel_build GUI_ButtonPasswordOpener_build)

add_custom_target(GUI_PropertyPieceDef_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPieceDef" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPieceDef/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPieceDef/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyPieceDef sequentially..."
)
add_dependencies(GUI_PropertyPieceDef_build GUI_PieceDefImagePanel_build)

add_custom_target(GUI_ShowResultSmallLot_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultSmallLot" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultSmallLot/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultSmallLot/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowResultSmallLot sequentially..."
)
add_dependencies(GUI_ShowResultSmallLot_build GUI_PropertyPieceDef_build)

add_custom_target(GUI_ButtonSelectSmallLot_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectSmallLot" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectSmallLot/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectSmallLot/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSelectSmallLot sequentially..."
)
add_dependencies(GUI_ButtonSelectSmallLot_build GUI_ShowResultSmallLot_build)

add_custom_target(GUI_ListCondition_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListCondition" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListCondition/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListCondition/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ListCondition sequentially..."
)
add_dependencies(GUI_ListCondition_build GUI_ButtonSelectSmallLot_build)

add_custom_target(GUI_ShowStrategicAllNumber_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowStrategicAllNumber" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowStrategicAllNumber/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowStrategicAllNumber/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowStrategicAllNumber sequentially..."
)
add_dependencies(GUI_ShowStrategicAllNumber_build GUI_ListCondition_build)

add_custom_target(GUI_ButtonChangeServerForMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonChangeServerForMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonChangeServerForMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonChangeServerForMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonChangeServerForMaster sequentially..."
)
add_dependencies(GUI_ButtonChangeServerForMaster_build GUI_ShowStrategicAllNumber_build)

add_custom_target(GUI_GeneralPanelFromSeq_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralPanelFromSeq" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralPanelFromSeq/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralPanelFromSeq/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/GeneralPanelFromSeq sequentially..."
)
add_dependencies(GUI_GeneralPanelFromSeq_build GUI_ButtonChangeServerForMaster_build)

add_custom_target(GUI_CheckCycleTime_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckCycleTime" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckCycleTime/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckCycleTime/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CheckCycleTime sequentially..."
)
add_dependencies(GUI_CheckCycleTime_build GUI_GeneralPanelFromSeq_build)

add_custom_target(GUI_CheckBrightnessImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckBrightnessImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckBrightnessImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckBrightnessImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CheckBrightnessImagePanel sequentially..."
)
add_dependencies(GUI_CheckBrightnessImagePanel_build GUI_CheckCycleTime_build)

add_custom_target(GUI_PropertyCheckBrightness_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyCheckBrightness" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyCheckBrightness/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyCheckBrightness/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyCheckBrightness sequentially..."
)
add_dependencies(GUI_PropertyCheckBrightness_build GUI_CheckBrightnessImagePanel_build)

add_custom_target(GUI_ShowCheckBrightnessPanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCheckBrightnessPanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCheckBrightnessPanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCheckBrightnessPanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowCheckBrightnessPanel sequentially..."
)
add_dependencies(GUI_ShowCheckBrightnessPanel_build GUI_PropertyCheckBrightness_build)

add_custom_target(GUI_PropertyGerberFast_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyGerberFast" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyGerberFast/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyGerberFast/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyGerberFast sequentially..."
)
add_dependencies(GUI_PropertyGerberFast_build GUI_ShowCheckBrightnessPanel_build)

add_custom_target(GUI_GerberFastImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GerberFastImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GerberFastImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GerberFastImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/GerberFastImagePanel sequentially..."
)
add_dependencies(GUI_GerberFastImagePanel_build GUI_PropertyGerberFast_build)

add_custom_target(GUI_PropertyViaInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyViaInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyViaInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyViaInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyViaInspection sequentially..."
)
add_dependencies(GUI_PropertyViaInspection_build GUI_GerberFastImagePanel_build)

add_custom_target(GUI_VIAInspectionImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/VIAInspectionImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/VIAInspectionImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/VIAInspectionImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/VIAInspectionImagePanel sequentially..."
)
add_dependencies(GUI_VIAInspectionImagePanel_build GUI_PropertyViaInspection_build)

add_custom_target(GUI_PropertyCheckEveryday_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyCheckEveryday" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyCheckEveryday/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyCheckEveryday/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyCheckEveryday sequentially..."
)
add_dependencies(GUI_PropertyCheckEveryday_build GUI_VIAInspectionImagePanel_build)

add_custom_target(GUI_ShowCheckEveryday_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCheckEveryday" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCheckEveryday/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCheckEveryday/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowCheckEveryday sequentially..."
)
add_dependencies(GUI_ShowCheckEveryday_build GUI_PropertyCheckEveryday_build)

add_custom_target(GUI_CheckEverydayImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckEverydayImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckEverydayImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckEverydayImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CheckEverydayImagePanel sequentially..."
)
add_dependencies(GUI_CheckEverydayImagePanel_build GUI_ShowCheckEveryday_build)

add_custom_target(GUI_PanelXYSize_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelXYSize" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelXYSize/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelXYSize/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PanelXYSize sequentially..."
)
add_dependencies(GUI_PanelXYSize_build GUI_CheckEverydayImagePanel_build)

add_custom_target(GUI_SetFilterToMoveXY_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetFilterToMoveXY" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetFilterToMoveXY/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetFilterToMoveXY/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SetFilterToMoveXY sequentially..."
)
add_dependencies(GUI_SetFilterToMoveXY_build GUI_PanelXYSize_build)

add_custom_target(GUI_ButtonToSetFilter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToSetFilter" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToSetFilter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToSetFilter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonToSetFilter sequentially..."
)
add_dependencies(GUI_ButtonToSetFilter_build GUI_SetFilterToMoveXY_build)

add_custom_target(GUI_AdjustMoveAllAfterLoadMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AdjustMoveAllAfterLoadMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AdjustMoveAllAfterLoadMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AdjustMoveAllAfterLoadMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AdjustMoveAllAfterLoadMaster sequentially..."
)
add_dependencies(GUI_AdjustMoveAllAfterLoadMaster_build GUI_ButtonToSetFilter_build)

add_custom_target(GUI_PropertyMultiFileMap_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMultiFileMap" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMultiFileMap/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMultiFileMap/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyMultiFileMap sequentially..."
)
add_dependencies(GUI_PropertyMultiFileMap_build GUI_AdjustMoveAllAfterLoadMaster_build)

add_custom_target(GUI_MultiFileMapImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MultiFileMapImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MultiFileMapImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MultiFileMapImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/MultiFileMapImagePanel sequentially..."
)
add_dependencies(GUI_MultiFileMapImagePanel_build GUI_PropertyMultiFileMap_build)

add_custom_target(GUI_ButtonGeneralStocker_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonGeneralStocker" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonGeneralStocker/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonGeneralStocker/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonGeneralStocker sequentially..."
)
add_dependencies(GUI_ButtonGeneralStocker_build GUI_MultiFileMapImagePanel_build)

add_custom_target(GUI_ExecuteBatch_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExecuteBatch" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExecuteBatch/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExecuteBatch/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ExecuteBatch sequentially..."
)
add_dependencies(GUI_ExecuteBatch_build GUI_ButtonGeneralStocker_build)

add_custom_target(GUI_SaveMasterImageInInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveMasterImageInInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveMasterImageInInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveMasterImageInInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SaveMasterImageInInspection sequentially..."
)
add_dependencies(GUI_SaveMasterImageInInspection_build GUI_ExecuteBatch_build)

add_custom_target(GUI_CheckEverydayResultHistory_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckEverydayResultHistory" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckEverydayResultHistory/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckEverydayResultHistory/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CheckEverydayResultHistory sequentially..."
)
add_dependencies(GUI_CheckEverydayResultHistory_build GUI_SaveMasterImageInInspection_build)

add_custom_target(GUI_HookAlgorithmImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookAlgorithmImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookAlgorithmImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookAlgorithmImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/HookAlgorithmImagePanel sequentially..."
)
add_dependencies(GUI_HookAlgorithmImagePanel_build GUI_CheckEverydayResultHistory_build)

add_custom_target(GUI_ButtonSynchronizeImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSynchronizeImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSynchronizeImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSynchronizeImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSynchronizeImagePanel sequentially..."
)
add_dependencies(GUI_ButtonSynchronizeImagePanel_build GUI_HookAlgorithmImagePanel_build)

add_custom_target(GUI_SaveTargetInNG_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveTargetInNG" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveTargetInNG/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveTargetInNG/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SaveTargetInNG sequentially..."
)
add_dependencies(GUI_SaveTargetInNG_build GUI_ButtonSynchronizeImagePanel_build)

add_custom_target(GUI_SaveOutlineOffsetInMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveOutlineOffsetInMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveOutlineOffsetInMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SaveOutlineOffsetInMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SaveOutlineOffsetInMaster sequentially..."
)
add_dependencies(GUI_SaveOutlineOffsetInMaster_build GUI_SaveTargetInNG_build)

add_custom_target(GUI_LoadOutlineOffsetInMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadOutlineOffsetInMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadOutlineOffsetInMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadOutlineOffsetInMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/LoadOutlineOffsetInMaster sequentially..."
)
add_dependencies(GUI_LoadOutlineOffsetInMaster_build GUI_SaveOutlineOffsetInMaster_build)

add_custom_target(GUI_ThinMetalImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ThinMetalImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ThinMetalImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ThinMetalImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ThinMetalImagePanel sequentially..."
)
add_dependencies(GUI_ThinMetalImagePanel_build GUI_LoadOutlineOffsetInMaster_build)

add_custom_target(GUI_PropertyThinMetal_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyThinMetal" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyThinMetal/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyThinMetal/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyThinMetal sequentially..."
)
add_dependencies(GUI_PropertyThinMetal_build GUI_ThinMetalImagePanel_build)

add_custom_target(GUI_DistinguishPix_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DistinguishPix" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DistinguishPix/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DistinguishPix/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DistinguishPix sequentially..."
)
add_dependencies(GUI_DistinguishPix_build GUI_PropertyThinMetal_build)

add_custom_target(GUI_ButtonToStoreSamplesThinMetal_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToStoreSamplesThinMetal" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToStoreSamplesThinMetal/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToStoreSamplesThinMetal/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonToStoreSamplesThinMetal sequentially..."
)
add_dependencies(GUI_ButtonToStoreSamplesThinMetal_build GUI_DistinguishPix_build)

add_custom_target(InspectionEditor_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/InspectionEditor" -B "${CMAKE_CURRENT_SOURCE_DIR}/InspectionEditor/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/InspectionEditor/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building InspectionEditor sequentially..."
)
add_dependencies(InspectionEditor_build GUI_ButtonToStoreSamplesThinMetal_build)

add_custom_target(InspectionPlayer_InspectionPlayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/InspectionPlayer/InspectionPlayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/InspectionPlayer/InspectionPlayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/InspectionPlayer/InspectionPlayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building InspectionPlayer/InspectionPlayer sequentially..."
)
add_dependencies(InspectionPlayer_InspectionPlayer_build InspectionEditor_build)

add_custom_target(PluginDLL_Light_LightDLL_CCSControl_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControl" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControl/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControl/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Light/LightDLL/CCSControl sequentially..."
)
add_dependencies(PluginDLL_Light_LightDLL_CCSControl_build InspectionPlayer_InspectionPlayer_build)

add_custom_target(PluginDLL_Light_LightDLL_CCSControl2_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControl2" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControl2/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControl2/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Light/LightDLL/CCSControl2 sequentially..."
)
add_dependencies(PluginDLL_Light_LightDLL_CCSControl2_build PluginDLL_Light_LightDLL_CCSControl_build)

add_custom_target(GUI_Light_CCSControlGUI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Light/CCSControlGUI" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Light/CCSControlGUI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Light/CCSControlGUI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/Light/CCSControlGUI sequentially..."
)
add_dependencies(GUI_Light_CCSControlGUI_build PluginDLL_Light_LightDLL_CCSControl2_build)

add_custom_target(GUI_Light_CCSControl2GUI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Light/CCSControl2GUI" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Light/CCSControl2GUI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Light/CCSControl2GUI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/Light/CCSControl2GUI sequentially..."
)
add_dependencies(GUI_Light_CCSControl2GUI_build GUI_Light_CCSControlGUI_build)

add_custom_target(PluginDLL_Light_LightDLL_ControlHayashiTokei_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/ControlHayashiTokei" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/ControlHayashiTokei/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/ControlHayashiTokei/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Light/LightDLL/ControlHayashiTokei sequentially..."
)
add_dependencies(PluginDLL_Light_LightDLL_ControlHayashiTokei_build GUI_Light_CCSControl2GUI_build)

add_custom_target(GUI_Light_ControlHayashiTokeiGUI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Light/ControlHayashiTokeiGUI" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Light/ControlHayashiTokeiGUI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Light/ControlHayashiTokeiGUI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/Light/ControlHayashiTokeiGUI sequentially..."
)
add_dependencies(GUI_Light_ControlHayashiTokeiGUI_build PluginDLL_Light_LightDLL_ControlHayashiTokei_build)

add_custom_target(PluginDLL_Light_LightDLL_CCSControlByPIO_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControlByPIO" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControlByPIO/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControlByPIO/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Light/LightDLL/CCSControlByPIO sequentially..."
)
add_dependencies(PluginDLL_Light_LightDLL_CCSControlByPIO_build GUI_Light_ControlHayashiTokeiGUI_build)

add_custom_target(PluginDLL_Light_LightDLL_LightUSB8PortARM_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LightUSB8PortARM" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LightUSB8PortARM/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LightUSB8PortARM/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Light/LightDLL/LightUSB8PortARM sequentially..."
)
add_dependencies(PluginDLL_Light_LightDLL_LightUSB8PortARM_build PluginDLL_Light_LightDLL_CCSControlByPIO_build)

add_custom_target(PluginDLL_Light_LightDLL_LightDLLRemoteController_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LightDLLRemoteController" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LightDLLRemoteController/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LightDLLRemoteController/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Light/LightDLL/LightDLLRemoteController sequentially..."
)
add_dependencies(PluginDLL_Light_LightDLL_LightDLLRemoteController_build PluginDLL_Light_LightDLL_LightUSB8PortARM_build)

add_custom_target(PluginDLL_Light_LightDLL_CCSControlByPIO2Ch_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControlByPIO2Ch" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControlByPIO2Ch/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControlByPIO2Ch/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Light/LightDLL/CCSControlByPIO2Ch sequentially..."
)
add_dependencies(PluginDLL_Light_LightDLL_CCSControlByPIO2Ch_build PluginDLL_Light_LightDLL_LightDLLRemoteController_build)

add_custom_target(PluginDLL_Light_LightDLL_LEDControl32_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LEDControl32" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LEDControl32/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LEDControl32/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Light/LightDLL/LEDControl32 sequentially..."
)
add_dependencies(PluginDLL_Light_LightDLL_LEDControl32_build PluginDLL_Light_LightDLL_CCSControlByPIO2Ch_build)

add_custom_target(PluginDLL_PIO_Contec64DLL_Contec64DLL_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/Contec64DLL/Contec64DLL" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/Contec64DLL/Contec64DLL/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/Contec64DLL/Contec64DLL/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/Contec64DLL/Contec64DLL sequentially..."
)
add_dependencies(PluginDLL_PIO_Contec64DLL_Contec64DLL_build PluginDLL_Light_LightDLL_LEDControl32_build)

add_custom_target(PluginDLL_PIO_Contec64DLL2_Contec64DLL_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/Contec64DLL2/Contec64DLL" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/Contec64DLL2/Contec64DLL/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/Contec64DLL2/Contec64DLL/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/Contec64DLL2/Contec64DLL sequentially..."
)
add_dependencies(PluginDLL_PIO_Contec64DLL2_Contec64DLL_build PluginDLL_PIO_Contec64DLL_Contec64DLL_build)

add_custom_target(PluginDLL_PIO_Contec64Multi_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/Contec64Multi" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/Contec64Multi/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/Contec64Multi/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/Contec64Multi sequentially..."
)
add_dependencies(PluginDLL_PIO_Contec64Multi_build PluginDLL_PIO_Contec64DLL2_Contec64DLL_build)

add_custom_target(PluginDLL_PIO_NetworkContec64_PIOClient_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkContec64/PIOClient" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkContec64/PIOClient/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkContec64/PIOClient/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/NetworkContec64/PIOClient sequentially..."
)
add_dependencies(PluginDLL_PIO_NetworkContec64_PIOClient_build PluginDLL_PIO_Contec64Multi_build)

add_custom_target(PluginDLL_PIO_NetworkContec64_PIODevicer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkContec64/PIODevicer" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkContec64/PIODevicer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkContec64/PIODevicer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/NetworkContec64/PIODevicer sequentially..."
)
add_dependencies(PluginDLL_PIO_NetworkContec64_PIODevicer_build PluginDLL_PIO_NetworkContec64_PIOClient_build)

add_custom_target(PluginDLL_PIO_DummyPIO_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/DummyPIO" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/DummyPIO/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/DummyPIO/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/DummyPIO sequentially..."
)
add_dependencies(PluginDLL_PIO_DummyPIO_build PluginDLL_PIO_NetworkContec64_PIODevicer_build)

add_custom_target(PluginDLL_PIO_TestPIODLL_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/TestPIODLL" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/TestPIODLL/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/TestPIODLL/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/TestPIODLL sequentially..."
)
add_dependencies(PluginDLL_PIO_TestPIODLL_build PluginDLL_PIO_DummyPIO_build)

add_custom_target(PluginDLL_PIO_ContecBitAccess_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/ContecBitAccess" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/ContecBitAccess/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/ContecBitAccess/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/ContecBitAccess sequentially..."
)
add_dependencies(PluginDLL_PIO_ContecBitAccess_build PluginDLL_PIO_TestPIODLL_build)

add_custom_target(PluginDLL_PIO_VirtualPIOServer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/VirtualPIOServer" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/VirtualPIOServer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/VirtualPIOServer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/VirtualPIOServer sequentially..."
)
add_dependencies(PluginDLL_PIO_VirtualPIOServer_build PluginDLL_PIO_ContecBitAccess_build)

add_custom_target(PluginDLL_PIO_VirtualPIOAdapter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/VirtualPIOAdapter" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/VirtualPIOAdapter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/VirtualPIOAdapter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/VirtualPIOAdapter sequentially..."
)
add_dependencies(PluginDLL_PIO_VirtualPIOAdapter_build PluginDLL_PIO_VirtualPIOServer_build)

add_custom_target(ResultDLL_ResultXMLV3_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLV3" -B "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLV3/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLV3/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ResultDLL/ResultXMLV3 sequentially..."
)
add_dependencies(ResultDLL_ResultXMLV3_build PluginDLL_PIO_VirtualPIOAdapter_build)

add_custom_target(ResultDLL_ResultXMLForPiece_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLForPiece" -B "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLForPiece/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLForPiece/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ResultDLL/ResultXMLForPiece sequentially..."
)
add_dependencies(ResultDLL_ResultXMLForPiece_build ResultDLL_ResultXMLV3_build)

add_custom_target(ResultDLL_ResultXMLSmallLot_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLSmallLot" -B "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLSmallLot/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLSmallLot/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ResultDLL/ResultXMLSmallLot sequentially..."
)
add_dependencies(ResultDLL_ResultXMLSmallLot_build ResultDLL_ResultXMLForPiece_build)

add_custom_target(Delete_Delete_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Delete/Delete" -B "${CMAKE_CURRENT_SOURCE_DIR}/Delete/Delete/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Delete/Delete/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Delete/Delete sequentially..."
)
add_dependencies(Delete_Delete_build ResultDLL_ResultXMLSmallLot_build)

add_custom_target(EditGUI_EditGUI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/EditGUI/EditGUI" -B "${CMAKE_CURRENT_SOURCE_DIR}/EditGUI/EditGUI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/EditGUI/EditGUI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building EditGUI/EditGUI sequentially..."
)
add_dependencies(EditGUI_EditGUI_build Delete_Delete_build)

add_custom_target(EditParameter_EditParameter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/EditParameter/EditParameter" -B "${CMAKE_CURRENT_SOURCE_DIR}/EditParameter/EditParameter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/EditParameter/EditParameter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building EditParameter/EditParameter sequentially..."
)
add_dependencies(EditParameter_EditParameter_build EditGUI_EditGUI_build)

add_custom_target(EditStatusComment_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/EditStatusComment" -B "${CMAKE_CURRENT_SOURCE_DIR}/EditStatusComment/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/EditStatusComment/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building EditStatusComment sequentially..."
)
add_dependencies(EditStatusComment_build EditParameter_EditParameter_build)

add_custom_target(FileRegistryEditor_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/FileRegistryEditor" -B "${CMAKE_CURRENT_SOURCE_DIR}/FileRegistryEditor/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/FileRegistryEditor/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building FileRegistryEditor sequentially..."
)
add_dependencies(FileRegistryEditor_build EditStatusComment_build)

add_custom_target(LearningServer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/LearningServer" -B "${CMAKE_CURRENT_SOURCE_DIR}/LearningServer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/LearningServer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building LearningServer sequentially..."
)
add_dependencies(LearningServer_build FileRegistryEditor_build)

add_custom_target(Messager_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Messager" -B "${CMAKE_CURRENT_SOURCE_DIR}/Messager/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Messager/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Messager sequentially..."
)
add_dependencies(Messager_build LearningServer_build)

add_custom_target(Messager_ReportDisk_ReportDisk_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Messager/ReportDisk/ReportDisk" -B "${CMAKE_CURRENT_SOURCE_DIR}/Messager/ReportDisk/ReportDisk/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Messager/ReportDisk/ReportDisk/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Messager/ReportDisk/ReportDisk sequentially..."
)
add_dependencies(Messager_ReportDisk_ReportDisk_build Messager_build)

add_custom_target(PIOWatch_PIOWatch_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PIOWatch/PIOWatch" -B "${CMAKE_CURRENT_SOURCE_DIR}/PIOWatch/PIOWatch/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PIOWatch/PIOWatch/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PIOWatch/PIOWatch sequentially..."
)
add_dependencies(PIOWatch_PIOWatch_build Messager_ReportDisk_ReportDisk_build)

add_custom_target(ServiceLib_DLLChecker_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DLLChecker" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DLLChecker/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DLLChecker/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/DLLChecker sequentially..."
)
add_dependencies(ServiceLib_DLLChecker_build PIOWatch_PIOWatch_build)

add_custom_target(ServiceLib_ServiceForDBLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ServiceForDBLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ServiceForDBLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ServiceForDBLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/ServiceForDBLib sequentially..."
)
add_dependencies(ServiceLib_ServiceForDBLib_build ServiceLib_DLLChecker_build)

add_custom_target(ServiceLib_SlaveIndicator_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/SlaveIndicator" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/SlaveIndicator/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/SlaveIndicator/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/SlaveIndicator sequentially..."
)
add_dependencies(ServiceLib_SlaveIndicator_build ServiceLib_ServiceForDBLib_build)

add_custom_target(AutoStart_AutoStartPlayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/AutoStart/AutoStartPlayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/AutoStart/AutoStartPlayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/AutoStart/AutoStartPlayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building AutoStart/AutoStartPlayer sequentially..."
)
add_dependencies(AutoStart_AutoStartPlayer_build ServiceLib_SlaveIndicator_build)

add_custom_target(AutoStartList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/AutoStartList" -B "${CMAKE_CURRENT_SOURCE_DIR}/AutoStartList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/AutoStartList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building AutoStartList sequentially..."
)
add_dependencies(AutoStartList_build AutoStart_AutoStartPlayer_build)

add_custom_target(ServiceLib_EditSequence_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/EditSequence" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/EditSequence/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/EditSequence/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/EditSequence sequentially..."
)
add_dependencies(ServiceLib_EditSequence_build AutoStartList_build)

add_custom_target(ChangeServer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ChangeServer" -B "${CMAKE_CURRENT_SOURCE_DIR}/ChangeServer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ChangeServer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ChangeServer sequentially..."
)
add_dependencies(ChangeServer_build ServiceLib_EditSequence_build)

add_custom_target(ServiceLib_EditAnyDataInLibrary_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/EditAnyDataInLibrary" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/EditAnyDataInLibrary/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/EditAnyDataInLibrary/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/EditAnyDataInLibrary sequentially..."
)
add_dependencies(ServiceLib_EditAnyDataInLibrary_build ChangeServer_build)

add_custom_target(XmlServer_XMLExplorer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/XmlServer/XMLExplorer" -B "${CMAKE_CURRENT_SOURCE_DIR}/XmlServer/XMLExplorer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/XmlServer/XMLExplorer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building XmlServer/XMLExplorer sequentially..."
)
add_dependencies(XmlServer_XMLExplorer_build ServiceLib_EditAnyDataInLibrary_build)

add_custom_target(ExecuteVisualizer_EditExecuteVisualizer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ExecuteVisualizer/EditExecuteVisualizer" -B "${CMAKE_CURRENT_SOURCE_DIR}/ExecuteVisualizer/EditExecuteVisualizer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ExecuteVisualizer/EditExecuteVisualizer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ExecuteVisualizer/EditExecuteVisualizer sequentially..."
)
add_dependencies(ExecuteVisualizer_EditExecuteVisualizer_build XmlServer_XMLExplorer_build)

add_custom_target(JDTUnpacker_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/JDTUnpacker" -B "${CMAKE_CURRENT_SOURCE_DIR}/JDTUnpacker/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/JDTUnpacker/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building JDTUnpacker sequentially..."
)
add_dependencies(JDTUnpacker_build ExecuteVisualizer_EditExecuteVisualizer_build)

add_custom_target(PIOWatch_PIOViewer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PIOWatch/PIOViewer" -B "${CMAKE_CURRENT_SOURCE_DIR}/PIOWatch/PIOViewer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PIOWatch/PIOViewer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PIOWatch/PIOViewer sequentially..."
)
add_dependencies(PIOWatch_PIOViewer_build JDTUnpacker_build)

add_custom_target(EditParameter_EditGlobalOnMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/EditParameter/EditGlobalOnMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/EditParameter/EditGlobalOnMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/EditParameter/EditGlobalOnMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building EditParameter/EditGlobalOnMaster sequentially..."
)
add_dependencies(EditParameter_EditGlobalOnMaster_build PIOWatch_PIOViewer_build)

add_custom_target(ServiceLib_MakeMasterReport_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/MakeMasterReport" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/MakeMasterReport/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/MakeMasterReport/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/MakeMasterReport sequentially..."
)
add_dependencies(ServiceLib_MakeMasterReport_build EditParameter_EditGlobalOnMaster_build)

add_custom_target(ServiceLib_LanguageManager_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/LanguageManager" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/LanguageManager/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/LanguageManager/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/LanguageManager sequentially..."
)
add_dependencies(ServiceLib_LanguageManager_build ServiceLib_MakeMasterReport_build)

add_custom_target(LanguageSolver_LanguageNewSolver_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/LanguageSolver/LanguageNewSolver" -B "${CMAKE_CURRENT_SOURCE_DIR}/LanguageSolver/LanguageNewSolver/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/LanguageSolver/LanguageNewSolver/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building LanguageSolver/LanguageNewSolver sequentially..."
)
add_dependencies(LanguageSolver_LanguageNewSolver_build ServiceLib_LanguageManager_build)

add_custom_target(ChangeServer_CloseProcess_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ChangeServer/CloseProcess" -B "${CMAKE_CURRENT_SOURCE_DIR}/ChangeServer/CloseProcess/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ChangeServer/CloseProcess/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ChangeServer/CloseProcess sequentially..."
)
add_dependencies(ChangeServer_CloseProcess_build LanguageSolver_LanguageNewSolver_build)

add_custom_target(ChangeServer_RemoteControlToClose_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ChangeServer/RemoteControlToClose" -B "${CMAKE_CURRENT_SOURCE_DIR}/ChangeServer/RemoteControlToClose/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ChangeServer/RemoteControlToClose/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ChangeServer/RemoteControlToClose sequentially..."
)
add_dependencies(ChangeServer_RemoteControlToClose_build ChangeServer_CloseProcess_build)

add_custom_target(ServiceLib_LanguageMergeXLSX_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/LanguageMergeXLSX" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/LanguageMergeXLSX/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/LanguageMergeXLSX/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/LanguageMergeXLSX sequentially..."
)
add_dependencies(ServiceLib_LanguageMergeXLSX_build ChangeServer_RemoteControlToClose_build)

add_custom_target(CopyMultiple_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/CopyMultiple" -B "${CMAKE_CURRENT_SOURCE_DIR}/CopyMultiple/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/CopyMultiple/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building CopyMultiple sequentially..."
)
add_dependencies(CopyMultiple_build ServiceLib_LanguageMergeXLSX_build)

add_custom_target(LightingManager_TesterLightDLL_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/LightingManager/TesterLightDLL" -B "${CMAKE_CURRENT_SOURCE_DIR}/LightingManager/TesterLightDLL/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/LightingManager/TesterLightDLL/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building LightingManager/TesterLightDLL sequentially..."
)
add_dependencies(LightingManager_TesterLightDLL_build CopyMultiple_build)

add_custom_target(LightingManager_RemoteLightController_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/LightingManager/RemoteLightController" -B "${CMAKE_CURRENT_SOURCE_DIR}/LightingManager/RemoteLightController/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/LightingManager/RemoteLightController/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building LightingManager/RemoteLightController sequentially..."
)
add_dependencies(LightingManager_RemoteLightController_build LightingManager_TesterLightDLL_build)

add_custom_target(ServiceLib_ScreenLock_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ScreenLock" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ScreenLock/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ScreenLock/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/ScreenLock sequentially..."
)
add_dependencies(ServiceLib_ScreenLock_build LightingManager_RemoteLightController_build)

add_custom_target(ServiceLib_DelayExe_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DelayExe" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DelayExe/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DelayExe/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/DelayExe sequentially..."
)
add_dependencies(ServiceLib_DelayExe_build ServiceLib_ScreenLock_build)

add_custom_target(LightingManager_RemoteLightExecuter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/LightingManager/RemoteLightExecuter" -B "${CMAKE_CURRENT_SOURCE_DIR}/LightingManager/RemoteLightExecuter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/LightingManager/RemoteLightExecuter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building LightingManager/RemoteLightExecuter sequentially..."
)
add_dependencies(LightingManager_RemoteLightExecuter_build ServiceLib_DelayExe_build)

add_custom_target(ServiceLib_Booter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/Booter" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/Booter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/Booter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/Booter sequentially..."
)
add_dependencies(ServiceLib_Booter_build LightingManager_RemoteLightExecuter_build)

add_custom_target(ServiceLib_SyncMasterFiles_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/SyncMasterFiles" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/SyncMasterFiles/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/SyncMasterFiles/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/SyncMasterFiles sequentially..."
)
add_dependencies(ServiceLib_SyncMasterFiles_build ServiceLib_Booter_build)

add_custom_target(ServiceLib_SyncDatabase_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/SyncDatabase" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/SyncDatabase/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/SyncDatabase/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/SyncDatabase sequentially..."
)
add_dependencies(ServiceLib_SyncDatabase_build ServiceLib_SyncMasterFiles_build)

add_custom_target(ServiceLib_WatchdogRebooter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/WatchdogRebooter" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/WatchdogRebooter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/WatchdogRebooter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/WatchdogRebooter sequentially..."
)
add_dependencies(ServiceLib_WatchdogRebooter_build ServiceLib_SyncDatabase_build)

add_custom_target(ServiceLib_ForceRebooter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ForceRebooter" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ForceRebooter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ForceRebooter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/ForceRebooter sequentially..."
)
add_dependencies(ServiceLib_ForceRebooter_build ServiceLib_WatchdogRebooter_build)

add_custom_target(Messager_DiskManager_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Messager/DiskManager" -B "${CMAKE_CURRENT_SOURCE_DIR}/Messager/DiskManager/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Messager/DiskManager/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Messager/DiskManager sequentially..."
)
add_dependencies(Messager_DiskManager_build ServiceLib_ForceRebooter_build)

add_custom_target(Data_management_Data_management_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Data management/Data management" -B "${CMAKE_CURRENT_SOURCE_DIR}/Data management/Data management/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Data management/Data management/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Data management/Data management sequentially..."
)
add_dependencies(Data_management_Data_management_build Messager_DiskManager_build)

add_custom_target(PluginDLL_SequencePlugin_SampleDLL_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/SampleDLL" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/SampleDLL/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/SampleDLL/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/SequencePlugin/SampleDLL sequentially..."
)
add_dependencies(PluginDLL_SequencePlugin_SampleDLL_build Data_management_Data_management_build)

add_custom_target(PluginDLL_SequencePlugin_LogWriter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/LogWriter" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/LogWriter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/LogWriter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/SequencePlugin/LogWriter sequentially..."
)
add_dependencies(PluginDLL_SequencePlugin_LogWriter_build PluginDLL_SequencePlugin_SampleDLL_build)

add_custom_target(PluginDLL_SequencePlugin_SeqFor64Connector_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/SeqFor64Connector" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/SeqFor64Connector/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/SeqFor64Connector/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/SequencePlugin/SeqFor64Connector sequentially..."
)
add_dependencies(PluginDLL_SequencePlugin_SeqFor64Connector_build PluginDLL_SequencePlugin_LogWriter_build)

add_custom_target(PluginDLL_SequencePlugin_IOLogger_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/IOLogger" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/IOLogger/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/IOLogger/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/SequencePlugin/IOLogger sequentially..."
)
add_dependencies(PluginDLL_SequencePlugin_IOLogger_build PluginDLL_SequencePlugin_SeqFor64Connector_build)

add_custom_target(PluginDLL_SequencePlugin_OutputMessager_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/OutputMessager" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/OutputMessager/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/OutputMessager/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/SequencePlugin/OutputMessager sequentially..."
)
add_dependencies(PluginDLL_SequencePlugin_OutputMessager_build PluginDLL_SequencePlugin_IOLogger_build)

add_custom_target(PluginDLL_SequencePlugin_CheckProgramRun_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/CheckProgramRun" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/CheckProgramRun/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/CheckProgramRun/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/SequencePlugin/CheckProgramRun sequentially..."
)
add_dependencies(PluginDLL_SequencePlugin_CheckProgramRun_build PluginDLL_SequencePlugin_OutputMessager_build)

add_custom_target(PluginDLL_SequencePlugin_ShutDownDLL_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/ShutDownDLL" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/ShutDownDLL/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/ShutDownDLL/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/SequencePlugin/ShutDownDLL sequentially..."
)
add_dependencies(PluginDLL_SequencePlugin_ShutDownDLL_build PluginDLL_SequencePlugin_CheckProgramRun_build)

add_custom_target(PluginDLL_SequencePlugin_PlaySound_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/PlaySound" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/PlaySound/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/PlaySound/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/SequencePlugin/PlaySound sequentially..."
)
add_dependencies(PluginDLL_SequencePlugin_PlaySound_build PluginDLL_SequencePlugin_ShutDownDLL_build)

add_custom_target(GUI_ChangeWindowSizeInvisible_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeWindowSizeInvisible" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeWindowSizeInvisible/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeWindowSizeInvisible/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ChangeWindowSizeInvisible sequentially..."
)
add_dependencies(GUI_ChangeWindowSizeInvisible_build PluginDLL_SequencePlugin_PlaySound_build)

add_custom_target(GUI_CopyItemsBetweenPhase_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CopyItemsBetweenPhase" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CopyItemsBetweenPhase/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CopyItemsBetweenPhase/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CopyItemsBetweenPhase sequentially..."
)
add_dependencies(GUI_CopyItemsBetweenPhase_build GUI_ChangeWindowSizeInvisible_build)

add_custom_target(GUI_FixedWindowSize_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/FixedWindowSize" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/FixedWindowSize/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/FixedWindowSize/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/FixedWindowSize sequentially..."
)
add_dependencies(GUI_FixedWindowSize_build GUI_CopyItemsBetweenPhase_build)

add_custom_target(Algorithm_ProjectedInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ProjectedInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ProjectedInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ProjectedInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/ProjectedInspection sequentially..."
)
add_dependencies(Algorithm_ProjectedInspection_build GUI_FixedWindowSize_build)

add_custom_target(GUI_PropertyProjectedInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyProjectedInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyProjectedInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyProjectedInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyProjectedInspection sequentially..."
)
add_dependencies(GUI_PropertyProjectedInspection_build Algorithm_ProjectedInspection_build)

add_custom_target(GUI_ProjectedInspectionImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ProjectedInspectionImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ProjectedInspectionImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ProjectedInspectionImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ProjectedInspectionImagePanel sequentially..."
)
add_dependencies(GUI_ProjectedInspectionImagePanel_build GUI_PropertyProjectedInspection_build)

add_custom_target(PluginDLL_PIO_VirtualPIOClient_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/VirtualPIOClient" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/VirtualPIOClient/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/VirtualPIOClient/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/VirtualPIOClient sequentially..."
)
add_dependencies(PluginDLL_PIO_VirtualPIOClient_build GUI_ProjectedInspectionImagePanel_build)

add_custom_target(ResultDLL_ResultWriteCSV_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultWriteCSV" -B "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultWriteCSV/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultWriteCSV/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ResultDLL/ResultWriteCSV sequentially..."
)
add_dependencies(ResultDLL_ResultWriteCSV_build PluginDLL_PIO_VirtualPIOClient_build)

add_custom_target(GUI_ButtonLightShortCut_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLightShortCut" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLightShortCut/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLightShortCut/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLightShortCut sequentially..."
)
add_dependencies(GUI_ButtonLightShortCut_build ResultDLL_ResultWriteCSV_build)

add_custom_target(Filter_FilterReplaceColor_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReplaceColor" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReplaceColor/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReplaceColor/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReplaceColor sequentially..."
)
add_dependencies(Filter_FilterReplaceColor_build GUI_ButtonLightShortCut_build)

add_custom_target(GUI_ResultBinderImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ResultBinderImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ResultBinderImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ResultBinderImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ResultBinderImagePanel sequentially..."
)
add_dependencies(GUI_ResultBinderImagePanel_build Filter_FilterReplaceColor_build)

add_custom_target(Filter_FilterDifferencialHV_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterDifferencialHV" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterDifferencialHV/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterDifferencialHV/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterDifferencialHV sequentially..."
)
add_dependencies(Filter_FilterDifferencialHV_build GUI_ResultBinderImagePanel_build)

add_custom_target(GUI_CompressImageIndicator_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CompressImageIndicator" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CompressImageIndicator/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CompressImageIndicator/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CompressImageIndicator sequentially..."
)
add_dependencies(GUI_CompressImageIndicator_build Filter_FilterDifferencialHV_build)

add_custom_target(GUI_ShowMatrixImageCenter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMatrixImageCenter" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMatrixImageCenter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMatrixImageCenter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowMatrixImageCenter sequentially..."
)
add_dependencies(GUI_ShowMatrixImageCenter_build GUI_CompressImageIndicator_build)

add_custom_target(GUI_HoughInspectionImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HoughInspectionImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HoughInspectionImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HoughInspectionImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/HoughInspectionImagePanel sequentially..."
)
add_dependencies(GUI_HoughInspectionImagePanel_build GUI_ShowMatrixImageCenter_build)

add_custom_target(GUI_PropertyHoughInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyHoughInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyHoughInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyHoughInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyHoughInspection sequentially..."
)
add_dependencies(GUI_PropertyHoughInspection_build GUI_HoughInspectionImagePanel_build)

add_custom_target(Algorithm_HoughInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/HoughInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/HoughInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/HoughInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/HoughInspection sequentially..."
)
add_dependencies(Algorithm_HoughInspection_build GUI_PropertyHoughInspection_build)

add_custom_target(ServiceLib_ConvertPixImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ConvertPixImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ConvertPixImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ConvertPixImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/ConvertPixImage sequentially..."
)
add_dependencies(ServiceLib_ConvertPixImage_build Algorithm_HoughInspection_build)

add_custom_target(GUI_ResetCameraSeq_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ResetCameraSeq" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ResetCameraSeq/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ResetCameraSeq/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ResetCameraSeq sequentially..."
)
add_dependencies(GUI_ResetCameraSeq_build ServiceLib_ConvertPixImage_build)

add_custom_target(ServiceLib_DFSServer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DFSServer" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DFSServer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DFSServer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/DFSServer sequentially..."
)
add_dependencies(ServiceLib_DFSServer_build GUI_ResetCameraSeq_build)

add_custom_target(ServiceLib_DFSProvider_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DFSProvider" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DFSProvider/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DFSProvider/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/DFSProvider sequentially..."
)
add_dependencies(ServiceLib_DFSProvider_build ServiceLib_DFSServer_build)

add_custom_target(ServiceLib_DFSExplorer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DFSExplorer" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DFSExplorer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DFSExplorer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/DFSExplorer sequentially..."
)
add_dependencies(ServiceLib_DFSExplorer_build ServiceLib_DFSProvider_build)

add_custom_target(ServiceLib_DFSProvider_DFSFilterMJC_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DFSProvider/DFSFilterMJC" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DFSProvider/DFSFilterMJC/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/DFSProvider/DFSFilterMJC/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/DFSProvider/DFSFilterMJC sequentially..."
)
add_dependencies(ServiceLib_DFSProvider_DFSFilterMJC_build ServiceLib_DFSExplorer_build)

add_custom_target(ServiceLib_ChangeAttribute_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ChangeAttribute" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ChangeAttribute/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ChangeAttribute/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/ChangeAttribute sequentially..."
)
add_dependencies(ServiceLib_ChangeAttribute_build ServiceLib_DFSProvider_DFSFilterMJC_build)

add_custom_target(ServiceLib_CheckKeyCode_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/CheckKeyCode" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/CheckKeyCode/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/CheckKeyCode/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/CheckKeyCode sequentially..."
)
add_dependencies(ServiceLib_CheckKeyCode_build ServiceLib_ChangeAttribute_build)

add_custom_target(Algorithm_PartialImaging_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PartialImaging" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PartialImaging/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PartialImaging/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/PartialImaging sequentially..."
)
add_dependencies(Algorithm_PartialImaging_build ServiceLib_CheckKeyCode_build)

add_custom_target(GUI_PartialImagingImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PartialImagingImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PartialImagingImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PartialImagingImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PartialImagingImagePanel sequentially..."
)
add_dependencies(GUI_PartialImagingImagePanel_build Algorithm_PartialImaging_build)

add_custom_target(GUI_PropertyPartialImaging_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPartialImaging" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPartialImaging/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPartialImaging/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyPartialImaging sequentially..."
)
add_dependencies(GUI_PropertyPartialImaging_build GUI_PartialImagingImagePanel_build)

add_custom_target(GUI_ShowPartialImagingList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowPartialImagingList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowPartialImagingList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowPartialImagingList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowPartialImagingList sequentially..."
)
add_dependencies(GUI_ShowPartialImagingList_build GUI_PropertyPartialImaging_build)

add_custom_target(GUI_ShowPartialImagingPanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowPartialImagingPanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowPartialImagingPanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowPartialImagingPanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowPartialImagingPanel sequentially..."
)
add_dependencies(GUI_ShowPartialImagingPanel_build GUI_ShowPartialImagingList_build)

add_custom_target(GUI_CameraBuffer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CameraBuffer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CameraBuffer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CameraBuffer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CameraBuffer sequentially..."
)
add_dependencies(GUI_CameraBuffer_build GUI_ShowPartialImagingPanel_build)

add_custom_target(Algorithm_SkipMark_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/SkipMark" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/SkipMark/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/SkipMark/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/SkipMark sequentially..."
)
add_dependencies(Algorithm_SkipMark_build GUI_CameraBuffer_build)

add_custom_target(GUI_PropertySkipMark_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertySkipMark" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertySkipMark/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertySkipMark/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertySkipMark sequentially..."
)
add_dependencies(GUI_PropertySkipMark_build Algorithm_SkipMark_build)

add_custom_target(GUI_SkipMarkImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SkipMarkImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SkipMarkImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SkipMarkImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SkipMarkImagePanel sequentially..."
)
add_dependencies(GUI_SkipMarkImagePanel_build GUI_PropertySkipMark_build)

add_custom_target(GUI_ButtonSelectMultiDelivery_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectMultiDelivery" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectMultiDelivery/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectMultiDelivery/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSelectMultiDelivery sequentially..."
)
add_dependencies(GUI_ButtonSelectMultiDelivery_build GUI_SkipMarkImagePanel_build)

add_custom_target(GUI_ShowResultMultiDelivery_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultMultiDelivery" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultMultiDelivery/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultMultiDelivery/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowResultMultiDelivery sequentially..."
)
add_dependencies(GUI_ShowResultMultiDelivery_build GUI_ButtonSelectMultiDelivery_build)

add_custom_target(ResultDLL_ResultXMLMultiDelivery_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLMultiDelivery" -B "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLMultiDelivery/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLMultiDelivery/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ResultDLL/ResultXMLMultiDelivery sequentially..."
)
add_dependencies(ResultDLL_ResultXMLMultiDelivery_build GUI_ShowResultMultiDelivery_build)

add_custom_target(GUI_ShowBlockList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowBlockList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowBlockList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowBlockList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowBlockList sequentially..."
)
add_dependencies(GUI_ShowBlockList_build ResultDLL_ResultXMLMultiDelivery_build)

add_custom_target(GUI_EulerRingL1ImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/EulerRingL1ImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/EulerRingL1ImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/EulerRingL1ImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/EulerRingL1ImagePanel sequentially..."
)
add_dependencies(GUI_EulerRingL1ImagePanel_build GUI_ShowBlockList_build)

add_custom_target(GUI_PropertyEulerRingL1_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyEulerRingL1" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyEulerRingL1/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyEulerRingL1/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyEulerRingL1 sequentially..."
)
add_dependencies(GUI_PropertyEulerRingL1_build GUI_EulerRingL1ImagePanel_build)

add_custom_target(Algorithm_EulerRingL1_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/EulerRingL1" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/EulerRingL1/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/EulerRingL1/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/EulerRingL1 sequentially..."
)
add_dependencies(Algorithm_EulerRingL1_build GUI_PropertyEulerRingL1_build)

add_custom_target(GUI_ButtonTransferPushGUI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferPushGUI" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferPushGUI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferPushGUI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonTransferPushGUI sequentially..."
)
add_dependencies(GUI_ButtonTransferPushGUI_build Algorithm_EulerRingL1_build)

add_custom_target(GUI_ButtonTransferRequireMasterData_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferRequireMasterData" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferRequireMasterData/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferRequireMasterData/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonTransferRequireMasterData sequentially..."
)
add_dependencies(GUI_ButtonTransferRequireMasterData_build GUI_ButtonTransferPushGUI_build)

add_custom_target(GUI_ButtonTransferSendMasterData_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferSendMasterData" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferSendMasterData/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferSendMasterData/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonTransferSendMasterData sequentially..."
)
add_dependencies(GUI_ButtonTransferSendMasterData_build GUI_ButtonTransferRequireMasterData_build)

add_custom_target(GUI_ButtonTransferRequireGlobalParam_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferRequireGlobalParam" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferRequireGlobalParam/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferRequireGlobalParam/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonTransferRequireGlobalParam sequentially..."
)
add_dependencies(GUI_ButtonTransferRequireGlobalParam_build GUI_ButtonTransferSendMasterData_build)

add_custom_target(GUI_ButtonTransferSendGlobalParam_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferSendGlobalParam" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferSendGlobalParam/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferSendGlobalParam/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonTransferSendGlobalParam sequentially..."
)
add_dependencies(GUI_ButtonTransferSendGlobalParam_build GUI_ButtonTransferRequireGlobalParam_build)

add_custom_target(GUI_ButtonTransferLoadGUI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferLoadGUI" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferLoadGUI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferLoadGUI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonTransferLoadGUI sequentially..."
)
add_dependencies(GUI_ButtonTransferLoadGUI_build GUI_ButtonTransferSendGlobalParam_build)

add_custom_target(ServiceLib_ProjectPropertyManager_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ProjectPropertyManager" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ProjectPropertyManager/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/ProjectPropertyManager/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/ProjectPropertyManager sequentially..."
)
add_dependencies(ServiceLib_ProjectPropertyManager_build GUI_ButtonTransferLoadGUI_build)

add_custom_target(GUI_PanelXYCalc_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelXYCalc" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelXYCalc/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelXYCalc/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PanelXYCalc sequentially..."
)
add_dependencies(GUI_PanelXYCalc_build ServiceLib_ProjectPropertyManager_build)

add_custom_target(PluginDLL_Camera_CameraSharer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraSharer" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraSharer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraSharer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraSharer sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraSharer_build GUI_PanelXYCalc_build)

add_custom_target(PluginDLL_Camera_CameraSharerDLL_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraSharerDLL" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraSharerDLL/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraSharerDLL/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraSharerDLL sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraSharerDLL_build PluginDLL_Camera_CameraSharer_build)

add_custom_target(Algorithm_FrameDef_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/FrameDef" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/FrameDef/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/FrameDef/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/FrameDef sequentially..."
)
add_dependencies(Algorithm_FrameDef_build PluginDLL_Camera_CameraSharerDLL_build)

add_custom_target(GUI_FrameDefImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/FrameDefImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/FrameDefImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/FrameDefImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/FrameDefImagePanel sequentially..."
)
add_dependencies(GUI_FrameDefImagePanel_build Algorithm_FrameDef_build)

add_custom_target(GUI_PropertyFrameDef_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyFrameDef" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyFrameDef/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyFrameDef/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyFrameDef sequentially..."
)
add_dependencies(GUI_PropertyFrameDef_build GUI_FrameDefImagePanel_build)

add_custom_target(GUI_SelectResultLotFrame_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SelectResultLotFrame" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SelectResultLotFrame/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SelectResultLotFrame/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SelectResultLotFrame sequentially..."
)
add_dependencies(GUI_SelectResultLotFrame_build GUI_PropertyFrameDef_build)

add_custom_target(GUI_ShowResultFrame_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultFrame" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultFrame/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultFrame/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowResultFrame sequentially..."
)
add_dependencies(GUI_ShowResultFrame_build GUI_SelectResultLotFrame_build)

add_custom_target(ResultDLL_ResultFrameDLL_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultFrameDLL" -B "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultFrameDLL/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultFrameDLL/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ResultDLL/ResultFrameDLL sequentially..."
)
add_dependencies(ResultDLL_ResultFrameDLL_build GUI_ShowResultFrame_build)

add_custom_target(GUI_ButtonSwapIn_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSwapIn" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSwapIn/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSwapIn/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSwapIn sequentially..."
)
add_dependencies(GUI_ButtonSwapIn_build ResultDLL_ResultFrameDLL_build)

add_custom_target(GUI_ButtonSwapOut_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSwapOut" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSwapOut/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSwapOut/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSwapOut sequentially..."
)
add_dependencies(GUI_ButtonSwapOut_build GUI_ButtonSwapIn_build)

add_custom_target(GUI_ButtonInitialize_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonInitialize" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonInitialize/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonInitialize/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonInitialize sequentially..."
)
add_dependencies(GUI_ButtonInitialize_build GUI_ButtonSwapOut_build)

add_custom_target(PluginDLL_PIO_NetworkSIOServer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkSIOServer" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkSIOServer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkSIOServer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/NetworkSIOServer sequentially..."
)
add_dependencies(PluginDLL_PIO_NetworkSIOServer_build GUI_ButtonInitialize_build)

add_custom_target(PluginDLL_PIO_NetworkSIOTestClient_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkSIOTestClient" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkSIOTestClient/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkSIOTestClient/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/NetworkSIOTestClient sequentially..."
)
add_dependencies(PluginDLL_PIO_NetworkSIOTestClient_build PluginDLL_PIO_NetworkSIOServer_build)

add_custom_target(GUI_OCRImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/OCRImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/OCRImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/OCRImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/OCRImagePanel sequentially..."
)
add_dependencies(GUI_OCRImagePanel_build PluginDLL_PIO_NetworkSIOTestClient_build)

add_custom_target(GUI_PropertyOCR_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyOCR" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyOCR/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyOCR/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyOCR sequentially..."
)
add_dependencies(GUI_PropertyOCR_build GUI_OCRImagePanel_build)

add_custom_target(GUI_ButtonLoadRelease_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadRelease" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadRelease/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadRelease/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLoadRelease sequentially..."
)
add_dependencies(GUI_ButtonLoadRelease_build GUI_PropertyOCR_build)

add_custom_target(Filter_FilterImageShadingArea_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShadingArea" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShadingArea/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShadingArea/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterImageShadingArea sequentially..."
)
add_dependencies(Filter_FilterImageShadingArea_build GUI_ButtonLoadRelease_build)

add_custom_target(GUI_PushToSavePix_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PushToSavePix" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PushToSavePix/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PushToSavePix/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PushToSavePix sequentially..."
)
add_dependencies(GUI_PushToSavePix_build Filter_FilterImageShadingArea_build)

add_custom_target(Algorithm_Process3D_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Process3D" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Process3D/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Process3D/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/Process3D sequentially..."
)
add_dependencies(Algorithm_Process3D_build GUI_PushToSavePix_build)

add_custom_target(GUI_Process3DImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Process3DImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Process3DImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Process3DImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/Process3DImagePanel sequentially..."
)
add_dependencies(GUI_Process3DImagePanel_build Algorithm_Process3D_build)

add_custom_target(GUI_PropertyProcess3D_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyProcess3D" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyProcess3D/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyProcess3D/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyProcess3D sequentially..."
)
add_dependencies(GUI_PropertyProcess3D_build GUI_Process3DImagePanel_build)

add_custom_target(GUI_ButtonModeAutoIncScanNumber_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonModeAutoIncScanNumber" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonModeAutoIncScanNumber/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonModeAutoIncScanNumber/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonModeAutoIncScanNumber sequentially..."
)
add_dependencies(GUI_ButtonModeAutoIncScanNumber_build GUI_PropertyProcess3D_build)

add_custom_target(GUI_ButtonOutlineOffsetWindow_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonOutlineOffsetWindow" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonOutlineOffsetWindow/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonOutlineOffsetWindow/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonOutlineOffsetWindow sequentially..."
)
add_dependencies(GUI_ButtonOutlineOffsetWindow_build GUI_ButtonModeAutoIncScanNumber_build)

add_custom_target(Filter_FilterRemoveNoiseLine_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterRemoveNoiseLine" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterRemoveNoiseLine/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterRemoveNoiseLine/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterRemoveNoiseLine sequentially..."
)
add_dependencies(Filter_FilterRemoveNoiseLine_build GUI_ButtonOutlineOffsetWindow_build)

add_custom_target(Algorithm_LinePatternInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinePatternInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinePatternInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinePatternInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/LinePatternInspection sequentially..."
)
add_dependencies(Algorithm_LinePatternInspection_build Filter_FilterRemoveNoiseLine_build)

add_custom_target(GUI_LinePatternImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LinePatternImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LinePatternImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LinePatternImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/LinePatternImagePanel sequentially..."
)
add_dependencies(GUI_LinePatternImagePanel_build Algorithm_LinePatternInspection_build)

add_custom_target(GUI_PropertyLinePattern_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyLinePattern" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyLinePattern/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyLinePattern/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyLinePattern sequentially..."
)
add_dependencies(GUI_PropertyLinePattern_build GUI_LinePatternImagePanel_build)

add_custom_target(Algorithm_AlignmentFlexArea_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentFlexArea" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentFlexArea/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentFlexArea/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/AlignmentFlexArea sequentially..."
)
add_dependencies(Algorithm_AlignmentFlexArea_build GUI_PropertyLinePattern_build)

add_custom_target(GUI_AlignmentFlexAreaImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentFlexAreaImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentFlexAreaImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentFlexAreaImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AlignmentFlexAreaImagePanel sequentially..."
)
add_dependencies(GUI_AlignmentFlexAreaImagePanel_build Algorithm_AlignmentFlexArea_build)

add_custom_target(GUI_PropertyAlignmentFlexArea_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentFlexArea" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentFlexArea/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentFlexArea/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyAlignmentFlexArea sequentially..."
)
add_dependencies(GUI_PropertyAlignmentFlexArea_build GUI_AlignmentFlexAreaImagePanel_build)

add_custom_target(Filter_FilterBrightnessLogConvert_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterBrightnessLogConvert" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterBrightnessLogConvert/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterBrightnessLogConvert/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterBrightnessLogConvert sequentially..."
)
add_dependencies(Filter_FilterBrightnessLogConvert_build GUI_PropertyAlignmentFlexArea_build)

add_custom_target(PluginDLL_Camera_CameraXtium_CLHS_PX8_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtium-CLHS_PX8" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtium-CLHS_PX8/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtium-CLHS_PX8/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraXtium-CLHS_PX8 sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraXtium_CLHS_PX8_build Filter_FilterBrightnessLogConvert_build)

add_custom_target(GUI_PanelInputInformation_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelInputInformation" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelInputInformation/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelInputInformation/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PanelInputInformation sequentially..."
)
add_dependencies(GUI_PanelInputInformation_build PluginDLL_Camera_CameraXtium_CLHS_PX8_build)

add_custom_target(GUI_ShortcutKeyInvisible_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShortcutKeyInvisible" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShortcutKeyInvisible/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShortcutKeyInvisible/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShortcutKeyInvisible sequentially..."
)
add_dependencies(GUI_ShortcutKeyInvisible_build GUI_PanelInputInformation_build)

add_custom_target(PluginDLL_PIO_PIOForCameraExecuter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/PIOForCameraExecuter" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/PIOForCameraExecuter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/PIOForCameraExecuter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/PIOForCameraExecuter sequentially..."
)
add_dependencies(PluginDLL_PIO_PIOForCameraExecuter_build GUI_ShortcutKeyInvisible_build)

add_custom_target(GUI_PanelXYZSize_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelXYZSize" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelXYZSize/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelXYZSize/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PanelXYZSize sequentially..."
)
add_dependencies(GUI_PanelXYZSize_build PluginDLL_PIO_PIOForCameraExecuter_build)

add_custom_target(GUI_PanelMaxStock_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelMaxStock" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelMaxStock/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelMaxStock/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PanelMaxStock sequentially..."
)
add_dependencies(GUI_PanelMaxStock_build GUI_PanelXYZSize_build)

add_custom_target(Filter_FilterVBandOneLayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVBandOneLayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVBandOneLayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterVBandOneLayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterVBandOneLayer sequentially..."
)
add_dependencies(Filter_FilterVBandOneLayer_build GUI_PanelMaxStock_build)

add_custom_target(GUI_ButtonAlignmentLargeTransform_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAlignmentLargeTransform" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAlignmentLargeTransform/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAlignmentLargeTransform/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonAlignmentLargeTransform sequentially..."
)
add_dependencies(GUI_ButtonAlignmentLargeTransform_build Filter_FilterVBandOneLayer_build)

add_custom_target(GUI_ShowAlignmentResult_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowAlignmentResult" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowAlignmentResult/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowAlignmentResult/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowAlignmentResult sequentially..."
)
add_dependencies(GUI_ShowAlignmentResult_build GUI_ButtonAlignmentLargeTransform_build)

add_custom_target(GUI_ButtonExecuteMacro_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExecuteMacro" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExecuteMacro/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExecuteMacro/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonExecuteMacro sequentially..."
)
add_dependencies(GUI_ButtonExecuteMacro_build GUI_ShowAlignmentResult_build)

add_custom_target(GUI_SetThresholdByHistogram_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetThresholdByHistogram" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetThresholdByHistogram/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetThresholdByHistogram/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SetThresholdByHistogram sequentially..."
)
add_dependencies(GUI_SetThresholdByHistogram_build GUI_ButtonExecuteMacro_build)

add_custom_target(ServiceLib_MakeShrinkingTable_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/MakeShrinkingTable" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/MakeShrinkingTable/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/MakeShrinkingTable/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/MakeShrinkingTable sequentially..."
)
add_dependencies(ServiceLib_MakeShrinkingTable_build GUI_SetThresholdByHistogram_build)

add_custom_target(GUI_ListGenerateChildLibrary_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListGenerateChildLibrary" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListGenerateChildLibrary/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListGenerateChildLibrary/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ListGenerateChildLibrary sequentially..."
)
add_dependencies(GUI_ListGenerateChildLibrary_build ServiceLib_MakeShrinkingTable_build)

add_custom_target(GUI_ButtonStartCaptureContinuousLy_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonStartCaptureContinuousLy" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonStartCaptureContinuousLy/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonStartCaptureContinuousLy/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonStartCaptureContinuousLy sequentially..."
)
add_dependencies(GUI_ButtonStartCaptureContinuousLy_build GUI_ListGenerateChildLibrary_build)

add_custom_target(GUI_RealtimeImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RealtimeImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RealtimeImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RealtimeImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/RealtimeImagePanel sequentially..."
)
add_dependencies(GUI_RealtimeImagePanel_build GUI_ButtonStartCaptureContinuousLy_build)

add_custom_target(PluginDLL_Light_LightDLL_CCSControlByLAN_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControlByLAN" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControlByLAN/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControlByLAN/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Light/LightDLL/CCSControlByLAN sequentially..."
)
add_dependencies(PluginDLL_Light_LightDLL_CCSControlByLAN_build GUI_RealtimeImagePanel_build)

add_custom_target(PluginDLL_Light_LightDLL_ImacControlByLAN_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/ImacControlByLAN" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/ImacControlByLAN/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/ImacControlByLAN/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Light/LightDLL/ImacControlByLAN sequentially..."
)
add_dependencies(PluginDLL_Light_LightDLL_ImacControlByLAN_build PluginDLL_Light_LightDLL_CCSControlByLAN_build)

add_custom_target(Algorithm_MatchShiftRotation_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MatchShiftRotation" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MatchShiftRotation/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MatchShiftRotation/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/MatchShiftRotation sequentially..."
)
add_dependencies(Algorithm_MatchShiftRotation_build PluginDLL_Light_LightDLL_ImacControlByLAN_build)

add_custom_target(GUI_MatchShiftRotationImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MatchShiftRotationImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MatchShiftRotationImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MatchShiftRotationImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/MatchShiftRotationImagePanel sequentially..."
)
add_dependencies(GUI_MatchShiftRotationImagePanel_build Algorithm_MatchShiftRotation_build)

add_custom_target(GUI_PropertyMatchShiftRotation_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMatchShiftRotation" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMatchShiftRotation/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMatchShiftRotation/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyMatchShiftRotation sequentially..."
)
add_dependencies(GUI_PropertyMatchShiftRotation_build GUI_MatchShiftRotationImagePanel_build)

add_custom_target(GUI_DrawHookControlPanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DrawHookControlPanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DrawHookControlPanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DrawHookControlPanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DrawHookControlPanel sequentially..."
)
add_dependencies(GUI_DrawHookControlPanel_build GUI_PropertyMatchShiftRotation_build)

add_custom_target(GUI_HookOverlapImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookOverlapImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookOverlapImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookOverlapImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/HookOverlapImage sequentially..."
)
add_dependencies(GUI_HookOverlapImage_build GUI_DrawHookControlPanel_build)

add_custom_target(GUI_HookMeasure_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookMeasure" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookMeasure/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookMeasure/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/HookMeasure sequentially..."
)
add_dependencies(GUI_HookMeasure_build GUI_HookOverlapImage_build)

add_custom_target(GUI_HookPeaking_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookPeaking" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookPeaking/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookPeaking/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/HookPeaking sequentially..."
)
add_dependencies(GUI_HookPeaking_build GUI_HookMeasure_build)

add_custom_target(GUI_GeneralStackForm_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralStackForm" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralStackForm/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/GeneralStackForm/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/GeneralStackForm sequentially..."
)
add_dependencies(GUI_GeneralStackForm_build GUI_HookPeaking_build)

add_custom_target(GUI_ButtonSaveBmpJpg_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveBmpJpg" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveBmpJpg/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveBmpJpg/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSaveBmpJpg sequentially..."
)
add_dependencies(GUI_ButtonSaveBmpJpg_build GUI_GeneralStackForm_build)

add_custom_target(PluginDLL_Camera_CameraXtumiPx8LineTrigger_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtumiPx8LineTrigger" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtumiPx8LineTrigger/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtumiPx8LineTrigger/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraXtumiPx8LineTrigger sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraXtumiPx8LineTrigger_build GUI_ButtonSaveBmpJpg_build)

add_custom_target(GUI_ChangeTurnTop_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeTurnTop" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeTurnTop/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeTurnTop/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ChangeTurnTop sequentially..."
)
add_dependencies(GUI_ChangeTurnTop_build PluginDLL_Camera_CameraXtumiPx8LineTrigger_build)

add_custom_target(Algorithm_NickInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/NickInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/NickInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/NickInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/NickInspection sequentially..."
)
add_dependencies(Algorithm_NickInspection_build GUI_ChangeTurnTop_build)

add_custom_target(GUI_NickInspectionImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/NickInspectionImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/NickInspectionImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/NickInspectionImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/NickInspectionImagePanel sequentially..."
)
add_dependencies(GUI_NickInspectionImagePanel_build Algorithm_NickInspection_build)

add_custom_target(GUI_PropertyNickInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyNickInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyNickInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyNickInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyNickInspection sequentially..."
)
add_dependencies(GUI_PropertyNickInspection_build GUI_NickInspectionImagePanel_build)

add_custom_target(PluginDLL_Camera_CameraXtumiPx8LineTrigger_DalsaLoadImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtumiPx8LineTrigger/DalsaLoadImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtumiPx8LineTrigger/DalsaLoadImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtumiPx8LineTrigger/DalsaLoadImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraXtumiPx8LineTrigger/DalsaLoadImage sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraXtumiPx8LineTrigger_DalsaLoadImage_build GUI_PropertyNickInspection_build)

add_custom_target(GUI_PanelHidable_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelHidable" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelHidable/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelHidable/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PanelHidable sequentially..."
)
add_dependencies(GUI_PanelHidable_build PluginDLL_Camera_CameraXtumiPx8LineTrigger_DalsaLoadImage_build)

add_custom_target(PluginDLL_PIO_NetworkPIOClient_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkPIOClient" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkPIOClient/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkPIOClient/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/NetworkPIOClient sequentially..."
)
add_dependencies(PluginDLL_PIO_NetworkPIOClient_build GUI_PanelHidable_build)

add_custom_target(GUI_DotColorMatchingImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DotColorMatchingImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DotColorMatchingImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DotColorMatchingImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DotColorMatchingImagePanel sequentially..."
)
add_dependencies(GUI_DotColorMatchingImagePanel_build PluginDLL_PIO_NetworkPIOClient_build)

add_custom_target(GUI_PropertyDotColorMatching_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDotColorMatching" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDotColorMatching/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDotColorMatching/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyDotColorMatching sequentially..."
)
add_dependencies(GUI_PropertyDotColorMatching_build GUI_DotColorMatchingImagePanel_build)

add_custom_target(Algorithm_DotColorMatching_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DotColorMatching" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DotColorMatching/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DotColorMatching/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/DotColorMatching sequentially..."
)
add_dependencies(Algorithm_DotColorMatching_build GUI_PropertyDotColorMatching_build)

add_custom_target(GUI_ShowMatchShiftRotation_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMatchShiftRotation" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMatchShiftRotation/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMatchShiftRotation/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowMatchShiftRotation sequentially..."
)
add_dependencies(GUI_ShowMatchShiftRotation_build Algorithm_DotColorMatching_build)

add_custom_target(GUI_ShowCurrentLightName_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCurrentLightName" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCurrentLightName/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCurrentLightName/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowCurrentLightName sequentially..."
)
add_dependencies(GUI_ShowCurrentLightName_build GUI_ShowMatchShiftRotation_build)

add_custom_target(Filter_FilterBrightnessThresholdConvert_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterBrightnessThresholdConvert" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterBrightnessThresholdConvert/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterBrightnessThresholdConvert/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterBrightnessThresholdConvert sequentially..."
)
add_dependencies(Filter_FilterBrightnessThresholdConvert_build GUI_ShowCurrentLightName_build)

add_custom_target(GUI_ExecutorOfPixList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExecutorOfPixList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExecutorOfPixList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ExecutorOfPixList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ExecutorOfPixList sequentially..."
)
add_dependencies(GUI_ExecutorOfPixList_build Filter_FilterBrightnessThresholdConvert_build)

add_custom_target(ResultDLL_ResultXMLPrintFast_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLPrintFast" -B "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLPrintFast/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultXMLPrintFast/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ResultDLL/ResultXMLPrintFast sequentially..."
)
add_dependencies(ResultDLL_ResultXMLPrintFast_build GUI_ExecutorOfPixList_build)

add_custom_target(Algorithm_SwitchPhase_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/SwitchPhase" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/SwitchPhase/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/SwitchPhase/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/SwitchPhase sequentially..."
)
add_dependencies(Algorithm_SwitchPhase_build ResultDLL_ResultXMLPrintFast_build)

add_custom_target(GUI_PropertySwitchPhase_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertySwitchPhase" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertySwitchPhase/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertySwitchPhase/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertySwitchPhase sequentially..."
)
add_dependencies(GUI_PropertySwitchPhase_build Algorithm_SwitchPhase_build)

add_custom_target(GUI_SwitchPhaseImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SwitchPhaseImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SwitchPhaseImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SwitchPhaseImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SwitchPhaseImagePanel sequentially..."
)
add_dependencies(GUI_SwitchPhaseImagePanel_build GUI_PropertySwitchPhase_build)

add_custom_target(GUI_ButtonToShowCrossLine_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToShowCrossLine" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToShowCrossLine/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToShowCrossLine/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonToShowCrossLine sequentially..."
)
add_dependencies(GUI_ButtonToShowCrossLine_build GUI_SwitchPhaseImagePanel_build)

add_custom_target(GUI_ShowCycleTime_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCycleTime" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCycleTime/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCycleTime/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowCycleTime sequentially..."
)
add_dependencies(GUI_ShowCycleTime_build GUI_ButtonToShowCrossLine_build)

add_custom_target(GUI_HookDrawRegulationLine_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookDrawRegulationLine" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookDrawRegulationLine/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookDrawRegulationLine/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/HookDrawRegulationLine sequentially..."
)
add_dependencies(GUI_HookDrawRegulationLine_build GUI_ShowCycleTime_build)

add_custom_target(GUI_ButtonLoadMasterDataInPhase_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMasterDataInPhase" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMasterDataInPhase/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadMasterDataInPhase/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLoadMasterDataInPhase sequentially..."
)
add_dependencies(GUI_ButtonLoadMasterDataInPhase_build GUI_HookDrawRegulationLine_build)

add_custom_target(GUI_CopyMirroredTransfer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CopyMirroredTransfer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CopyMirroredTransfer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CopyMirroredTransfer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CopyMirroredTransfer sequentially..."
)
add_dependencies(GUI_CopyMirroredTransfer_build GUI_ButtonLoadMasterDataInPhase_build)

add_custom_target(GUI_ShowImageList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowImageList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowImageList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowImageList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowImageList sequentially..."
)
add_dependencies(GUI_ShowImageList_build GUI_CopyMirroredTransfer_build)

add_custom_target(ResultDLL_ResultDLLIntoFile_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultDLLIntoFile" -B "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultDLLIntoFile/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultDLLIntoFile/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ResultDLL/ResultDLLIntoFile sequentially..."
)
add_dependencies(ResultDLL_ResultDLLIntoFile_build GUI_ShowImageList_build)

add_custom_target(GUI_HoleWallInspectionImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HoleWallInspectionImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HoleWallInspectionImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HoleWallInspectionImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/HoleWallInspectionImagePanel sequentially..."
)
add_dependencies(GUI_HoleWallInspectionImagePanel_build ResultDLL_ResultDLLIntoFile_build)

add_custom_target(GUI_PropertyHoleWallInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyHoleWallInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyHoleWallInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyHoleWallInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyHoleWallInspection sequentially..."
)
add_dependencies(GUI_PropertyHoleWallInspection_build GUI_HoleWallInspectionImagePanel_build)

add_custom_target(Algorithm_HoleWallInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/HoleWallInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/HoleWallInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/HoleWallInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/HoleWallInspection sequentially..."
)
add_dependencies(Algorithm_HoleWallInspection_build GUI_PropertyHoleWallInspection_build)

add_custom_target(GUI_ButtonGenerateFromGerber_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonGenerateFromGerber" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonGenerateFromGerber/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonGenerateFromGerber/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonGenerateFromGerber sequentially..."
)
add_dependencies(GUI_ButtonGenerateFromGerber_build Algorithm_HoleWallInspection_build)

add_custom_target(GUI_RecordMovie_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RecordMovie" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RecordMovie/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RecordMovie/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/RecordMovie sequentially..."
)
add_dependencies(GUI_RecordMovie_build GUI_ButtonGenerateFromGerber_build)

add_custom_target(GUI_ButtonToSnapImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToSnapImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToSnapImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToSnapImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonToSnapImage sequentially..."
)
add_dependencies(GUI_ButtonToSnapImage_build GUI_RecordMovie_build)

add_custom_target(GUI_ShowItemNameResultSeq_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowItemNameResultSeq" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowItemNameResultSeq/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowItemNameResultSeq/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowItemNameResultSeq sequentially..."
)
add_dependencies(GUI_ShowItemNameResultSeq_build GUI_ButtonToSnapImage_build)

add_custom_target(GUI_ButtonChange_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonChange" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonChange/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonChange/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonChange sequentially..."
)
add_dependencies(GUI_ButtonChange_build GUI_ShowItemNameResultSeq_build)

add_custom_target(GUI_ShowThinMetalResultList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowThinMetalResultList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowThinMetalResultList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowThinMetalResultList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowThinMetalResultList sequentially..."
)
add_dependencies(GUI_ShowThinMetalResultList_build GUI_ButtonChange_build)

add_custom_target(EditStatusComment_ShowStatusComment_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/EditStatusComment/ShowStatusComment" -B "${CMAKE_CURRENT_SOURCE_DIR}/EditStatusComment/ShowStatusComment/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/EditStatusComment/ShowStatusComment/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building EditStatusComment/ShowStatusComment sequentially..."
)
add_dependencies(EditStatusComment_ShowStatusComment_build GUI_ShowThinMetalResultList_build)

add_custom_target(GUI_ButtonToShowStatusComment_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToShowStatusComment" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToShowStatusComment/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonToShowStatusComment/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonToShowStatusComment sequentially..."
)
add_dependencies(GUI_ButtonToShowStatusComment_build EditStatusComment_ShowStatusComment_build)

add_custom_target(GUI_DentImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DentImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DentImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DentImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DentImagePanel sequentially..."
)
add_dependencies(GUI_DentImagePanel_build GUI_ButtonToShowStatusComment_build)

add_custom_target(GUI_PropertyDent_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDent" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDent/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDent/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyDent sequentially..."
)
add_dependencies(GUI_PropertyDent_build GUI_DentImagePanel_build)

add_custom_target(Algorithm_DentInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DentInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DentInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DentInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/DentInspection sequentially..."
)
add_dependencies(Algorithm_DentInspection_build GUI_PropertyDent_build)

add_custom_target(GUI_ButtonSelectStackedPage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectStackedPage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectStackedPage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSelectStackedPage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSelectStackedPage sequentially..."
)
add_dependencies(GUI_ButtonSelectStackedPage_build Algorithm_DentInspection_build)

add_custom_target(GUI_ShowMultiImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMultiImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMultiImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMultiImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowMultiImage sequentially..."
)
add_dependencies(GUI_ShowMultiImage_build GUI_ButtonSelectStackedPage_build)

add_custom_target(GUI_PanelHide_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelHide" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelHide/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelHide/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PanelHide sequentially..."
)
add_dependencies(GUI_PanelHide_build GUI_ShowMultiImage_build)

add_custom_target(ResultAnalizer_DustReducer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ResultAnalizer/DustReducer" -B "${CMAKE_CURRENT_SOURCE_DIR}/ResultAnalizer/DustReducer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ResultAnalizer/DustReducer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ResultAnalizer/DustReducer sequentially..."
)
add_dependencies(ResultAnalizer_DustReducer_build GUI_PanelHide_build)

add_custom_target(ServiceLib_CopyAndExecute_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/CopyAndExecute" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/CopyAndExecute/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/CopyAndExecute/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/CopyAndExecute sequentially..."
)
add_dependencies(ServiceLib_CopyAndExecute_build ResultAnalizer_DustReducer_build)

add_custom_target(ResultAnalizer_DustReducerAI_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ResultAnalizer/DustReducerAI" -B "${CMAKE_CURRENT_SOURCE_DIR}/ResultAnalizer/DustReducerAI/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ResultAnalizer/DustReducerAI/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ResultAnalizer/DustReducerAI sequentially..."
)
add_dependencies(ResultAnalizer_DustReducerAI_build ServiceLib_CopyAndExecute_build)

add_custom_target(GUI_ButtonClearMasterInfo_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonClearMasterInfo" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonClearMasterInfo/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonClearMasterInfo/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonClearMasterInfo sequentially..."
)
add_dependencies(GUI_ButtonClearMasterInfo_build ResultAnalizer_DustReducerAI_build)

add_custom_target(GUI_HookLearningRegistOkNg_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookLearningRegistOkNg" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookLearningRegistOkNg/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/HookLearningRegistOkNg/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/HookLearningRegistOkNg sequentially..."
)
add_dependencies(GUI_HookLearningRegistOkNg_build GUI_ButtonClearMasterInfo_build)

add_custom_target(InspectionPlayer_InspectionFastPlayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/InspectionPlayer/InspectionFastPlayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/InspectionPlayer/InspectionFastPlayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/InspectionPlayer/InspectionFastPlayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building InspectionPlayer/InspectionFastPlayer sequentially..."
)
add_dependencies(InspectionPlayer_InspectionFastPlayer_build GUI_HookLearningRegistOkNg_build)

add_custom_target(PluginDLL_PIO_NetworkPIOVirtual_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkPIOVirtual" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkPIOVirtual/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkPIOVirtual/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/NetworkPIOVirtual sequentially..."
)
add_dependencies(PluginDLL_PIO_NetworkPIOVirtual_build InspectionPlayer_InspectionFastPlayer_build)

add_custom_target(PluginDLL_PIO_NetworkPIOVirtualCommunicator_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkPIOVirtualCommunicator" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkPIOVirtualCommunicator/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/NetworkPIOVirtualCommunicator/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/NetworkPIOVirtualCommunicator sequentially..."
)
add_dependencies(PluginDLL_PIO_NetworkPIOVirtualCommunicator_build PluginDLL_PIO_NetworkPIOVirtual_build)

add_custom_target(GUI_VideoController_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/VideoController" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/VideoController/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/VideoController/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/VideoController sequentially..."
)
add_dependencies(GUI_VideoController_build PluginDLL_PIO_NetworkPIOVirtualCommunicator_build)

add_custom_target(GUI_PlayVideoWidget_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PlayVideoWidget" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PlayVideoWidget/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PlayVideoWidget/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PlayVideoWidget sequentially..."
)
add_dependencies(GUI_PlayVideoWidget_build GUI_VideoController_build)

add_custom_target(GUI_ButtonAutoGenerateMeasureLineMove_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAutoGenerateMeasureLineMove" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAutoGenerateMeasureLineMove/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAutoGenerateMeasureLineMove/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonAutoGenerateMeasureLineMove sequentially..."
)
add_dependencies(GUI_ButtonAutoGenerateMeasureLineMove_build GUI_PlayVideoWidget_build)

add_custom_target(GUI_PropertyDXFOperation_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDXFOperation" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDXFOperation/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyDXFOperation/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyDXFOperation sequentially..."
)
add_dependencies(GUI_PropertyDXFOperation_build GUI_ButtonAutoGenerateMeasureLineMove_build)

add_custom_target(GUI_DXFOperationImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DXFOperationImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DXFOperationImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DXFOperationImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DXFOperationImagePanel sequentially..."
)
add_dependencies(GUI_DXFOperationImagePanel_build GUI_PropertyDXFOperation_build)

add_custom_target(Algorithm_DXFOperation_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DXFOperation" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DXFOperation/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/DXFOperation/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/DXFOperation sequentially..."
)
add_dependencies(Algorithm_DXFOperation_build GUI_DXFOperationImagePanel_build)

add_custom_target(GUI_ShowFileListBrowser_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowFileListBrowser" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowFileListBrowser/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowFileListBrowser/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowFileListBrowser sequentially..."
)
add_dependencies(GUI_ShowFileListBrowser_build Algorithm_DXFOperation_build)

add_custom_target(GUI_ButtonExecuteCommand_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExecuteCommand" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExecuteCommand/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonExecuteCommand/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonExecuteCommand sequentially..."
)
add_dependencies(GUI_ButtonExecuteCommand_build GUI_ShowFileListBrowser_build)

add_custom_target(PluginDLL_PIO_RelayLCUS2_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/RelayLCUS2" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/RelayLCUS2/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/RelayLCUS2/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/RelayLCUS2 sequentially..."
)
add_dependencies(PluginDLL_PIO_RelayLCUS2_build GUI_ButtonExecuteCommand_build)

add_custom_target(GUI_ShowMemory_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMemory" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMemory/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMemory/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowMemory sequentially..."
)
add_dependencies(GUI_ShowMemory_build PluginDLL_PIO_RelayLCUS2_build)

add_custom_target(Data_management_Maintainer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Data management/Maintainer" -B "${CMAKE_CURRENT_SOURCE_DIR}/Data management/Maintainer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Data management/Maintainer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Data management/Maintainer sequentially..."
)
add_dependencies(Data_management_Maintainer_build GUI_ShowMemory_build)

add_custom_target(ResultDLL_ResultSaveTargetImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultSaveTargetImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultSaveTargetImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultSaveTargetImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ResultDLL/ResultSaveTargetImage sequentially..."
)
add_dependencies(ResultDLL_ResultSaveTargetImage_build Data_management_Maintainer_build)

add_custom_target(GUI_ButtonShowStockedImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowStockedImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowStockedImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowStockedImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonShowStockedImage sequentially..."
)
add_dependencies(GUI_ButtonShowStockedImage_build ResultDLL_ResultSaveTargetImage_build)

add_custom_target(PluginDLL_PIO_SharedPIO_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/SharedPIO" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/SharedPIO/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/SharedPIO/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/SharedPIO sequentially..."
)
add_dependencies(PluginDLL_PIO_SharedPIO_build GUI_ButtonShowStockedImage_build)

add_custom_target(GUI_ButtonShowSnapImageFileName_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowSnapImageFileName" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowSnapImageFileName/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowSnapImageFileName/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonShowSnapImageFileName sequentially..."
)
add_dependencies(GUI_ButtonShowSnapImageFileName_build PluginDLL_PIO_SharedPIO_build)

add_custom_target(GUI_ButtonResetThresholdDotColorMatching_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonResetThresholdDotColorMatching" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonResetThresholdDotColorMatching/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonResetThresholdDotColorMatching/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonResetThresholdDotColorMatching sequentially..."
)
add_dependencies(GUI_ButtonResetThresholdDotColorMatching_build GUI_ButtonShowSnapImageFileName_build)

add_custom_target(GUI_ShowCurrentTime_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCurrentTime" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCurrentTime/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowCurrentTime/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowCurrentTime sequentially..."
)
add_dependencies(GUI_ShowCurrentTime_build GUI_ButtonResetThresholdDotColorMatching_build)

add_custom_target(GUI_ButtonCopyAnyPhasePageLayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCopyAnyPhasePageLayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCopyAnyPhasePageLayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCopyAnyPhasePageLayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonCopyAnyPhasePageLayer sequentially..."
)
add_dependencies(GUI_ButtonCopyAnyPhasePageLayer_build GUI_ShowCurrentTime_build)

add_custom_target(Algorithm_ColorDifference_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ColorDifference" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ColorDifference/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ColorDifference/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/ColorDifference sequentially..."
)
add_dependencies(Algorithm_ColorDifference_build GUI_ButtonCopyAnyPhasePageLayer_build)

add_custom_target(GUI_ColorDifferenceImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ColorDifferenceImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ColorDifferenceImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ColorDifferenceImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ColorDifferenceImagePanel sequentially..."
)
add_dependencies(GUI_ColorDifferenceImagePanel_build Algorithm_ColorDifference_build)

add_custom_target(GUI_PropertyColorDifference_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyColorDifference" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyColorDifference/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyColorDifference/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyColorDifference sequentially..."
)
add_dependencies(GUI_PropertyColorDifference_build GUI_ColorDifferenceImagePanel_build)

add_custom_target(Algorithm_AlignmentProjection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentProjection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentProjection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentProjection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/AlignmentProjection sequentially..."
)
add_dependencies(Algorithm_AlignmentProjection_build GUI_PropertyColorDifference_build)

add_custom_target(GUI_AlignmentProjectionImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentProjectionImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentProjectionImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentProjectionImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AlignmentProjectionImagePanel sequentially..."
)
add_dependencies(GUI_AlignmentProjectionImagePanel_build Algorithm_AlignmentProjection_build)

add_custom_target(GUI_PropertyAlignmentProjection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentProjection" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentProjection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentProjection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyAlignmentProjection sequentially..."
)
add_dependencies(GUI_PropertyAlignmentProjection_build GUI_AlignmentProjectionImagePanel_build)

add_custom_target(GUI_SelectStackedWindows_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SelectStackedWindows" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SelectStackedWindows/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SelectStackedWindows/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SelectStackedWindows sequentially..."
)
add_dependencies(GUI_SelectStackedWindows_build GUI_PropertyAlignmentProjection_build)

add_custom_target(GUI_InsertTelop_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/InsertTelop" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/InsertTelop/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/InsertTelop/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/InsertTelop sequentially..."
)
add_dependencies(GUI_InsertTelop_build GUI_SelectStackedWindows_build)

add_custom_target(GUI_ImageBank_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImageBank" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImageBank/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ImageBank/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ImageBank sequentially..."
)
add_dependencies(GUI_ImageBank_build GUI_InsertTelop_build)

add_custom_target(Integrator_GUI_IntegrationResultList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationResultList" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationResultList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationResultList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationResultList sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationResultList_build GUI_ImageBank_build)

add_custom_target(Integrator_IntegrationPlayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/IntegrationPlayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/IntegrationPlayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/IntegrationPlayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/IntegrationPlayer sequentially..."
)
add_dependencies(Integrator_IntegrationPlayer_build Integrator_GUI_IntegrationResultList_build)

add_custom_target(Integrator_EditParamIntegrationMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/EditParamIntegrationMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/EditParamIntegrationMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/EditParamIntegrationMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/EditParamIntegrationMaster sequentially..."
)
add_dependencies(Integrator_EditParamIntegrationMaster_build Integrator_IntegrationPlayer_build)

add_custom_target(Integrator_GUI_IntegrationInputLot_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationInputLot" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationInputLot/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationInputLot/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationInputLot sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationInputLot_build Integrator_EditParamIntegrationMaster_build)

add_custom_target(Integrator_GUI_IntegrationLoadMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationLoadMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationLoadMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationLoadMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationLoadMaster sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationLoadMaster_build Integrator_GUI_IntegrationInputLot_build)

add_custom_target(Integrator_GUI_IntegrationSaveMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationSaveMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationSaveMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationSaveMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationSaveMaster sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationSaveMaster_build Integrator_GUI_IntegrationLoadMaster_build)

add_custom_target(Integrator_GUI_IntegrationHistory_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationHistory" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationHistory/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationHistory/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationHistory sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationHistory_build Integrator_GUI_IntegrationSaveMaster_build)

add_custom_target(Integrator_GUI_IntegrationShowOKNG_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowOKNG" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowOKNG/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowOKNG/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationShowOKNG sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationShowOKNG_build Integrator_GUI_IntegrationHistory_build)

add_custom_target(Integrator_GUI_IntegrationShowTotal_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowTotal" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowTotal/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowTotal/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationShowTotal sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationShowTotal_build Integrator_GUI_IntegrationShowOKNG_build)

add_custom_target(Integrator_GUI_IntegrationThumbnail_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationThumbnail" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationThumbnail/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationThumbnail/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationThumbnail sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationThumbnail_build Integrator_GUI_IntegrationShowTotal_build)

add_custom_target(Integrator_GUI_IntegrationShowSavedImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowSavedImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowSavedImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowSavedImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationShowSavedImage sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationShowSavedImage_build Integrator_GUI_IntegrationThumbnail_build)

add_custom_target(Integrator_GUI_IntegrationShowHistoryLoadImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowHistoryLoadImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowHistoryLoadImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowHistoryLoadImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationShowHistoryLoadImage sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationShowHistoryLoadImage_build Integrator_GUI_IntegrationShowSavedImage_build)

add_custom_target(Integrator_GUI_IntegrationSelectLot_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationSelectLot" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationSelectLot/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationSelectLot/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationSelectLot sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationSelectLot_build Integrator_GUI_IntegrationShowHistoryLoadImage_build)

add_custom_target(Integrator_GUI_IntegrationSelectMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationSelectMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationSelectMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationSelectMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationSelectMaster sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationSelectMaster_build Integrator_GUI_IntegrationSelectLot_build)

add_custom_target(Integrator_GUI_IntegrationShowRelationInfo_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowRelationInfo" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowRelationInfo/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowRelationInfo/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationShowRelationInfo sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationShowRelationInfo_build Integrator_GUI_IntegrationSelectMaster_build)

add_custom_target(Integrator_GUI_IntegrationShowNGArrow_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowNGArrow" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowNGArrow/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowNGArrow/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationShowNGArrow sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationShowNGArrow_build Integrator_GUI_IntegrationShowRelationInfo_build)

add_custom_target(Integrator_GUI_IntegrationDisplayMasterImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationDisplayMasterImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationDisplayMasterImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationDisplayMasterImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationDisplayMasterImage sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationDisplayMasterImage_build Integrator_GUI_IntegrationShowNGArrow_build)

add_custom_target(Integrator_GUI_OperateThroughNet_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/OperateThroughNet" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/OperateThroughNet/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/OperateThroughNet/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/OperateThroughNet sequentially..."
)
add_dependencies(Integrator_GUI_OperateThroughNet_build Integrator_GUI_IntegrationDisplayMasterImage_build)

add_custom_target(Integrator_GUI_IntegrationShowConnectionState_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowConnectionState" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowConnectionState/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowConnectionState/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationShowConnectionState sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationShowConnectionState_build Integrator_GUI_OperateThroughNet_build)

add_custom_target(Integrator_GUI_IntegrationUpdateHistoryList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationUpdateHistoryList" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationUpdateHistoryList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationUpdateHistoryList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationUpdateHistoryList sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationUpdateHistoryList_build Integrator_GUI_IntegrationShowConnectionState_build)

add_custom_target(Integrator_GUI_IntegrationShowName_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowName" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowName/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowName/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationShowName sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationShowName_build Integrator_GUI_IntegrationUpdateHistoryList_build)

add_custom_target(Integrator_GUI_IntegrationStackNGThumbnail_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationStackNGThumbnail" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationStackNGThumbnail/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationStackNGThumbnail/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationStackNGThumbnail sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationStackNGThumbnail_build Integrator_GUI_IntegrationShowName_build)

add_custom_target(Integrator_GUI_SignalResultDoneToMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/SignalResultDoneToMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/SignalResultDoneToMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/SignalResultDoneToMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/SignalResultDoneToMaster sequentially..."
)
add_dependencies(Integrator_GUI_SignalResultDoneToMaster_build Integrator_GUI_IntegrationStackNGThumbnail_build)

add_custom_target(Integrator_GUI_IntegrationNewMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationNewMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationNewMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationNewMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationNewMaster sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationNewMaster_build Integrator_GUI_SignalResultDoneToMaster_build)

add_custom_target(Integrator_GUI_IntegrationClose_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationClose" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationClose/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationClose/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationClose sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationClose_build Integrator_GUI_IntegrationNewMaster_build)

add_custom_target(Integrator_GUI_IntegrationChangePhase_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationChangePhase" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationChangePhase/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationChangePhase/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationChangePhase sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationChangePhase_build Integrator_GUI_IntegrationClose_build)

add_custom_target(Integrator_GUI_IntegrationCopyImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCopyImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCopyImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCopyImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationCopyImage sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationCopyImage_build Integrator_GUI_IntegrationChangePhase_build)

add_custom_target(Integrator_GUI_IntegrationShowNGMap_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowNGMap" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowNGMap/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowNGMap/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationShowNGMap sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationShowNGMap_build Integrator_GUI_IntegrationCopyImage_build)

add_custom_target(Integrator_GUI_IntegrationShowRunningTrend_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowRunningTrend" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowRunningTrend/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowRunningTrend/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationShowRunningTrend sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationShowRunningTrend_build Integrator_GUI_IntegrationShowNGMap_build)

add_custom_target(Integrator_GUI_IntegrationShowMemory_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowMemory" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowMemory/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowMemory/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationShowMemory sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationShowMemory_build Integrator_GUI_IntegrationShowRunningTrend_build)

add_custom_target(Integrator_GUI_IntegrationClearNGThumbnail_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationClearNGThumbnail" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationClearNGThumbnail/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationClearNGThumbnail/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationClearNGThumbnail sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationClearNGThumbnail_build Integrator_GUI_IntegrationShowMemory_build)

add_custom_target(GUI_ShowSwitchPhaseResultList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowSwitchPhaseResultList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowSwitchPhaseResultList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowSwitchPhaseResultList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowSwitchPhaseResultList sequentially..."
)
add_dependencies(GUI_ShowSwitchPhaseResultList_build Integrator_GUI_IntegrationClearNGThumbnail_build)

add_custom_target(GUI_StartCaptureOnlyTarget_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartCaptureOnlyTarget" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartCaptureOnlyTarget/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartCaptureOnlyTarget/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/StartCaptureOnlyTarget sequentially..."
)
add_dependencies(GUI_StartCaptureOnlyTarget_build GUI_ShowSwitchPhaseResultList_build)

add_custom_target(GUI_StartScanningAgain_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartScanningAgain" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartScanningAgain/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/StartScanningAgain/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/StartScanningAgain sequentially..."
)
add_dependencies(GUI_StartScanningAgain_build GUI_StartCaptureOnlyTarget_build)

add_custom_target(GUI_ButtonShowResultAnalizer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowResultAnalizer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowResultAnalizer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowResultAnalizer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonShowResultAnalizer sequentially..."
)
add_dependencies(GUI_ButtonShowResultAnalizer_build GUI_StartScanningAgain_build)

add_custom_target(GUI_ShowTrialInformation_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowTrialInformation" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowTrialInformation/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowTrialInformation/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowTrialInformation sequentially..."
)
add_dependencies(GUI_ShowTrialInformation_build GUI_ButtonShowResultAnalizer_build)

add_custom_target(ServiceLib_StartCloseOnce_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/StartCloseOnce" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/StartCloseOnce/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/StartCloseOnce/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/StartCloseOnce sequentially..."
)
add_dependencies(ServiceLib_StartCloseOnce_build GUI_ShowTrialInformation_build)

add_custom_target(GUI_ShiftImsgeInLayerPage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShiftImsgeInLayerPage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShiftImsgeInLayerPage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShiftImsgeInLayerPage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShiftImsgeInLayerPage sequentially..."
)
add_dependencies(GUI_ShiftImsgeInLayerPage_build ServiceLib_StartCloseOnce_build)

add_custom_target(GUI_ButtonSwitchPhaseSynchronize_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSwitchPhaseSynchronize" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSwitchPhaseSynchronize/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSwitchPhaseSynchronize/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSwitchPhaseSynchronize sequentially..."
)
add_dependencies(GUI_ButtonSwitchPhaseSynchronize_build GUI_ShiftImsgeInLayerPage_build)

add_custom_target(GUI_ButtonTransferRequireImageData_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferRequireImageData" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferRequireImageData/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferRequireImageData/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonTransferRequireImageData sequentially..."
)
add_dependencies(GUI_ButtonTransferRequireImageData_build GUI_ButtonSwitchPhaseSynchronize_build)

add_custom_target(XmlServer_XMLServerV3_XMLServerV3_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/XmlServer/XMLServerV3/XMLServerV3" -B "${CMAKE_CURRENT_SOURCE_DIR}/XmlServer/XMLServerV3/XMLServerV3/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/XmlServer/XMLServerV3/XMLServerV3/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building XmlServer/XMLServerV3/XMLServerV3 sequentially..."
)
add_dependencies(XmlServer_XMLServerV3_XMLServerV3_build GUI_ButtonTransferRequireImageData_build)

add_custom_target(GUI_LoadImageInAnyPageLayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageInAnyPageLayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageInAnyPageLayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LoadImageInAnyPageLayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/LoadImageInAnyPageLayer sequentially..."
)
add_dependencies(GUI_LoadImageInAnyPageLayer_build XmlServer_XMLServerV3_XMLServerV3_build)

add_custom_target(GUI_Splitter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Splitter" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Splitter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/Splitter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/Splitter sequentially..."
)
add_dependencies(GUI_Splitter_build GUI_LoadImageInAnyPageLayer_build)

add_custom_target(GUI_PanelResolutionSize_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelResolutionSize" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelResolutionSize/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PanelResolutionSize/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PanelResolutionSize sequentially..."
)
add_dependencies(GUI_PanelResolutionSize_build GUI_Splitter_build)

add_custom_target(GUI_ButtonTransferSendImageData_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferSendImageData" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferSendImageData/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonTransferSendImageData/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonTransferSendImageData sequentially..."
)
add_dependencies(GUI_ButtonTransferSendImageData_build GUI_PanelResolutionSize_build)

add_custom_target(Algorithm_MakeAverageImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MakeAverageImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MakeAverageImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MakeAverageImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/MakeAverageImage sequentially..."
)
add_dependencies(Algorithm_MakeAverageImage_build GUI_ButtonTransferSendImageData_build)

add_custom_target(GUI_MakeAverageImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MakeAverageImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MakeAverageImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MakeAverageImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/MakeAverageImagePanel sequentially..."
)
add_dependencies(GUI_MakeAverageImagePanel_build Algorithm_MakeAverageImage_build)

add_custom_target(GUI_PropertyMakeAverageImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMakeAverageImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMakeAverageImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMakeAverageImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyMakeAverageImage sequentially..."
)
add_dependencies(GUI_PropertyMakeAverageImage_build GUI_MakeAverageImagePanel_build)

add_custom_target(GUI_ButtonAutoScanningMode_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAutoScanningMode" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAutoScanningMode/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAutoScanningMode/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonAutoScanningMode sequentially..."
)
add_dependencies(GUI_ButtonAutoScanningMode_build GUI_PropertyMakeAverageImage_build)

add_custom_target(GUI_ShowThresholdLevel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowThresholdLevel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowThresholdLevel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowThresholdLevel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowThresholdLevel sequentially..."
)
add_dependencies(GUI_ShowThresholdLevel_build GUI_ButtonAutoScanningMode_build)

add_custom_target(Integrator_GUI_IntegrationShowThresholdLevel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowThresholdLevel" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowThresholdLevel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationShowThresholdLevel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationShowThresholdLevel sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationShowThresholdLevel_build GUI_ShowThresholdLevel_build)

add_custom_target(Algorithm_Counter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Counter" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Counter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Counter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/Counter sequentially..."
)
add_dependencies(Algorithm_Counter_build Integrator_GUI_IntegrationShowThresholdLevel_build)

add_custom_target(GUI_CounterImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CounterImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CounterImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CounterImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CounterImagePanel sequentially..."
)
add_dependencies(GUI_CounterImagePanel_build Algorithm_Counter_build)

add_custom_target(GUI_PropertyCounter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyCounter" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyCounter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyCounter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyCounter sequentially..."
)
add_dependencies(GUI_PropertyCounter_build GUI_CounterImagePanel_build)

add_custom_target(Integrator_GUI_IntegrationChangeCameraSetting_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationChangeCameraSetting" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationChangeCameraSetting/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationChangeCameraSetting/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationChangeCameraSetting sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationChangeCameraSetting_build GUI_PropertyCounter_build)

add_custom_target(GUI_ButtonSaveScreenCapture_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveScreenCapture" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveScreenCapture/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveScreenCapture/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSaveScreenCapture sequentially..."
)
add_dependencies(GUI_ButtonSaveScreenCapture_build Integrator_GUI_IntegrationChangeCameraSetting_build)

add_custom_target(GUI_ShowBindNGNamingList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowBindNGNamingList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowBindNGNamingList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowBindNGNamingList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowBindNGNamingList sequentially..."
)
add_dependencies(GUI_ShowBindNGNamingList_build GUI_ButtonSaveScreenCapture_build)

add_custom_target(Algorithm_SavePartialImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/SavePartialImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/SavePartialImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/SavePartialImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/SavePartialImage sequentially..."
)
add_dependencies(Algorithm_SavePartialImage_build GUI_ShowBindNGNamingList_build)

add_custom_target(GUI_SavePartialImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SavePartialImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SavePartialImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SavePartialImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SavePartialImagePanel sequentially..."
)
add_dependencies(GUI_SavePartialImagePanel_build Algorithm_SavePartialImage_build)

add_custom_target(PluginDLL_Camera_CameraXtiumPx8MonoLineTrigger_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumPx8MonoLineTrigger" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumPx8MonoLineTrigger/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumPx8MonoLineTrigger/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraXtiumPx8MonoLineTrigger sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraXtiumPx8MonoLineTrigger_build GUI_SavePartialImagePanel_build)

add_custom_target(GUI_ButtonShadowToShow_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShadowToShow" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShadowToShow/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShadowToShow/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonShadowToShow sequentially..."
)
add_dependencies(GUI_ButtonShadowToShow_build PluginDLL_Camera_CameraXtiumPx8MonoLineTrigger_build)

add_custom_target(ShadowTree_ShrinkedInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ShadowTree/ShrinkedInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/ShadowTree/ShrinkedInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ShadowTree/ShrinkedInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ShadowTree/ShrinkedInspection sequentially..."
)
add_dependencies(ShadowTree_ShrinkedInspection_build GUI_ButtonShadowToShow_build)

add_custom_target(ResultAnalizer_ResultCategorizer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ResultAnalizer/ResultCategorizer" -B "${CMAKE_CURRENT_SOURCE_DIR}/ResultAnalizer/ResultCategorizer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ResultAnalizer/ResultCategorizer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ResultAnalizer/ResultCategorizer sequentially..."
)
add_dependencies(ResultAnalizer_ResultCategorizer_build ShadowTree_ShrinkedInspection_build)

add_custom_target(GUI_DisplayNGListCategorized_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayNGListCategorized" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayNGListCategorized/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayNGListCategorized/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayNGListCategorized sequentially..."
)
add_dependencies(GUI_DisplayNGListCategorized_build ResultAnalizer_ResultCategorizer_build)

add_custom_target(Algorithm_Raster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Raster" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Raster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Raster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/Raster sequentially..."
)
add_dependencies(Algorithm_Raster_build GUI_DisplayNGListCategorized_build)

add_custom_target(GUI_PropertyRaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyRaster sequentially..."
)
add_dependencies(GUI_PropertyRaster_build Algorithm_Raster_build)

add_custom_target(GUI_RasterImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RasterImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RasterImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RasterImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/RasterImagePanel sequentially..."
)
add_dependencies(GUI_RasterImagePanel_build GUI_PropertyRaster_build)

add_custom_target(ShadowTree_ShrinkLowHigh_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ShadowTree/ShrinkLowHigh" -B "${CMAKE_CURRENT_SOURCE_DIR}/ShadowTree/ShrinkLowHigh/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ShadowTree/ShrinkLowHigh/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ShadowTree/ShrinkLowHigh sequentially..."
)
add_dependencies(ShadowTree_ShrinkLowHigh_build GUI_RasterImagePanel_build)

add_custom_target(Integrator_GUI_IntegrationNGCategorizedList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationNGCategorizedList" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationNGCategorizedList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationNGCategorizedList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationNGCategorizedList sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationNGCategorizedList_build ShadowTree_ShrinkLowHigh_build)

add_custom_target(ChangeServer_CheckPort_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ChangeServer/CheckPort" -B "${CMAKE_CURRENT_SOURCE_DIR}/ChangeServer/CheckPort/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ChangeServer/CheckPort/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ChangeServer/CheckPort sequentially..."
)
add_dependencies(ChangeServer_CheckPort_build Integrator_GUI_IntegrationNGCategorizedList_build)

add_custom_target(Integrator_GUI_IntegrationImageBank_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationImageBank" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationImageBank/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationImageBank/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationImageBank sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationImageBank_build ChangeServer_CheckPort_build)

add_custom_target(GUI_ButtonCreateThresholdLevel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCreateThresholdLevel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCreateThresholdLevel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCreateThresholdLevel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonCreateThresholdLevel sequentially..."
)
add_dependencies(GUI_ButtonCreateThresholdLevel_build Integrator_GUI_IntegrationImageBank_build)

add_custom_target(Integrator_GUI_IntegrationCreateThreshold_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCreateThreshold" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCreateThreshold/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCreateThreshold/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationCreateThreshold sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationCreateThreshold_build GUI_ButtonCreateThresholdLevel_build)

add_custom_target(GUI_CameraChangeQuickProperty_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CameraChangeQuickProperty" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CameraChangeQuickProperty/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CameraChangeQuickProperty/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CameraChangeQuickProperty sequentially..."
)
add_dependencies(GUI_CameraChangeQuickProperty_build Integrator_GUI_IntegrationCreateThreshold_build)

add_custom_target(Integrator_GUI_IntegrationCameraChangeQuickProperty_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCameraChangeQuickProperty" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCameraChangeQuickProperty/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCameraChangeQuickProperty/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationCameraChangeQuickProperty sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationCameraChangeQuickProperty_build GUI_CameraChangeQuickProperty_build)

add_custom_target(GUI_MakeShading_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MakeShading" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MakeShading/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MakeShading/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/MakeShading sequentially..."
)
add_dependencies(GUI_MakeShading_build Integrator_GUI_IntegrationCameraChangeQuickProperty_build)

add_custom_target(Filter_FilterLineShading_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterLineShading" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterLineShading/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterLineShading/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterLineShading sequentially..."
)
add_dependencies(Filter_FilterLineShading_build GUI_MakeShading_build)

add_custom_target(GUI_CopyByControlPoints_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CopyByControlPoints" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CopyByControlPoints/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CopyByControlPoints/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CopyByControlPoints sequentially..."
)
add_dependencies(GUI_CopyByControlPoints_build Filter_FilterLineShading_build)

add_custom_target(GUI_ButtonSettingControlPointsForPages_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSettingControlPointsForPages" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSettingControlPointsForPages/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSettingControlPointsForPages/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSettingControlPointsForPages sequentially..."
)
add_dependencies(GUI_ButtonSettingControlPointsForPages_build GUI_CopyByControlPoints_build)

add_custom_target(GUI_ButtonFilterSwitch_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonFilterSwitch" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonFilterSwitch/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonFilterSwitch/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonFilterSwitch sequentially..."
)
add_dependencies(GUI_ButtonFilterSwitch_build GUI_ButtonSettingControlPointsForPages_build)

add_custom_target(GUI_ButtonLoadFilterConfig_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadFilterConfig" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadFilterConfig/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonLoadFilterConfig/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonLoadFilterConfig sequentially..."
)
add_dependencies(GUI_ButtonLoadFilterConfig_build GUI_ButtonFilterSwitch_build)

add_custom_target(Filter_FilterImageShadingDynamic_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShadingDynamic" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShadingDynamic/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterImageShadingDynamic/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterImageShadingDynamic sequentially..."
)
add_dependencies(Filter_FilterImageShadingDynamic_build GUI_ButtonLoadFilterConfig_build)

add_custom_target(Algorithm_Palletize_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Palletize" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Palletize/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Palletize/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/Palletize sequentially..."
)
add_dependencies(Algorithm_Palletize_build Filter_FilterImageShadingDynamic_build)

add_custom_target(GUI_PalletizeImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PalletizeImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PalletizeImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PalletizeImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PalletizeImagePanel sequentially..."
)
add_dependencies(GUI_PalletizeImagePanel_build Algorithm_Palletize_build)

add_custom_target(GUI_PropertyPalletize_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPalletize" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPalletize/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyPalletize/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyPalletize sequentially..."
)
add_dependencies(GUI_PropertyPalletize_build GUI_PalletizeImagePanel_build)

add_custom_target(GUI_DisplayProductivity_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayProductivity" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayProductivity/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayProductivity/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayProductivity sequentially..."
)
add_dependencies(GUI_DisplayProductivity_build GUI_PropertyPalletize_build)

add_custom_target(GUI_ButtonSaveGUILanguage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveGUILanguage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveGUILanguage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveGUILanguage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSaveGUILanguage sequentially..."
)
add_dependencies(GUI_ButtonSaveGUILanguage_build GUI_DisplayProductivity_build)

add_custom_target(Algorithm_MultiSpectral_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MultiSpectral" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MultiSpectral/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/MultiSpectral/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/MultiSpectral sequentially..."
)
add_dependencies(Algorithm_MultiSpectral_build GUI_ButtonSaveGUILanguage_build)

add_custom_target(GUI_MultiSpectralImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MultiSpectralImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MultiSpectralImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/MultiSpectralImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/MultiSpectralImagePanel sequentially..."
)
add_dependencies(GUI_MultiSpectralImagePanel_build Algorithm_MultiSpectral_build)

add_custom_target(GUI_PropertyMultiSpectral_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMultiSpectral" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMultiSpectral/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyMultiSpectral/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyMultiSpectral sequentially..."
)
add_dependencies(GUI_PropertyMultiSpectral_build GUI_MultiSpectralImagePanel_build)

add_custom_target(GUI_ShowSelectLayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowSelectLayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowSelectLayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowSelectLayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowSelectLayer sequentially..."
)
add_dependencies(GUI_ShowSelectLayer_build GUI_PropertyMultiSpectral_build)

add_custom_target(PluginDLL_Camera_CameraXtiumSpectral_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumSpectral" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumSpectral/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumSpectral/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraXtiumSpectral sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraXtiumSpectral_build GUI_ShowSelectLayer_build)

add_custom_target(GUI_ButtonResetCamera_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonResetCamera" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonResetCamera/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonResetCamera/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonResetCamera sequentially..."
)
add_dependencies(GUI_ButtonResetCamera_build PluginDLL_Camera_CameraXtiumSpectral_build)

add_custom_target(Algorithm_RasterInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/RasterInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/RasterInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/RasterInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/RasterInspection sequentially..."
)
add_dependencies(Algorithm_RasterInspection_build GUI_ButtonResetCamera_build)

add_custom_target(GUI_PropertyRasterInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRasterInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRasterInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRasterInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyRasterInspection sequentially..."
)
add_dependencies(GUI_PropertyRasterInspection_build Algorithm_RasterInspection_build)

add_custom_target(GUI_RasterInspectionImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RasterInspectionImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RasterInspectionImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RasterInspectionImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/RasterInspectionImagePanel sequentially..."
)
add_dependencies(GUI_RasterInspectionImagePanel_build GUI_PropertyRasterInspection_build)

add_custom_target(Algorithm_RepeatControl_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/RepeatControl" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/RepeatControl/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/RepeatControl/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/RepeatControl sequentially..."
)
add_dependencies(Algorithm_RepeatControl_build GUI_RasterInspectionImagePanel_build)

add_custom_target(GUI_PropertyRepeatControl_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRepeatControl" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRepeatControl/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRepeatControl/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyRepeatControl sequentially..."
)
add_dependencies(GUI_PropertyRepeatControl_build Algorithm_RepeatControl_build)

add_custom_target(GUI_RepeatControlImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RepeatControlImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RepeatControlImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RepeatControlImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/RepeatControlImagePanel sequentially..."
)
add_dependencies(GUI_RepeatControlImagePanel_build GUI_PropertyRepeatControl_build)

add_custom_target(Integrator_GUI_IntegrationButtonCreateRepeatControl_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonCreateRepeatControl" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonCreateRepeatControl/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonCreateRepeatControl/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationButtonCreateRepeatControl sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationButtonCreateRepeatControl_build GUI_RepeatControlImagePanel_build)

add_custom_target(Integrator_GUI_IntegrationCalibrateCamera_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCalibrateCamera" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCalibrateCamera/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCalibrateCamera/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationCalibrateCamera sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationCalibrateCamera_build Integrator_GUI_IntegrationButtonCreateRepeatControl_build)

add_custom_target(GUI_ButtonCalibrateCamera_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCalibrateCamera" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCalibrateCamera/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonCalibrateCamera/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonCalibrateCamera sequentially..."
)
add_dependencies(GUI_ButtonCalibrateCamera_build Integrator_GUI_IntegrationCalibrateCamera_build)

add_custom_target(GUI_ButtonShiftImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShiftImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShiftImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShiftImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonShiftImage sequentially..."
)
add_dependencies(GUI_ButtonShiftImage_build GUI_ButtonCalibrateCamera_build)

add_custom_target(Integrator_GUI_IntegrationStopUpdateThumbnail_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationStopUpdateThumbnail" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationStopUpdateThumbnail/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationStopUpdateThumbnail/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationStopUpdateThumbnail sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationStopUpdateThumbnail_build GUI_ButtonShiftImage_build)

add_custom_target(Integrator_GUI_IntegrationCameraAdjustment_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCameraAdjustment" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCameraAdjustment/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationCameraAdjustment/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationCameraAdjustment sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationCameraAdjustment_build Integrator_GUI_IntegrationStopUpdateThumbnail_build)

add_custom_target(Filter_FilterShiftVBand_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShiftVBand" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShiftVBand/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShiftVBand/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterShiftVBand sequentially..."
)
add_dependencies(Filter_FilterShiftVBand_build Integrator_GUI_IntegrationCameraAdjustment_build)

add_custom_target(GUI_ShowMeasureHolePosResultList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMeasureHolePosResultList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMeasureHolePosResultList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowMeasureHolePosResultList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowMeasureHolePosResultList sequentially..."
)
add_dependencies(GUI_ShowMeasureHolePosResultList_build Filter_FilterShiftVBand_build)

add_custom_target(GUI_ShowResultDetail_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultDetail" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultDetail/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultDetail/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowResultDetail sequentially..."
)
add_dependencies(GUI_ShowResultDetail_build GUI_ShowMeasureHolePosResultList_build)

add_custom_target(GUI_LearningCommandPanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LearningCommandPanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LearningCommandPanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/LearningCommandPanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/LearningCommandPanel sequentially..."
)
add_dependencies(GUI_LearningCommandPanel_build GUI_ShowResultDetail_build)

add_custom_target(Filter_FilterConvertResolution_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterConvertResolution" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterConvertResolution/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterConvertResolution/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterConvertResolution sequentially..."
)
add_dependencies(Filter_FilterConvertResolution_build GUI_LearningCommandPanel_build)

add_custom_target(GUI_ButtonEnableFilter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonEnableFilter" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonEnableFilter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonEnableFilter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonEnableFilter sequentially..."
)
add_dependencies(GUI_ButtonEnableFilter_build Filter_FilterConvertResolution_build)

add_custom_target(GUI_ButtonConvertColorDistribution_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonConvertColorDistribution" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonConvertColorDistribution/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonConvertColorDistribution/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonConvertColorDistribution sequentially..."
)
add_dependencies(GUI_ButtonConvertColorDistribution_build GUI_ButtonEnableFilter_build)

add_custom_target(GUI_ButtonAlignmentOffset_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAlignmentOffset" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAlignmentOffset/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAlignmentOffset/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonAlignmentOffset sequentially..."
)
add_dependencies(GUI_ButtonAlignmentOffset_build GUI_ButtonConvertColorDistribution_build)

add_custom_target(Algorithm_AngleInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AngleInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AngleInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AngleInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/AngleInspection sequentially..."
)
add_dependencies(Algorithm_AngleInspection_build GUI_ButtonAlignmentOffset_build)

add_custom_target(GUI_SetAngleInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetAngleInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetAngleInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetAngleInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SetAngleInspection sequentially..."
)
add_dependencies(GUI_SetAngleInspection_build Algorithm_AngleInspection_build)

add_custom_target(GUI_ShowResultAngleInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultAngleInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultAngleInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowResultAngleInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowResultAngleInspection sequentially..."
)
add_dependencies(GUI_ShowResultAngleInspection_build GUI_SetAngleInspection_build)

add_custom_target(Algorithm_ReplaceImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ReplaceImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ReplaceImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ReplaceImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/ReplaceImage sequentially..."
)
add_dependencies(Algorithm_ReplaceImage_build GUI_ShowResultAngleInspection_build)

add_custom_target(GUI_ButtonReplaceImageControl_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonReplaceImageControl" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonReplaceImageControl/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonReplaceImageControl/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonReplaceImageControl sequentially..."
)
add_dependencies(GUI_ButtonReplaceImageControl_build Algorithm_ReplaceImage_build)

add_custom_target(GUI_PropertyReplaceImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyReplaceImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyReplaceImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyReplaceImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyReplaceImage sequentially..."
)
add_dependencies(GUI_PropertyReplaceImage_build GUI_ButtonReplaceImageControl_build)

add_custom_target(GUI_ReplaceImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ReplaceImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ReplaceImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ReplaceImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ReplaceImagePanel sequentially..."
)
add_dependencies(GUI_ReplaceImagePanel_build GUI_PropertyReplaceImage_build)

add_custom_target(Integrator_GUI_AutoGenerator_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/AutoGenerator" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/AutoGenerator/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/AutoGenerator/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/AutoGenerator sequentially..."
)
add_dependencies(Integrator_GUI_AutoGenerator_build GUI_ReplaceImagePanel_build)

add_custom_target(Filter_FilterShiftByLayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShiftByLayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShiftByLayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterShiftByLayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterShiftByLayer sequentially..."
)
add_dependencies(Filter_FilterShiftByLayer_build Integrator_GUI_AutoGenerator_build)

add_custom_target(GUI_PropertyRasterReference_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRasterReference" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRasterReference/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRasterReference/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyRasterReference sequentially..."
)
add_dependencies(GUI_PropertyRasterReference_build Filter_FilterShiftByLayer_build)

add_custom_target(GUI_RasterReferenceImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RasterReferenceImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RasterReferenceImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RasterReferenceImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/RasterReferenceImagePanel sequentially..."
)
add_dependencies(GUI_RasterReferenceImagePanel_build GUI_PropertyRasterReference_build)

add_custom_target(AutoStart_AutoReStart_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/AutoStart/AutoReStart" -B "${CMAKE_CURRENT_SOURCE_DIR}/AutoStart/AutoReStart/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/AutoStart/AutoReStart/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building AutoStart/AutoReStart sequentially..."
)
add_dependencies(AutoStart_AutoReStart_build GUI_RasterReferenceImagePanel_build)

add_custom_target(Algorithm_ShiftMark_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ShiftMark" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ShiftMark/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ShiftMark/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/ShiftMark sequentially..."
)
add_dependencies(Algorithm_ShiftMark_build AutoStart_AutoReStart_build)

add_custom_target(Filter_FilterDynamicBrightness_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterDynamicBrightness" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterDynamicBrightness/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterDynamicBrightness/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterDynamicBrightness sequentially..."
)
add_dependencies(Filter_FilterDynamicBrightness_build Algorithm_ShiftMark_build)

add_custom_target(GUI_PropertyShiftMark_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyShiftMark" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyShiftMark/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyShiftMark/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyShiftMark sequentially..."
)
add_dependencies(GUI_PropertyShiftMark_build Filter_FilterDynamicBrightness_build)

add_custom_target(GUI_ShiftMarkImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShiftMarkImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShiftMarkImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShiftMarkImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShiftMarkImagePanel sequentially..."
)
add_dependencies(GUI_ShiftMarkImagePanel_build GUI_PropertyShiftMark_build)

add_custom_target(Integrator_GUI_IntegrationButtonCopyAlgorithm_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonCopyAlgorithm" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonCopyAlgorithm/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonCopyAlgorithm/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationButtonCopyAlgorithm sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationButtonCopyAlgorithm_build GUI_ShiftMarkImagePanel_build)

add_custom_target(Integrator_GUI_IntegrationButtonLoadAlgorithm_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonLoadAlgorithm" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonLoadAlgorithm/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonLoadAlgorithm/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationButtonLoadAlgorithm sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationButtonLoadAlgorithm_build Integrator_GUI_IntegrationButtonCopyAlgorithm_build)

add_custom_target(Integrator_GUI_IntegrationButtonSaveAlgorithm_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonSaveAlgorithm" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonSaveAlgorithm/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonSaveAlgorithm/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationButtonSaveAlgorithm sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationButtonSaveAlgorithm_build Integrator_GUI_IntegrationButtonLoadAlgorithm_build)

add_custom_target(GUI_ButtonShowInPlayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowInPlayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowInPlayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonShowInPlayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonShowInPlayer sequentially..."
)
add_dependencies(GUI_ButtonShowInPlayer_build Integrator_GUI_IntegrationButtonSaveAlgorithm_build)

add_custom_target(Filter_FilterMergeColor_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMergeColor" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMergeColor/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMergeColor/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterMergeColor sequentially..."
)
add_dependencies(Filter_FilterMergeColor_build GUI_ButtonShowInPlayer_build)

add_custom_target(GUI_ButtonAddSubPage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAddSubPage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAddSubPage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonAddSubPage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonAddSubPage sequentially..."
)
add_dependencies(GUI_ButtonAddSubPage_build Filter_FilterMergeColor_build)

add_custom_target(Filter_FilterReduceVStripe_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReduceVStripe" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReduceVStripe/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterReduceVStripe/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterReduceVStripe sequentially..."
)
add_dependencies(Filter_FilterReduceVStripe_build GUI_ButtonAddSubPage_build)

add_custom_target(Integrator_GUI_IntegrationSettingLight_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationSettingLight" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationSettingLight/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationSettingLight/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationSettingLight sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationSettingLight_build Filter_FilterReduceVStripe_build)

add_custom_target(PluginDLL_Light_LightDLL_CCSControlByLANVer2_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControlByLANVer2" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControlByLANVer2/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/CCSControlByLANVer2/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Light/LightDLL/CCSControlByLANVer2 sequentially..."
)
add_dependencies(PluginDLL_Light_LightDLL_CCSControlByLANVer2_build Integrator_GUI_IntegrationSettingLight_build)

add_custom_target(PluginDLL_Camera_CameraXtiumFx8ColorMonoLineTrigger_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumFx8ColorMonoLineTrigger" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumFx8ColorMonoLineTrigger/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumFx8ColorMonoLineTrigger/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraXtiumFx8ColorMonoLineTrigger sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraXtiumFx8ColorMonoLineTrigger_build PluginDLL_Light_LightDLL_CCSControlByLANVer2_build)

add_custom_target(Algorithm_CheckDataValidation_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CheckDataValidation" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CheckDataValidation/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/CheckDataValidation/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/CheckDataValidation sequentially..."
)
add_dependencies(Algorithm_CheckDataValidation_build PluginDLL_Camera_CameraXtiumFx8ColorMonoLineTrigger_build)

add_custom_target(GUI_CheckDataValidationImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckDataValidationImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckDataValidationImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/CheckDataValidationImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/CheckDataValidationImagePanel sequentially..."
)
add_dependencies(GUI_CheckDataValidationImagePanel_build Algorithm_CheckDataValidation_build)

add_custom_target(GUI_PropertyCheckDataValidation_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyCheckDataValidation" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyCheckDataValidation/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyCheckDataValidation/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyCheckDataValidation sequentially..."
)
add_dependencies(GUI_PropertyCheckDataValidation_build GUI_CheckDataValidationImagePanel_build)

add_custom_target(GUI_DisplayTargetList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayTargetList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayTargetList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/DisplayTargetList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/DisplayTargetList sequentially..."
)
add_dependencies(GUI_DisplayTargetList_build GUI_PropertyCheckDataValidation_build)

add_custom_target(Algorithm_World3D_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/World3D" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/World3D/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/World3D/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/World3D sequentially..."
)
add_dependencies(Algorithm_World3D_build GUI_DisplayTargetList_build)

add_custom_target(GUI_RobotActionEditPanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RobotActionEditPanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RobotActionEditPanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RobotActionEditPanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/RobotActionEditPanel sequentially..."
)
add_dependencies(GUI_RobotActionEditPanel_build Algorithm_World3D_build)

add_custom_target(GUI_PropertyRobotAction_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRobotAction" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRobotAction/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyRobotAction/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyRobotAction sequentially..."
)
add_dependencies(GUI_PropertyRobotAction_build GUI_RobotActionEditPanel_build)

add_custom_target(GUI_ShowRobotActivity_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowRobotActivity" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowRobotActivity/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowRobotActivity/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowRobotActivity sequentially..."
)
add_dependencies(GUI_ShowRobotActivity_build GUI_PropertyRobotAction_build)

add_custom_target(Algorithm_ColorCorrector_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ColorCorrector" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ColorCorrector/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/ColorCorrector/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/ColorCorrector sequentially..."
)
add_dependencies(Algorithm_ColorCorrector_build GUI_ShowRobotActivity_build)

add_custom_target(GUI_ColorCorrectorImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ColorCorrectorImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ColorCorrectorImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ColorCorrectorImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ColorCorrectorImagePanel sequentially..."
)
add_dependencies(GUI_ColorCorrectorImagePanel_build Algorithm_ColorCorrector_build)

add_custom_target(GUI_PropertyColorCorrector_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyColorCorrector" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyColorCorrector/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyColorCorrector/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyColorCorrector sequentially..."
)
add_dependencies(GUI_PropertyColorCorrector_build GUI_ColorCorrectorImagePanel_build)

add_custom_target(Integrator_GUI_IntegrationButtonGeneral_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonGeneral" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonGeneral/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationButtonGeneral/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationButtonGeneral sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationButtonGeneral_build GUI_PropertyColorCorrector_build)

add_custom_target(GUI_PropertyWorld3D_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyWorld3D" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyWorld3D/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyWorld3D/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyWorld3D sequentially..."
)
add_dependencies(GUI_PropertyWorld3D_build Integrator_GUI_IntegrationButtonGeneral_build)

add_custom_target(GUI_World3DImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/World3DImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/World3DImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/World3DImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/World3DImagePanel sequentially..."
)
add_dependencies(GUI_World3DImagePanel_build GUI_PropertyWorld3D_build)

add_custom_target(GUI_ListSelectFixedPage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListSelectFixedPage" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListSelectFixedPage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ListSelectFixedPage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ListSelectFixedPage sequentially..."
)
add_dependencies(GUI_ListSelectFixedPage_build GUI_World3DImagePanel_build)

add_custom_target(GUI_SetAlignmentLargeHeadLine_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetAlignmentLargeHeadLine" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetAlignmentLargeHeadLine/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetAlignmentLargeHeadLine/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SetAlignmentLargeHeadLine sequentially..."
)
add_dependencies(GUI_SetAlignmentLargeHeadLine_build GUI_ListSelectFixedPage_build)

add_custom_target(GUI_ButtonGenerateMaskFromBackGround_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonGenerateMaskFromBackGround" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonGenerateMaskFromBackGround/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonGenerateMaskFromBackGround/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonGenerateMaskFromBackGround sequentially..."
)
add_dependencies(GUI_ButtonGenerateMaskFromBackGround_build GUI_SetAlignmentLargeHeadLine_build)

add_custom_target(Algorithm_AlignmentBlock_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentBlock" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentBlock/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentBlock/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/AlignmentBlock sequentially..."
)
add_dependencies(Algorithm_AlignmentBlock_build GUI_ButtonGenerateMaskFromBackGround_build)

add_custom_target(GUI_AlignmentBlockImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentBlockImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentBlockImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentBlockImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AlignmentBlockImagePanel sequentially..."
)
add_dependencies(GUI_AlignmentBlockImagePanel_build Algorithm_AlignmentBlock_build)

add_custom_target(GUI_PropertyAlignmentBlock_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentBlock" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentBlock/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentBlock/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyAlignmentBlock sequentially..."
)
add_dependencies(GUI_PropertyAlignmentBlock_build GUI_AlignmentBlockImagePanel_build)

add_custom_target(PluginDLL_Camera_CameraXtiumCISVienex_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumCISVienex" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumCISVienex/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumCISVienex/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraXtiumCISVienex sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraXtiumCISVienex_build GUI_PropertyAlignmentBlock_build)

add_custom_target(GUI_ShowThresholdSlideBar_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowThresholdSlideBar" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowThresholdSlideBar/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowThresholdSlideBar/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowThresholdSlideBar sequentially..."
)
add_dependencies(GUI_ShowThresholdSlideBar_build PluginDLL_Camera_CameraXtiumCISVienex_build)

add_custom_target(Integrator_GUI_IntegrationLocalBind_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationLocalBind" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationLocalBind/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationLocalBind/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationLocalBind sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationLocalBind_build GUI_ShowThresholdSlideBar_build)

add_custom_target(GUI_ButtonRaiseOtherProcess_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonRaiseOtherProcess" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonRaiseOtherProcess/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonRaiseOtherProcess/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonRaiseOtherProcess sequentially..."
)
add_dependencies(GUI_ButtonRaiseOtherProcess_build Integrator_GUI_IntegrationLocalBind_build)

add_custom_target(GUI_ButtonReplaceColorInLibID_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonReplaceColorInLibID" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonReplaceColorInLibID/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonReplaceColorInLibID/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonReplaceColorInLibID sequentially..."
)
add_dependencies(GUI_ButtonReplaceColorInLibID_build GUI_ButtonRaiseOtherProcess_build)

add_custom_target(Integrator_GUI_IntegrationModifyMaster_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationModifyMaster" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationModifyMaster/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationModifyMaster/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationModifyMaster sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationModifyMaster_build GUI_ButtonReplaceColorInLibID_build)

add_custom_target(Integrator_GUI_IntegrationStackMultiNGThumbnail_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationStackMultiNGThumbnail" -B "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationStackMultiNGThumbnail/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Integrator/GUI/IntegrationStackMultiNGThumbnail/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Integrator/GUI/IntegrationStackMultiNGThumbnail sequentially..."
)
add_dependencies(Integrator_GUI_IntegrationStackMultiNGThumbnail_build Integrator_GUI_IntegrationModifyMaster_build)

add_custom_target(Filter_FilterMatchColorBandDynamically_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMatchColorBandDynamically" -B "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMatchColorBandDynamically/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Filter/FilterMatchColorBandDynamically/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Filter/FilterMatchColorBandDynamically sequentially..."
)
add_dependencies(Filter_FilterMatchColorBandDynamically_build Integrator_GUI_IntegrationStackMultiNGThumbnail_build)

add_custom_target(PluginDLL_Camera_CameraXtiumLinearHSColorMonoLineTrigger_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumLinearHSColorMonoLineTrigger" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumLinearHSColorMonoLineTrigger/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraXtiumLinearHSColorMonoLineTrigger/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraXtiumLinearHSColorMonoLineTrigger sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraXtiumLinearHSColorMonoLineTrigger_build Filter_FilterMatchColorBandDynamically_build)

add_custom_target(PluginDLL_Camera_CameraMVSGigE_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraMVSGigE" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraMVSGigE/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraMVSGigE/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraMVSGigE sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraMVSGigE_build PluginDLL_Camera_CameraXtiumLinearHSColorMonoLineTrigger_build)

add_custom_target(GUI_FlatInspectionImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/FlatInspectionImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/FlatInspectionImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/FlatInspectionImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/FlatInspectionImagePanel sequentially..."
)
add_dependencies(GUI_FlatInspectionImagePanel_build PluginDLL_Camera_CameraMVSGigE_build)

add_custom_target(GUI_PropertyFlatInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyFlatInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyFlatInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyFlatInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyFlatInspection sequentially..."
)
add_dependencies(GUI_PropertyFlatInspection_build GUI_FlatInspectionImagePanel_build)

add_custom_target(PluginDLL_Camera_CameraFromLoadedImages_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraFromLoadedImages" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraFromLoadedImages/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraFromLoadedImages/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraFromLoadedImages sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraFromLoadedImages_build GUI_PropertyFlatInspection_build)

add_custom_target(GUI_ButtonSaveInitialLoadGUIData_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveInitialLoadGUIData" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveInitialLoadGUIData/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonSaveInitialLoadGUIData/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonSaveInitialLoadGUIData sequentially..."
)
add_dependencies(GUI_ButtonSaveInitialLoadGUIData_build PluginDLL_Camera_CameraFromLoadedImages_build)

add_custom_target(GUI_SetAutoThresholdByHistogram_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetAutoThresholdByHistogram" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetAutoThresholdByHistogram/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/SetAutoThresholdByHistogram/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/SetAutoThresholdByHistogram sequentially..."
)
add_dependencies(GUI_SetAutoThresholdByHistogram_build GUI_ButtonSaveInitialLoadGUIData_build)

add_custom_target(Algorithm_FlatInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/FlatInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/FlatInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/FlatInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/FlatInspection sequentially..."
)
add_dependencies(Algorithm_FlatInspection_build GUI_SetAutoThresholdByHistogram_build)

add_custom_target(PluginDLL_Camera_CameraMVSUSB_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraMVSUSB" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraMVSUSB/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraMVSUSB/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraMVSUSB sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraMVSUSB_build Algorithm_FlatInspection_build)

add_custom_target(ServiceLib_CheckBoard_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/CheckBoard" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/CheckBoard/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/CheckBoard/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib/CheckBoard sequentially..."
)
add_dependencies(ServiceLib_CheckBoard_build PluginDLL_Camera_CameraMVSUSB_build)

add_custom_target(PluginDLL_Camera_CameraQtUSBStandard_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraQtUSBStandard" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraQtUSBStandard/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraQtUSBStandard/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraQtUSBStandard sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraQtUSBStandard_build ServiceLib_CheckBoard_build)

add_custom_target(GUI_ButtonUpdateAllByHistogram_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonUpdateAllByHistogram" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonUpdateAllByHistogram/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ButtonUpdateAllByHistogram/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ButtonUpdateAllByHistogram sequentially..."
)
add_dependencies(GUI_ButtonUpdateAllByHistogram_build PluginDLL_Camera_CameraQtUSBStandard_build)

add_custom_target(GUI_ShowFPSInCamera_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowFPSInCamera" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowFPSInCamera/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowFPSInCamera/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowFPSInCamera sequentially..."
)
add_dependencies(GUI_ShowFPSInCamera_build GUI_ButtonUpdateAllByHistogram_build)

add_custom_target(GUI_RecordMoiveWinExe_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RecordMoiveWinExe" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RecordMoiveWinExe/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/RecordMoiveWinExe/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/RecordMoiveWinExe sequentially..."
)
add_dependencies(GUI_RecordMoiveWinExe_build GUI_ShowFPSInCamera_build)

add_custom_target(GUI_ShowOCR_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowOCR" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowOCR/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowOCR/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowOCR sequentially..."
)
add_dependencies(GUI_ShowOCR_build GUI_RecordMoiveWinExe_build)

add_custom_target(PluginDLL_Camera_CameraMVSLinear_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraMVSLinear" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraMVSLinear/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraMVSLinear/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraMVSLinear sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraMVSLinear_build GUI_ShowOCR_build)

add_custom_target(PluginDLL_Light_LightDLL_LightHIKRobotLAN_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LightHIKRobotLAN" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LightHIKRobotLAN/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LightHIKRobotLAN/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Light/LightDLL/LightHIKRobotLAN sequentially..."
)
add_dependencies(PluginDLL_Light_LightDLL_LightHIKRobotLAN_build PluginDLL_Camera_CameraMVSLinear_build)

add_custom_target(PluginDLL_PIO_GIOHIKRobotCamera_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/GIOHIKRobotCamera" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/GIOHIKRobotCamera/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/GIOHIKRobotCamera/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/GIOHIKRobotCamera sequentially..."
)
add_dependencies(PluginDLL_PIO_GIOHIKRobotCamera_build PluginDLL_Light_LightDLL_LightHIKRobotLAN_build)

add_custom_target(GUI_ChangeCameraByInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeCameraByInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeCameraByInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ChangeCameraByInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ChangeCameraByInspection sequentially..."
)
add_dependencies(GUI_ChangeCameraByInspection_build PluginDLL_PIO_GIOHIKRobotCamera_build)

add_custom_target(Algorithm_PixelInspection_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PixelInspection" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PixelInspection/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/PixelInspection/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/PixelInspection sequentially..."
)
add_dependencies(Algorithm_PixelInspection_build GUI_ChangeCameraByInspection_build)

add_custom_target(GUI_ShowColorDifferenceResultList_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowColorDifferenceResultList" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowColorDifferenceResultList/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowColorDifferenceResultList/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowColorDifferenceResultList sequentially..."
)
add_dependencies(GUI_ShowColorDifferenceResultList_build Algorithm_PixelInspection_build)

add_custom_target(Algorithm_XRay3D_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/XRay3D" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/XRay3D/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/XRay3D/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/XRay3D sequentially..."
)
add_dependencies(Algorithm_XRay3D_build GUI_ShowColorDifferenceResultList_build)

add_custom_target(GUI_XRay3DImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/XRay3DImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/XRay3DImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/XRay3DImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/XRay3DImagePanel sequentially..."
)
add_dependencies(GUI_XRay3DImagePanel_build Algorithm_XRay3D_build)

add_custom_target(GUI_PropertyXRay3D_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyXRay3D" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyXRay3D/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyXRay3D/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyXRay3D sequentially..."
)
add_dependencies(GUI_PropertyXRay3D_build GUI_XRay3DImagePanel_build)

add_custom_target(GUI_ShowColorDifferenceEditManual_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowColorDifferenceEditManual" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowColorDifferenceEditManual/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/ShowColorDifferenceEditManual/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/ShowColorDifferenceEditManual sequentially..."
)
add_dependencies(GUI_ShowColorDifferenceEditManual_build GUI_PropertyXRay3D_build)

add_custom_target(ResultDLL_ResultWriteCSVBarcodeLine_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultWriteCSVBarcodeLine" -B "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultWriteCSVBarcodeLine/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ResultDLL/ResultWriteCSVBarcodeLine/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ResultDLL/ResultWriteCSVBarcodeLine sequentially..."
)
add_dependencies(ResultDLL_ResultWriteCSVBarcodeLine_build GUI_ShowColorDifferenceEditManual_build)

add_custom_target(Algorithm_RobotAction_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/RobotAction" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/RobotAction/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/RobotAction/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/RobotAction sequentially..."
)
add_dependencies(Algorithm_RobotAction_build ResultDLL_ResultWriteCSVBarcodeLine_build)

add_custom_target(PluginDLL_Light_LightDLL_LightOpenAACam1B_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LightOpenAACam1B" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LightOpenAACam1B/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Light/LightDLL/LightOpenAACam1B/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Light/LightDLL/LightOpenAACam1B sequentially..."
)
add_dependencies(PluginDLL_Light_LightDLL_LightOpenAACam1B_build Algorithm_RobotAction_build)

add_custom_target(PluginDLL_PIO_PIOOpenAACam1B_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/PIOOpenAACam1B" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/PIOOpenAACam1B/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/PIO/PIOOpenAACam1B/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/PIO/PIOOpenAACam1B sequentially..."
)
add_dependencies(PluginDLL_PIO_PIOOpenAACam1B_build PluginDLL_Light_LightDLL_LightOpenAACam1B_build)

add_custom_target(Algorithm_AlignmentShiftRotation_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentShiftRotation" -B "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentShiftRotation/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/AlignmentShiftRotation/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Algorithm/AlignmentShiftRotation sequentially..."
)
add_dependencies(Algorithm_AlignmentShiftRotation_build PluginDLL_PIO_PIOOpenAACam1B_build)

add_custom_target(GUI_AlignmentShiftRotationImagePanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentShiftRotationImagePanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentShiftRotationImagePanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/AlignmentShiftRotationImagePanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/AlignmentShiftRotationImagePanel sequentially..."
)
add_dependencies(GUI_AlignmentShiftRotationImagePanel_build Algorithm_AlignmentShiftRotation_build)

add_custom_target(GUI_PropertyAlignmentShiftRotation_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentShiftRotation" -B "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentShiftRotation/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/GUI/PropertyAlignmentShiftRotation/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building GUI/PropertyAlignmentShiftRotation sequentially..."
)
add_dependencies(GUI_PropertyAlignmentShiftRotation_build GUI_AlignmentShiftRotationImagePanel_build)

add_custom_target(PluginDLL_SequencePlugin_SeqOpenAAController1B_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/SeqOpenAAController1B" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/SeqOpenAAController1B/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/SequencePlugin/SeqOpenAAController1B/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/SequencePlugin/SeqOpenAAController1B sequentially..."
)
add_dependencies(PluginDLL_SequencePlugin_SeqOpenAAController1B_build GUI_PropertyAlignmentShiftRotation_build)

add_custom_target(MachineController_RobotInspection_CaptureHIKCameraButton_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/MachineController/RobotInspection/CaptureHIKCameraButton" -B "${CMAKE_CURRENT_SOURCE_DIR}/MachineController/RobotInspection/CaptureHIKCameraButton/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/MachineController/RobotInspection/CaptureHIKCameraButton/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building MachineController/RobotInspection/CaptureHIKCameraButton sequentially..."
)
add_dependencies(MachineController_RobotInspection_CaptureHIKCameraButton_build PluginDLL_SequencePlugin_SeqOpenAAController1B_build)

add_custom_target(PluginDLL_Camera_CameraHIKRobotGigE_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraHIKRobotGigE" -B "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraHIKRobotGigE/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PluginDLL/Camera/CameraHIKRobotGigE/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PluginDLL/Camera/CameraHIKRobotGigE sequentially..."
)
add_dependencies(PluginDLL_Camera_CameraHIKRobotGigE_build MachineController_RobotInspection_CaptureHIKCameraButton_build)

add_custom_target(MachineController_RobotInspection_GUIShowPoints_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/MachineController/RobotInspection/GUIShowPoints" -B "${CMAKE_CURRENT_SOURCE_DIR}/MachineController/RobotInspection/GUIShowPoints/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/MachineController/RobotInspection/GUIShowPoints/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building MachineController/RobotInspection/GUIShowPoints sequentially..."
)
add_dependencies(MachineController_RobotInspection_GUIShowPoints_build PluginDLL_Camera_CameraHIKRobotGigE_build)

add_custom_target(MachineController_RobotInspection_GeneralStockerRobot_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/MachineController/RobotInspection/GeneralStockerRobot" -B "${CMAKE_CURRENT_SOURCE_DIR}/MachineController/RobotInspection/GeneralStockerRobot/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/MachineController/RobotInspection/GeneralStockerRobot/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building MachineController/RobotInspection/GeneralStockerRobot sequentially..."
)
add_dependencies(MachineController_RobotInspection_GeneralStockerRobot_build MachineController_RobotInspection_GUIShowPoints_build)

add_custom_target(Tutorial_TutrialExecuter_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Tutorial/TutrialExecuter" -B "${CMAKE_CURRENT_SOURCE_DIR}/Tutorial/TutrialExecuter/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Tutorial/TutrialExecuter/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Tutorial/TutrialExecuter sequentially..."
)
add_dependencies(Tutorial_TutrialExecuter_build MachineController_RobotInspection_GeneralStockerRobot_build)

