find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(engine STATIC
    # include files
    include/engine.h

    # source files
    src/engine.cpp
    src/app.cpp
)

target_link_libraries(engine PUBLIC glfw OpenGL::GL)

target_include_directories(engine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
)
