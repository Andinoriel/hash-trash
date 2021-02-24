cmake_minimum_required(VERSION 3.12)

enable_language(C)
set(CMAKE_C_STANDARD 98)

project(hash)
add_executable(hash)  
target_sources(hash PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
