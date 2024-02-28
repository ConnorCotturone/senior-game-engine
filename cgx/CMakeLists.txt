# find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(external/glfw)
add_subdirectory(external/spdlog)

# IMGUI Static Library Creation 
set(IMGUI_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)
set(IMGUI_SOURCE_FILES
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imgui_demo.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
)

add_library("imgui" STATIC ${IMGUI_SOURCE_FILES})

target_link_libraries(imgui PRIVATE glfw)
target_include_directories(imgui PUBLIC 
    ${IMGUI_PATH}
    ${IMGUI_PATH}/backends
)

# cgx Static Library Creation
add_library(cgx STATIC "")
    
target_sources(cgx
    # Core
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/engine.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/input_handler.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window.h 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/input_handler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window.cpp

    # ECS
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/ecs_types.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/i_system.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/component_array.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/component_manager.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/entity_manager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/system_manager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/ecs_manager.h 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/component_manager.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/entity_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/system_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/ecs_manager.cpp 

    # Event
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/event/event_handler.h 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/event/event_handler.cpp

    # Render
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/camera.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/material.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/mesh.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/model.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/shader.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/texture.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/resource_manager.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/framebuffer.h 

    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/camera.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/material.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/mesh.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/model.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/shader.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/texture.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/resource_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/framebuffer.cpp
    
    # Components
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/components/transform_component.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/components/render_component.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/components/light_component.h

    # Gui
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/imgui_manager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/imgui_ecs_system.h
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/imgui_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/imgui_ecs_system.cpp

    # Utility
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utility/logging.h
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utility/logging.cpp

    # glad
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/glad.c

)

target_include_directories(cgx 
    # cgx public header
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    
    SYSTEM PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external

    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render
    ${CMAKE_CURRENT_SOURCE_DIR}/src/event
    ${CMAKE_CURRENT_SOURCE_DIR}/src/components
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utility

)

target_link_libraries(cgx PUBLIC glfw OpenGL::GL spdlog::spdlog_header_only imgui)

set(SHADER_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/shaders")
set(DATA_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/data")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/resources_paths.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/resources_paths.h @ONLY)

# (todo - implement more robust solution to data / shaders at build-time)

# copy shaders to build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders
)

# copy data (i.e. assets) to build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data
)