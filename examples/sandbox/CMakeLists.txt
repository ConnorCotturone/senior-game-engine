add_executable(sandbox 
    src/sandbox.cpp 
)

target_link_libraries(sandbox PRIVATE 
    cgx 
)
