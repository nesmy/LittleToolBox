project(Editor)

# gather all source files
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_executable(${PROJECT_NAME} ${sources} ${headers})


# export engine symbols
target_compile_definitions(${PROJECT_NAME} PUBLIC 
)

# includes directories
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include    
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Controls    
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Windows    
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Editor    
    ${CMAKE_SOURCE_DIR}/Engine/include
    # ${CMAKE_SOURCE_DIR}/Vendor/raylib/src
    # ${CMAKE_SOURCE_DIR}/Vendor/raylib-cpp/include
    # ${CMAKE_SOURCE_DIR}/Vendor/spdlog/include
    # ${CMAKE_SOURCE_DIR}/Vendor/imgui
    # ${CMAKE_SOURCE_DIR}/Vendor/rImGui
    # ${CMAKE_SOURCE_DIR}/Vendor/entt/src
    # ${CMAKE_SOURCE_DIR}/Vendor/imgui/backends
)

# link directories
target_link_directories(${PROJECT_NAME} PUBLIC 
)

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    Engine
)


# copy resources
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Resources)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND 
        ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources
        ${EXECUTABLE_OUTPUT_PATH}/Resources
    )
else()
    message(WARNING "[WARNING] no resource directory!")
endif()