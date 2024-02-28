add_executable(sandbox 
    # headers
    include/sandbox.h
    include/cubemap.h

    # source
    src/sandbox.cpp 
    src/cubemap.cpp
)

target_link_libraries(sandbox PRIVATE 
    cgx 
)
