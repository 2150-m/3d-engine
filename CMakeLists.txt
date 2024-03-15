cmake_minimum_required(VERSION 3.5)
project(app)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -g")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE FILES
    src/*.cpp
    src/*.hpp

    lib/glad/glad.c
    lib/imgui/*.cpp
)

add_executable(app ${FILES})

target_include_directories(app PUBLIC
    "${CMAKE_SOURCE_DIR}/src/"
    "${CMAKE_SOURCE_DIR}/lib"
)

# target_compile_features(app PRIVATE cxx_std_17)
target_link_directories(app PRIVATE lib/glfw lib/glad)
target_link_libraries(app glfw3 X11 GL dl pthread Xrandr Xi)
