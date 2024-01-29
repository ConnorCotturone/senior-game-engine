find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(extern/assimp)
add_subdirectory(extern/spdlog)

set(IMGUI_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui)
set(IMGUI_SOURCES 
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imgui_demo.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})

target_link_libraries(imgui PRIVATE glfw)
target_include_directories(imgui PUBLIC 
    ${IMGUI_PATH}
    ${IMGUI_PATH}/backends
)

add_library(engine STATIC
    # include files
    include/engine.h
    include/window.h
    include/shader.h
    include/mesh.h
    include/model.h
    include/camera.h
    include/material.h
    include/logging.h
    include/input_handler.h
    include/imgui_handler.h
    include/event_handler.h

    include/ECS/Entity.h
    include/ECS/EntityManager.h
    include/ECS/Component.h
    include/ECS/IComponentArray.h
    include/ECS/ComponentManager.h
    include/ECS/ISystem.h
    include/ECS/SystemManager.h
    include/ECS/ECSManager.h

    include/Components/Transform.h

    # source files
    src/engine.cpp
    src/window.cpp
    src/shader.cpp
    src/mesh.cpp
    src/model.cpp
    src/camera.cpp
    src/material.cpp    
    src/logging.cpp
    src/input_handler.cpp
    src/imgui_handler.cpp
    src/event_handler.cpp

    src/ECS/EntityManager.cpp
    src/ECS/ComponentManager.cpp
    src/ECS/IComponentArray.cpp
    src/ECS/SystemManager.cpp
    src/ECS/ECSManager.cpp

    # glad
    extern/glad/glad.c
)

target_link_libraries(engine PUBLIC glfw OpenGL::GL assimp spdlog::spdlog_header_only imgui)

target_include_directories(engine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ECS
    ${CMAKE_CURRENT_SOURCE_DIR}/extern
    # ${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui/backends
    # ${CMAKE_CURRENT_SOURCE_DIR}/extern/glm
    # ${CMAKE_CURRENT_SOURCE_DIR}/extern/glad
    # ${CMAKE_CURRENT_SOURCE_DIR}/extern/KHR
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/../sandbox/shaders
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/../sandbox/resources
)