# CMakeLists.txt generated from ServiceLib.sln
cmake_minimum_required(VERSION 3.16)

project(ServiceLib LANGUAGES CXX)

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

add_custom_target(CommonGUIDLL_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/CommonGUIDLL" -B "${CMAKE_CURRENT_SOURCE_DIR}/CommonGUIDLL/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/CommonGUIDLL/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building CommonGUIDLL sequentially..."
)

add_custom_target(EditGUI_EditGUILib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/../EditGUI/EditGUILib" -B "${CMAKE_CURRENT_SOURCE_DIR}/../EditGUI/EditGUILib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/../EditGUI/EditGUILib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ../EditGUI/EditGUILib sequentially..."
)
add_dependencies(EditGUI_EditGUILib_build CommonGUIDLL_build)

add_custom_target(EditPasswordOnControl_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/EditPasswordOnControl" -B "${CMAKE_CURRENT_SOURCE_DIR}/EditPasswordOnControl/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/EditPasswordOnControl/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building EditPasswordOnControl sequentially..."
)
add_dependencies(EditPasswordOnControl_build EditGUI_EditGUILib_build)

add_custom_target(ModelPageItem_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ModelPageItem" -B "${CMAKE_CURRENT_SOURCE_DIR}/ModelPageItem/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ModelPageItem/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ModelPageItem sequentially..."
)
add_dependencies(ModelPageItem_build EditPasswordOnControl_build)

add_custom_target(ModelPageLayerItem_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ModelPageLayerItem" -B "${CMAKE_CURRENT_SOURCE_DIR}/ModelPageLayerItem/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ModelPageLayerItem/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ModelPageLayerItem sequentially..."
)
add_dependencies(ModelPageLayerItem_build ModelPageItem_build)

add_custom_target(XML_MTXMLServer_MTXMLLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/../XML/MTXMLServer/MTXMLLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/../XML/MTXMLServer/MTXMLLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/../XML/MTXMLServer/MTXMLLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ../XML/MTXMLServer/MTXMLLib sequentially..."
)
add_dependencies(XML_MTXMLServer_MTXMLLib_build ModelPageLayerItem_build)

add_custom_target(GeneralSource_Sequence_SeqLib_SeqLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/../GeneralSource/Sequence/SeqLib/SeqLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/../GeneralSource/Sequence/SeqLib/SeqLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/../GeneralSource/Sequence/SeqLib/SeqLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ../GeneralSource/Sequence/SeqLib/SeqLib sequentially..."
)
add_dependencies(GeneralSource_Sequence_SeqLib_SeqLib_build XML_MTXMLServer_MTXMLLib_build)

add_custom_target(ServiceLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceLib sequentially..."
)
add_dependencies(ServiceLib_build GeneralSource_Sequence_SeqLib_SeqLib_build)

add_custom_target(PasswordManager_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PasswordManager" -B "${CMAKE_CURRENT_SOURCE_DIR}/PasswordManager/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PasswordManager/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PasswordManager sequentially..."
)
add_dependencies(PasswordManager_build ServiceLib_build)

add_custom_target(ExecuteVisualizer_EVExecuterLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/../ExecuteVisualizer/EVExecuterLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/../ExecuteVisualizer/EVExecuterLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/../ExecuteVisualizer/EVExecuterLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ../ExecuteVisualizer/EVExecuterLib sequentially..."
)
add_dependencies(ExecuteVisualizer_EVExecuterLib_build PasswordManager_build)

add_custom_target(LanguageManager_LanguageManagerLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/LanguageManager/LanguageManagerLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/LanguageManager/LanguageManagerLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/LanguageManager/LanguageManagerLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building LanguageManager/LanguageManagerLib sequentially..."
)
add_dependencies(LanguageManager_LanguageManagerLib_build ExecuteVisualizer_EVExecuterLib_build)

add_custom_target(DFSLibrary_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/DFSLibrary" -B "${CMAKE_CURRENT_SOURCE_DIR}/DFSLibrary/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/DFSLibrary/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building DFSLibrary sequentially..."
)
add_dependencies(DFSLibrary_build LanguageManager_LanguageManagerLib_build)

add_custom_target(ExecuteVisualizer_EVObjectLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/../ExecuteVisualizer/EVObjectLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/../ExecuteVisualizer/EVObjectLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/../ExecuteVisualizer/EVObjectLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ../ExecuteVisualizer/EVObjectLib sequentially..."
)
add_dependencies(ExecuteVisualizer_EVObjectLib_build DFSLibrary_build)

add_custom_target(Integrator_IntegrationLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/../Integrator/IntegrationLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/../Integrator/IntegrationLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/../Integrator/IntegrationLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ../Integrator/IntegrationLib sequentially..."
)
add_dependencies(Integrator_IntegrationLib_build ExecuteVisualizer_EVObjectLib_build)

add_custom_target(ServiceForAlgorithm_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceForAlgorithm" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceForAlgorithm/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceForAlgorithm/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceForAlgorithm sequentially..."
)
add_dependencies(ServiceForAlgorithm_build Integrator_IntegrationLib_build)

add_custom_target(ForWindows_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ForWindows" -B "${CMAKE_CURRENT_SOURCE_DIR}/ForWindows/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ForWindows/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ForWindows sequentially..."
)
add_dependencies(ForWindows_build ServiceForAlgorithm_build)

add_custom_target(ServiceExecution_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecution" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecution/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecution/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceExecution sequentially..."
)
add_dependencies(ServiceExecution_build ForWindows_build)

add_custom_target(ServiceExecutionEditor_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecutionEditor" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecutionEditor/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecutionEditor/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceExecutionEditor sequentially..."
)
add_dependencies(ServiceExecutionEditor_build ServiceExecution_build)

add_custom_target(ServiceExecutionPlayer_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecutionPlayer" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecutionPlayer/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecutionPlayer/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceExecutionPlayer sequentially..."
)
add_dependencies(ServiceExecutionPlayer_build ServiceExecutionEditor_build)

add_custom_target(ServiceExecutionEditorWithSequence_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecutionEditorWithSequence" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecutionEditorWithSequence/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecutionEditorWithSequence/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceExecutionEditorWithSequence sequentially..."
)
add_dependencies(ServiceExecutionEditorWithSequence_build ServiceExecutionPlayer_build)

add_custom_target(ServiceExecutionShadow_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecutionShadow" -B "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecutionShadow/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/ServiceExecutionShadow/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ServiceExecutionShadow sequentially..."
)
add_dependencies(ServiceExecutionShadow_build ServiceExecutionEditorWithSequence_build)

add_custom_target(Integrator_IntegrationPanelLib_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/../Integrator/IntegrationPanelLib" -B "${CMAKE_CURRENT_SOURCE_DIR}/../Integrator/IntegrationPanelLib/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/../Integrator/IntegrationPanelLib/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building ../Integrator/IntegrationPanelLib sequentially..."
)
add_dependencies(Integrator_IntegrationPanelLib_build ServiceExecutionShadow_build)

add_custom_target(NetworkDrive_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/NetworkDrive" -B "${CMAKE_CURRENT_SOURCE_DIR}/NetworkDrive/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/NetworkDrive/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building NetworkDrive sequentially..."
)
add_dependencies(NetworkDrive_build Integrator_IntegrationPanelLib_build)

