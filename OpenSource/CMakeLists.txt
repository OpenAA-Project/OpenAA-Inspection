# CMakeLists.txt generated from OpenSource.sln
cmake_minimum_required(VERSION 3.16)

project(OpenSource LANGUAGES CXX)

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
set(TOTAL_PROJECTS 5)

include(ProcessorCount)
ProcessorCount(DETECTED_CORES)
if(DETECTED_CORES EQUAL 0)
    set(DETECTED_CORES 4)
endif()

set(SLN_INNER_JOBS 1 CACHE STRING "Parallel compile jobs per subproject")
set(META_MODE_DESC "Sequential SLN (Single-threaded)")

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

add_custom_target(MetaBuild_Init ALL
    COMMAND ${CMAKE_COMMAND}
        -DMODE=INIT
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DTOTAL_PROJECTS=${TOTAL_PROJECTS}"
        "-DMETA_MODE_DESC=${META_MODE_DESC}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)

add_custom_target(DisplayImage_build ALL
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=DisplayImage"
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
add_dependencies(DisplayImage_build MetaBuild_Init)

add_custom_target(Component_build ALL
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=Component"
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
add_dependencies(Component_build DisplayImage_build)

add_custom_target(DisplayOpenGL_build ALL
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=DisplayOpenGL"
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
add_dependencies(DisplayOpenGL_build Component_build)

add_custom_target(InputInTouchPanel_build ALL
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=InputInTouchPanel"
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
add_dependencies(InputInTouchPanel_build DisplayOpenGL_build)

add_custom_target(PDF_PDFWidget_build ALL
    COMMAND ${CMAKE_COMMAND}
        -DMODE=STEP
        "-DMETA_SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        "-DPROJ_REL_DIR=PDF/PDFWidget"
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
add_dependencies(PDF_PDFWidget_build InputInTouchPanel_build)

add_custom_target(MetaBuild_Finish ALL
    COMMAND ${CMAKE_COMMAND}
        -DMODE=FINISH
        "-DMETA_BIN_DIR=${CMAKE_BINARY_DIR}"
        -P "${META_HELPER_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
add_dependencies(MetaBuild_Finish PDF_PDFWidget_build)

