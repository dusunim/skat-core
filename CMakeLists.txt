cmake_minimum_required(VERSION 3.10)

project(skat-core)
include(${CMAKE_SOURCE_DIR}/cmake/config.cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src/foundation)
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

# package settings
set(CPACK_PACKAGE_NAME "skat-core")
set(CPACK_PACKAGE_VENDOR "Cupix")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "skat core library")
set(CPACK_PACKAGE_CONTACT "dustin.kim@cupix.com")

if(NOT DEFINED CPACK_PACKAGE_VERSION)
  set(CPACK_PACKAGE_VERSION "0.0.0")
endif()

if(MSVC)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_CONFIG_NAME}" CACHE PATH "" FORCE)
endif()

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/" DESTINATION include)
include(CPack)
