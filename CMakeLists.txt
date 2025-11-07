cmake_minimum_required(VERSION 3.28)
project(PongBot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0074 NEW)
set(Torch_DIR "~/libtorch/share/cmake/Torch")
find_package(Torch REQUIRED)

# Propagate Torch ABI flag (-D_GLIBCXX_USE_CXX11_ABI=0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
message(STATUS "Torch flags: ${TORCH_CXX_FLAGS}")

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

file(GLOB library_sources "src/*.cpp" "src/donat_lib/*.cpp")
add_library(GraphicalGameLib ${library_sources})
target_include_directories(GraphicalGameLib PUBLIC includes)
target_link_libraries(GraphicalGameLib
    SFML::Audio
    SFML::Graphics
    SFML::Window
    SFML::System
    ${TORCH_LIBRARIES}
)

add_executable(PongBot src/main.cpp)
target_include_directories(PongBot PRIVATE includes)
target_link_libraries(PongBot
    GraphicalGameLib
    ${TORCH_LIBRARIES}
)

set_target_properties(PongBot PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
