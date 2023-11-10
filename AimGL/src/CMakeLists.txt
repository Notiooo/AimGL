cmake_minimum_required(VERSION 3.24)

project(AimGLSrc VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CMakeLists_Sources.txt)

add_library(AimGLSrc STATIC ${PROJECT_SOURCES})
target_precompile_headers(AimGLSrc PUBLIC pch.h)

set(CUSTOM_INCLUDES_DIR ${CMAKE_CURRENT_BINARY_DIR}/custom_includes)
file(MAKE_DIRECTORY ${CUSTOM_INCLUDES_DIR})

set(CUSTOM_INCLUDES 
    ${FETCHCONTENT_BASE_DIR}/minitrace-src/minitrace.h
    ${FETCHCONTENT_BASE_DIR}/stb-src/stb_image.h
)

foreach(HEADER ${CUSTOM_INCLUDES})
    configure_file(
        ${HEADER}
        ${CUSTOM_INCLUDES_DIR}
        COPYONLY
    )
endforeach()

target_include_directories(AimGLSrc PUBLIC
        ${FETCHCONTENT_BASE_DIR}/glew-src/include
        ${FETCHCONTENT_BASE_DIR}/result-src/include
        ${FETCHCONTENT_BASE_DIR}/entt-src/src
        ${glm_SOURCE_DIR}
        ${CUSTOM_INCLUDES_DIR}
        )

target_link_libraries(AimGLSrc
        PUBLIC
        sfml-graphics
        ImGui-SFML::ImGui-SFML
        glew_s
        glm
        spdlog
        minitrace
        )

# Copy libraries

add_custom_command(TARGET AimGLSrc POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE:spdlog>
        $<TARGET_FILE:minitrace>
        $<TARGET_FILE_DIR:AimGLSrc>
        )

# Remove previous game resources

add_custom_command(TARGET AimGLSrc PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory
        $<TARGET_FILE_DIR:AimGLSrc>/resources
        )

# Copy game resources

add_custom_command(TARGET AimGLSrc POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:AimGLSrc>/resources
        )

add_executable(AimGLApp main.cpp)

add_custom_command(TARGET AimGLApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:AimGLSrc>
        $<TARGET_FILE_DIR:AimGLApp>
        )

target_link_libraries(AimGLApp PRIVATE AimGLSrc)
