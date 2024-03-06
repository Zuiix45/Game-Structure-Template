cmake_minimum_required(VERSION 3.2...3.5)

# Set C++ standard and flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-stack-protector")

# Use vcpkg toolchain file. This needs to be at the top of the file
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

set(CMAKE_BUILD_TYPE "Release")

project(Game)

# Find required packages
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)
find_package(Stb REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)

# Gather all sources (you can modify this as needed)
file(GLOB_RECURSE PROJECT_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.hpp
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.rc
    ${CMAKE_SOURCE_DIR}/glad/src/glad.c
)

# Create the executable - add WIN32 to build for application
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Link against the required headers
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/glad/include)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    glm::glm
    Freetype::Freetype
    OpenAL::OpenAL
    glfw
)

# Set output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# Copy data folder to the binary folder

add_custom_target(copy-runtime-files ALL
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/bin/data
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_SOURCE_DIR}/bin/data)
    