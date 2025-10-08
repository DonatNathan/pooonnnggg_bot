cmake_minimum_required(VERSION 3.28)
project(PongBot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fetch SFML from GitHub
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

# Compile graphical lib files
file(GLOB library_sources "src/*.cpp" "src/donat_lib/*.cpp")
add_library(GraphicalGameLib ${library_sources})
target_include_directories(GraphicalGameLib PUBLIC includes)

target_link_libraries(GraphicalGameLib SFML::Audio SFML::Graphics SFML::Window SFML::System)

# Create executable
add_executable(PongBot src/main.cpp)

# Link graphical lib to executable
target_link_libraries(PongBot GraphicalGameLib)

# Add include directories AFTER creating executable
target_include_directories(PongBot PRIVATE includes)

# Set output directory
set_target_properties(PongBot PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
