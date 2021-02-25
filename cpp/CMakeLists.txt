cmake_minimum_required(VERSION 3.12)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

project(hash)
add_executable(hash)  
target_sources(hash PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
