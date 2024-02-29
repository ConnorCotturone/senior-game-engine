# Copyright © 2024 Jacob Curlin
# setup external dependencies

# =====================================================

# glfw
add_subdirectory(glfw)

# =====================================================
# spdlog

add_subdirectory(spdlog)

# =====================================================
# ImGui

set(IMGUI_PATH imgui)
set(IMGUI_SOURCE_FILES
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imgui_demo.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
)

add_library("imgui" STATIC ${IMGUI_SOURCE_FILES})
target_link_libraries(imgui PRIVATE glfw)
target_include_directories(imgui PUBLIC
    ${IMGUI_PATH}
    ${IMGUI_PATH}/backends
)

# =====================================================
