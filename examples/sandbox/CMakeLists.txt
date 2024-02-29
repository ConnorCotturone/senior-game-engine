add_executable(sandbox 
    # headers
    include/sandbox.h
    include/cube_map.h

    # source
    src/sandbox.cpp
    src/cube_map.cpp
)

target_include_directories(sandbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(sandbox PRIVATE
    cgx 
)
