add_executable(sandbox 
    src/sandbox_app.cpp 
)

target_link_libraries(sandbox PRIVATE 
    engine 
)
