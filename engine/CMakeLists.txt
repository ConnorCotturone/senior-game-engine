find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(extern/assimp)


add_library(engine STATIC
    # include files
    include/engine.h
    include/window.h
    include/input.h
    include/shader.h
    include/mesh.h
    include/model.h
    include/camera.h
    include/material.h

    # source files
    src/engine.cpp
    src/window.cpp
    src/input.cpp
    src/shader.cpp
    src/mesh.cpp
    src/model.cpp
    src/camera.cpp
    src/material.cpp    

    # glad
    extern/glad/glad.c
)

target_link_libraries(engine PUBLIC glfw OpenGL::GL assimp)

target_include_directories(engine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/extern
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