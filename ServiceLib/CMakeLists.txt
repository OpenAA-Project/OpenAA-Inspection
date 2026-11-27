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

# === Meta-Build Configuration ===
# Default build type is Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

option(FORCE_RECONFIGURE "Force re-running CMake configure for all subprojects" OFF)
set(TOTAL_PROJECTS 23)

include(ProcessorCount)
ProcessorCount(DETECTED_CORES)
if(DETECTED_CORES EQUAL 0)
    set(DETECTED_CORES 4)
endif()

set(TOTAL_PARALLEL_BUDGET ${DETECTED_CORES})
set(DEFAULT_INNER_JOBS 1)
set(DEFAULT_OUTER_JOBS ${TOTAL_PARALLEL_BUDGET})
set(SLN_OUTER_JOBS ${DEFAULT_OUTER_JOBS} CACHE STRING "Number of subprojects to build concurrently")
set(SLN_INNER_JOBS ${DEFAULT_INNER_JOBS} CACHE STRING "Parallel compile jobs per subproject")
set(META_MODE_DESC "Parallel SLN (Outer: ${SLN_OUTER_JOBS} projects x Inner: ${SLN_INNER_JOBS} jobs)")

# === Progress Display & Subproject Build Helper Script ===
set(META_HELPER_SCRIPT "${CMAKE_BINARY_DIR}/_meta_build_helper.cmake")
file(WRITE "${META_HELPER_SCRIPT}" [===[
if(NOT DEFINED MODE)
    message(FATAL_ERROR "MODE is not defined")
endif()

set(STATE_DIR "${META_BIN_DIR}/_meta_build_state")
file(MAKE_DIRECTORY "${STATE_DIR}")
set(START_EPOCH_FILE "${STATE_DIR}/start_epoch.txt")
set(START_TIME_FILE  "${STATE_DIR}/start_time.txt")
set(COUNTER_FILE     "${STATE_DIR}/counter.txt")
set(LOCK_FILE        "${STATE_DIR}/progress.lock")

function(format_elapsed_time ELAPSED_SEC OUT_VAR)
    if(ELAPSED_SEC LESS 0)
        set(ELAPSED_SEC 0)
    endif()
    math(EXPR H "${ELAPSED_SEC} / 3600")
    math(EXPR M "(${ELAPSED_SEC} % 3600) / 60")
    math(EXPR S "${ELAPSED_SEC} % 60")
    if(H LESS 10)
        set(H "0${H}")
    endif()
    if(M LESS 10)
        set(M "0${M}")
    endif()
    if(S LESS 10)
        set(S "0${S}")
    endif()
    set(${OUT_VAR} "${H}:${M}:${S}" PARENT_SCOPE)
endfunction()

if(MODE STREQUAL "INIT")
    string(TIMESTAMP NOW_EPOCH "%s")
    string(TIMESTAMP NOW_STR   "%Y-%m-%d %H:%M:%S")
    file(WRITE "${START_EPOCH_FILE}" "${NOW_EPOCH}")
    file(WRITE "${START_TIME_FILE}"  "${NOW_STR}")
    file(WRITE "${COUNTER_FILE}"     "0")
    message(STATUS "========================================================================")
    message(STATUS "[Meta-Build] Build Started : ${NOW_STR} (Total Projects: ${TOTAL_PROJECTS})")
    if(DEFINED META_MODE_DESC)
        message(STATUS "[Meta-Build] Mode          : ${META_MODE_DESC}")
    endif()
    message(STATUS "========================================================================")

elseif(MODE STREQUAL "STEP")
    # Acquire lock to atomically increment counter and print progress header
    file(LOCK "${LOCK_FILE}" TIMEOUT 10)
    if(EXISTS "${START_EPOCH_FILE}")
        file(READ "${START_EPOCH_FILE}" START_EPOCH)
        string(STRIP "${START_EPOCH}" START_EPOCH)
    else()
        string(TIMESTAMP START_EPOCH "%s")
        file(WRITE "${START_EPOCH_FILE}" "${START_EPOCH}")
    endif()

    if(EXISTS "${START_TIME_FILE}")
        file(READ "${START_TIME_FILE}" TOTAL_START_STR)
        string(STRIP "${TOTAL_START_STR}" TOTAL_START_STR)
    else()
        string(TIMESTAMP TOTAL_START_STR "%Y-%m-%d %H:%M:%S")
        file(WRITE "${START_TIME_FILE}" "${TOTAL_START_STR}")
    endif()

    if(EXISTS "${COUNTER_FILE}")
        file(READ "${COUNTER_FILE}" CURRENT_COUNT)
        string(STRIP "${CURRENT_COUNT}" CURRENT_COUNT)
        if("${CURRENT_COUNT}" STREQUAL "")
            set(CURRENT_COUNT 0)
        endif()
    else()
        set(CURRENT_COUNT 0)
    endif()
    math(EXPR CURRENT_COUNT "${CURRENT_COUNT} + 1")
    file(WRITE "${COUNTER_FILE}" "${CURRENT_COUNT}")

    string(TIMESTAMP NOW_EPOCH "%s")
    string(TIMESTAMP NOW_STR   "%Y-%m-%d %H:%M:%S")
    math(EXPR ELAPSED_SEC "${NOW_EPOCH} - ${START_EPOCH}")
    format_elapsed_time(${ELAPSED_SEC} ELAPSED_STR)

    message(STATUS "------------------------------------------------------------------------\n-- [${CURRENT_COUNT}/${TOTAL_PROJECTS}] Building: ${PROJ_REL_DIR}\n--   Build Start : ${NOW_STR} (Total Start: ${TOTAL_START_STR})\n--   Elapsed     : ${ELAPSED_STR}\n-- ------------------------------------------------------------------------")
    file(LOCK "${LOCK_FILE}" RELEASE)

    # Avoid parent MAKEFLAGS jobserver interference
    unset(ENV{MAKEFLAGS})
    unset(ENV{MFLAGS})

    set(SUB_SRC_DIR "${META_SRC_DIR}/${PROJ_REL_DIR}")
    set(SUB_BIN_DIR "${SUB_SRC_DIR}/build")

    # Configure only on first run, build type change, or FORCE_RECONFIGURE=ON
    set(NEED_CONFIGURE TRUE)
    if(EXISTS "${SUB_BIN_DIR}/CMakeCache.txt" AND EXISTS "${SUB_BIN_DIR}/.meta_build_type" AND NOT FORCE_RECONFIGURE)
        file(READ "${SUB_BIN_DIR}/.meta_build_type" LAST_BUILD_TYPE)
        string(STRIP "${LAST_BUILD_TYPE}" LAST_BUILD_TYPE)
        if("${LAST_BUILD_TYPE}" STREQUAL "${BUILD_TYPE}")
            set(NEED_CONFIGURE FALSE)
        endif()
    endif()

    if(NEED_CONFIGURE)
        set(CFG_CMD "${CMAKE_COMMAND}" -S "${SUB_SRC_DIR}" -B "${SUB_BIN_DIR}" "-DCMAKE_BUILD_TYPE=${BUILD_TYPE}")
        if(NOT "${META_GENERATOR}" STREQUAL "")
            list(APPEND CFG_CMD -G "${META_GENERATOR}")
        endif()
        if(NOT "${META_GEN_PLATFORM}" STREQUAL "")
            list(APPEND CFG_CMD -A "${META_GEN_PLATFORM}")
        endif()
        if(NOT "${META_GEN_TOOLSET}" STREQUAL "")
            list(APPEND CFG_CMD -T "${META_GEN_TOOLSET}")
        endif()
        execute_process(
            COMMAND ${CFG_CMD}
            WORKING_DIRECTORY "${META_SRC_DIR}"
            RESULT_VARIABLE CFG_RES
        )
        if(NOT CFG_RES EQUAL 0)
            message(FATAL_ERROR "[Meta-Build] Configure failed (${CFG_RES}): ${PROJ_REL_DIR}")
        endif()
        file(WRITE "${SUB_BIN_DIR}/.meta_build_type" "${BUILD_TYPE}")
    endif()

    # Build
    set(BLD_CMD "${CMAKE_COMMAND}" --build "${SUB_BIN_DIR}" --config "${BUILD_TYPE}")
    if(INNER_JOBS GREATER 1)
        list(APPEND BLD_CMD --parallel "${INNER_JOBS}")
    endif()
    if(META_GENERATOR MATCHES "Makefiles")
        list(APPEND BLD_CMD -- -k)
    elseif(META_GENERATOR MATCHES "Ninja")
        list(APPEND BLD_CMD -- -k 0)
    endif()

    execute_process(
        COMMAND ${BLD_CMD}
        WORKING_DIRECTORY "${META_SRC_DIR}"
        RESULT_VARIABLE BLD_RES
    )
    if(NOT BLD_RES EQUAL 0)
        message(FATAL_ERROR "[Meta-Build] Build failed (${BLD_RES}): ${PROJ_REL_DIR}")
    endif()

elseif(MODE STREQUAL "RUN_PHASE")
    unset(ENV{MAKEFLAGS})
    unset(ENV{MFLAGS})
    set(PHASE_CMD "${CMAKE_COMMAND}" --build "${META_BIN_DIR}" --target "${PHASE_TARGET}" --config "${BUILD_TYPE}" --parallel "${OUTER_JOBS}")
    if(META_GENERATOR MATCHES "Makefiles")
        list(APPEND PHASE_CMD -- -k)
    elseif(META_GENERATOR MATCHES "Ninja")
        list(APPEND PHASE_CMD -- -k 0)
    endif()
    execute_process(
        COMMAND ${PHASE_CMD}
        WORKING_DIRECTORY "${META_SRC_DIR}"
        RESULT_VARIABLE PHASE_RES
    )
    if(NOT PHASE_RES EQUAL 0)
        message(WARNING "[Meta-Build] Phase '${PHASE_TARGET}' finished with errors (${PHASE_RES}).")
    endif()

elseif(MODE STREQUAL "FINISH")
    if(EXISTS "${START_EPOCH_FILE}")
        file(READ "${START_EPOCH_FILE}" START_EPOCH)
        string(STRIP "${START_EPOCH}" START_EPOCH)
        string(TIMESTAMP NOW_EPOCH "%s")
        string(TIMESTAMP NOW_STR   "%Y-%m-%d %H:%M:%S")
        math(EXPR ELAPSED_SEC "${NOW_EPOCH} - ${START_EPOCH}")
        format_elapsed_time(${ELAPSED_SEC} ELAPSED_STR)
        message(STATUS "========================================================================")
        message(STATUS "[Meta-Build] All Builds Finished : ${NOW_STR} (Total Elapsed: ${ELAPSED_STR})")
        message(STATUS "========================================================================")
    endif()
endif()
]===])

