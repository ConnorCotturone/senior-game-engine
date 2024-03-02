# Copyright © 2024 Jacob Curlin
# cgx engine

cmake_minimum_required(VERSION 3.6.0)
project(cgx VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# OpenGL
find_package(OpenGL REQUIRED)

# external dependencies
add_subdirectory(external)

# cgx Static Library Creation
add_library(cgx STATIC "")

target_sources(cgx
    # core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/core/common.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/core/engine.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/core/input_handler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/core/window.h
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/engine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/input_handler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window.cpp

    # ecs
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/ecs_types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/i_system.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/component_array.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/component_manager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/entity_manager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/system_manager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/ecs_manager.h
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/component_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/entity_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/system_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/ecs_manager.cpp

    # components
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/components/transform_component.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/components/render_component.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/components/light_component.h

    # event
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/event/event_handler.h
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/event/event_handler.cpp

    # render
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/render/camera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/render/material.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/render/mesh.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/render/model.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/render/shader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/render/texture.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/render/resource_manager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/render/framebuffer.h
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/render/camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/render/material.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/render/mesh.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/render/model.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/render/shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/render/texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/render/resource_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/render/framebuffer.cpp

    # gui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gui/imgui_manager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gui/imgui_render_window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gui/imgui_window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gui/imgui_performance_window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gui/imgui_ecs_window.h
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/imgui_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/imgui_render_window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/imgui_window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/imgui_performance_window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/imgui_ecs_window.cpp

    # utility
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/utility/logging.h
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utility/logging.cpp

    # glad
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/glad.c
)

target_include_directories(cgx 
    PUBLIC 
        include/

    SYSTEM PUBLIC 
        external/
    
    PRIVATE 
        src/
)

target_link_libraries(cgx PUBLIC
    glfw
    OpenGL::GL
    imgui
    spdlog::spdlog_header_only
    glm::glm-header-only
)

set(SHADERS_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/data/shaders/")
set(ASSETS_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/data/assets/")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/utility/paths.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/include/utility/paths.h
               @ONLY )

# copy assets to build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data/shaders
        ${SHADERS_DIRECTORY}
)

# copy assets to build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data/assets
        ${ASSETS_DIRECTORY}
)

add_subdirectory(examples)