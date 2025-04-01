cmake_minimum_required(VERSION 3.10)

project(skat-core)

find_package(fmt CONFIG REQUIRED)

set(
    CPP_SOURCES
    src/main.cpp
)

add_executable(skat-core ${CPP_SOURCES})

target_link_libraries(skat-core PRIVATE fmt::fmt)

add_custom_target(
    check-format
    COMMAND clang-format --dry-run ${CPP_SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "checking format in src..."
)

add_custom_target(
    format
    COMMAND clang-format -i ${CPP_SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "checking format in src..."
)