cmake_minimum_required(VERSION 3.15)
set(VCPKG_TARGET_TRIPLET "x64-mingw-static")
set(VCPKG_HOST_TRIPLET "x64-mingw-static")
project(DimetricMinesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(VCPKG_MANIFEST_MODE ON)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/field.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC "include")
find_package(SFML 3 COMPONENTS Graphics Window System CONFIG REQUIRED)
target_compile_definitions(${PROJECT_NAME} PRIVATE SFML_STATIC)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System
)