cmake_minimum_required(VERSION 3.10)

project(skat-core)

find_package(fmt CONFIG REQUIRED)

add_executable(skat-core src/main.cpp)

target_link_libraries(skat-core PRIVATE fmt::fmt)