# === Phase 1: Static Libraries (Parallel) ===
add_custom_target(CommonGUIDLL_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=CommonGUIDLL"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(EditGUI_EditGUILib_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=../EditGUI/EditGUILib"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(EditPasswordOnControl_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=EditPasswordOnControl"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(ModelPageItem_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=ModelPageItem"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(ModelPageLayerItem_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=ModelPageLayerItem"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(XML_MTXMLServer_MTXMLLib_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=../XML/MTXMLServer/MTXMLLib"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(GeneralSource_Sequence_SeqLib_SeqLib_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=../GeneralSource/Sequence/SeqLib/SeqLib"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(ServiceLib_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=ServiceLib"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(PasswordManager_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=PasswordManager"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(ExecuteVisualizer_EVExecuterLib_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=../ExecuteVisualizer/EVExecuterLib"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(LanguageManager_LanguageManagerLib_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=LanguageManager/LanguageManagerLib"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(DFSLibrary_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=DFSLibrary"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(ExecuteVisualizer_EVObjectLib_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=../ExecuteVisualizer/EVObjectLib"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(Integrator_IntegrationLib_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=../Integrator/IntegrationLib"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(ServiceForAlgorithm_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=ServiceForAlgorithm"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(ForWindows_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=ForWindows"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(ServiceExecution_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=ServiceExecution"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(ServiceExecutionEditor_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=ServiceExecutionEditor"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(ServiceExecutionPlayer_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=ServiceExecutionPlayer"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(ServiceExecutionEditorWithSequence_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=ServiceExecutionEditorWithSequence"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(ServiceExecutionShadow_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=ServiceExecutionShadow"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(Integrator_IntegrationPanelLib_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=../Integrator/IntegrationPanelLib"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(StaticLibs_all)
add_dependencies(StaticLibs_all
    CommonGUIDLL_build
    EditGUI_EditGUILib_build
    EditPasswordOnControl_build
    ModelPageItem_build
    ModelPageLayerItem_build
    XML_MTXMLServer_MTXMLLib_build
    GeneralSource_Sequence_SeqLib_SeqLib_build
    ServiceLib_build
    PasswordManager_build
    ExecuteVisualizer_EVExecuterLib_build
    LanguageManager_LanguageManagerLib_build
    DFSLibrary_build
    ExecuteVisualizer_EVObjectLib_build
    Integrator_IntegrationLib_build
    ServiceForAlgorithm_build
    ForWindows_build
    ServiceExecution_build
    ServiceExecutionEditor_build
    ServiceExecutionPlayer_build
    ServiceExecutionEditorWithSequence_build
    ServiceExecutionShadow_build
    Integrator_IntegrationPanelLib_build
)

# === Phase 2: Other Projects / DLLs / EXEs (Parallel) ===
add_custom_target(NetworkDrive_build
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=NetworkDrive"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DINNER_JOBS=${SLN_INNER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        "-DMETA_GEN_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
        "-DMETA_GEN_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
        "-DFORCE_RECONFIGURE=${FORCE_RECONFIGURE}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_custom_target(OtherProjects_all)
add_dependencies(OtherProjects_all
    NetworkDrive_build
)

# === Master Parallel Build Entrypoint ===
add_custom_target(MetaBuild_All ALL
    COMMAND ${CMAKE_COMMAND}
        -DMODE=INIT
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DMETA_MODE_DESC=${META_MODE_DESC}"
        -P "${META_HELPER_SCRIPT}"
    COMMAND ${CMAKE_COMMAND}
        -DMODE=RUN_PHASE
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        -DPHASE_TARGET=StaticLibs_all
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DOUTER_JOBS=${SLN_OUTER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        -P "${META_HELPER_SCRIPT}"
    COMMAND ${CMAKE_COMMAND}
        -DMODE=RUN_PHASE
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        -DPHASE_TARGET=OtherProjects_all
        "-DBUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DOUTER_JOBS=${SLN_OUTER_JOBS}"
        "-DMETA_GENERATOR=${CMAKE_GENERATOR}"
        -P "${META_HELPER_SCRIPT}"
    COMMAND ${CMAKE_COMMAND}
        -DMODE=FINISH
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)

