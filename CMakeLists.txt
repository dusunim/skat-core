cmake_minimum_required(VERSION 3.10)

project(skat-core)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  include(${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake)

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_subdirectory(src/foundation)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
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

  include(CPack)

  # install settings
  if(MSVC)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_CONFIG_NAME}" CACHE PATH "" FORCE)
  endif()

  include(GNUInstallDirs)

  install(
    DIRECTORY "${CMAKE_SOURCE_DIR}/include/"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  include(CMakePackageConfigHelpers)

  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/skat-coreConfigVersion.cmake"
    VERSION ${CPACK_PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
  )

  configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/skat-coreConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/skat-coreConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/skat-core
  )

  # install config files
  install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/skat-coreConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/skat-coreConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/skat-core
  )

  # export targets
  install(EXPORT skat-coreTargets
    FILE skat-coreTargets.cmake
    NAMESPACE skat-core::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/skat-core
  )
endif()
