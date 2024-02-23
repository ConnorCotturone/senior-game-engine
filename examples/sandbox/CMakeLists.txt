add_executable(sandbox 
    # headers
    include/sandbox.h

    # source
    src/sandbox.cpp 
)

target_link_libraries(sandbox PRIVATE 
    cgx 
)
