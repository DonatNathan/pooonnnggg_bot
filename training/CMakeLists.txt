cmake_minimum_required(VERSION 3.15)
project(pong_dqn)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED TORCH_DIR)
  message(STATUS "TORCH_DIR not defined, please set it or edit CMakeLists to point to LibTorch")
endif()

find_package(Torch REQUIRED PATHS ${TORCH_DIR} NO_DEFAULT_PATH)

file(GLOB library_sources "src/*.cpp")
add_library(ReinforcementTraining ${library_sources})
target_link_libraries(ReinforcementTraining "${TORCH_LIBRARIES}")
target_include_directories(ReinforcementTraining PUBLIC includes)

add_executable(pong_train src/main_training.cpp)
target_link_libraries(pong_train ReinforcementTraining)
target_include_directories(pong_train PRIVATE includes)

set_property(TARGET pong_train PROPERTY CXX_STANDARD 17)
