add_library(engine STATIC
    # include files
    include/engine.h

    # source files
    src/engine.cpp
)

target_include_directories(engine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
)