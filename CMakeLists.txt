cmake_minimum_required(VERSION 3.13)

project(stimpak CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(stimpak
  INTERFACE)

target_include_directories(stimpak
  INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
