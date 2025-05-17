cmake_minimum_required(VERSION 3.10)

project(skat-core)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(source/foundation)
add_subdirectory(test/test_foundation)

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

set_target_properties(check-format PROPERTIES FOLDER "workflow")
set_target_properties(format PROPERTIES FOLDER "workflow")
