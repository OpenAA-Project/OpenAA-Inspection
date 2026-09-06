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

# === Independent Parallel Builds (Meta-Build) ===
# デフォルトのビルドタイプを Release に設定 (指定されていない場合)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_custom_target(DisplayImage_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/DisplayImage" -B "${CMAKE_CURRENT_SOURCE_DIR}/DisplayImage/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/DisplayImage/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building DisplayImage sequentially..."
)

add_custom_target(Component_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/Component" -B "${CMAKE_CURRENT_SOURCE_DIR}/Component/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/Component/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building Component sequentially..."
)
add_dependencies(Component_build DisplayImage_build)

add_custom_target(DisplayOpenGL_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/DisplayOpenGL" -B "${CMAKE_CURRENT_SOURCE_DIR}/DisplayOpenGL/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/DisplayOpenGL/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building DisplayOpenGL sequentially..."
)
add_dependencies(DisplayOpenGL_build Component_build)

add_custom_target(InputInTouchPanel_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/InputInTouchPanel" -B "${CMAKE_CURRENT_SOURCE_DIR}/InputInTouchPanel/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/InputInTouchPanel/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building InputInTouchPanel sequentially..."
)
add_dependencies(InputInTouchPanel_build DisplayOpenGL_build)

add_custom_target(PDF_PDFWidget_build ALL
    COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/PDF/PDFWidget" -B "${CMAKE_CURRENT_SOURCE_DIR}/PDF/PDFWidget/build" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/PDF/PDFWidget/build" --config ${CMAKE_BUILD_TYPE} -- -k
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "[Meta-Build] Configuring and Building PDF/PDFWidget sequentially..."
)
add_dependencies(PDF_PDFWidget_build InputInTouchPanel_build)

