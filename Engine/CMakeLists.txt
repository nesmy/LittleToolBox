project(Engine)

# gather all source files

file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(${PROJECT_NAME} ${sources} ${headers})

target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/ltbpch.h)

# include directories

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Core
    ${CMAKE_SOURCE_DIR}/Vendor/raylib/src    
    ${CMAKE_SOURCE_DIR}/Vendor/entt/src
    ${CMAKE_SOURCE_DIR}/Vendor/imgui
    ${CMAKE_SOURCE_DIR}/Vendor/rImGui
    ${CMAKE_SOURCE_DIR}/Vendor/imgui/backends
    ${CMAKE_SOURCE_DIR}/Vendor/spdlog/include
)

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    raylib 
    spdlog   
    EnTT
    imgui
    rImGui
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