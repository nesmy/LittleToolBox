project(Engine)

# gather all source files

file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

file(GLOB ImGuizmo ${CMAKE_SOURCE_DIR}/Vendor/ImGuizmo/ImGuizmo.cpp)
file(GLOB ImGuizmoH ${CMAKE_SOURCE_DIR}/Vendor/ImGuizmo/ImGuizmo.h)

file(GLOB ImGuiFileDialog ${CMAKE_SOURCE_DIR}/Vendor/ImGuiFileDialog/ImGuiFileDialog.cpp)
file(GLOB ImGuiFileDialogH ${CMAKE_SOURCE_DIR}/Vendor/ImGuiFileDialog/ImGuiFileDialog.h)
file(GLOB ImGuiFileDialogConfig ${CMAKE_SOURCE_DIR}/Vendor/ImGuiFileDialog/ImGuiFileDialogConfig.h)

add_library(${PROJECT_NAME} ${sources} ${headers} 
                            ${ImGuizmoH} ${ImGuizmo} )
                            # ${ImGuiFileDialogH} ${ImGuiFileDialogH} ${ImGuiFileDialogConfig})

target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/ltbpch.h)
set_source_files_properties(${ImGuizmo}
  PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
set_source_files_properties(${ImGuizmoH}
    PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

# add_compile_definitions(LTB_ENABLE_ASSERTS)

# include directories

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Scene
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ImGui
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Auxiliaries
    ${CMAKE_SOURCE_DIR}/Vendor/raylib/src    
    ${CMAKE_SOURCE_DIR}/Vendor/raygui/src    
    ${CMAKE_SOURCE_DIR}/Vendor/entt/src
    ${CMAKE_SOURCE_DIR}/Vendor/glm
    ${CMAKE_SOURCE_DIR}/Vendor/imgui
    ${CMAKE_SOURCE_DIR}/Vendor/rImGui
    ${CMAKE_SOURCE_DIR}/Vendor/imgui/backends
    ${CMAKE_SOURCE_DIR}/Vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/Vendor/ImGuizmo
    ${CMAKE_SOURCE_DIR}/Vendor/yaml-cpp/include
    # ${CMAKE_SOURCE_DIR}/Vendor/raygizmo/include
    ${CMAKE_SOURCE_DIR}/Vendor/raylib/src
    ${CMAKE_SOURCE_DIR}/Vendor/ImGuiFileDialog
)

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    raylib 
    glm
    spdlog   
    EnTT
    imgui
    ImGuiFileDialog
    rImGui    
    yaml-cpp
)


# copy resources
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Data)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND 
        ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_CURRENT_SOURCE_DIR}/Data
        ${EXECUTABLE_OUTPUT_PATH}/Data
    )
else()
    message(WARNING "[WARNING] no Data directory!")
endif()