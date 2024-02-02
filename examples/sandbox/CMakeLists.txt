add_executable(sandbox 
    # headers
    include/sandbox.h
    include/grid.h

    # source
    src/grid.cpp
    src/sandbox.cpp 
)

target_link_libraries(sandbox PRIVATE 
    cgx 
)
