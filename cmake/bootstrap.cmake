if(NOT DEFINED ENV{VCPKG_ROOT} OR "$ENV{VCPKG_ROOT}" STREQUAL "")
    set(ENV{VCPKG_ROOT} "${CMAKE_SOURCE_DIR}/../vcpkg")

    if(NOT EXISTS "${ENV{VCPKG_ROOT}}")
        message(STATUS "cloning vcpkg...")
        execute_process(
            COMMAND git clone https://github.com/microsoft/vcpkg.git "${ENV{VCPKG_ROOT}}"
            RESULT_VARIABLE result
        )
        if(NOT result EQUAL 0)
            message(FATAL_ERROR "failed to clone vcpkg")
        endif()

        message(STATUS "bootstrapping vcpkg...")
        if(WIN32)
            execute_process(COMMAND ${ENV{VCPKG_ROOT}}/bootstrap-vcpkg.bat WORKING_DIRECTORY ${ENV{VCPKG_ROOT}})
        else()
            execute_process(COMMAND ./bootstrap-vcpkg.sh WORKING_DIRECTORY ${ENV{VCPKG_ROOT}})
        endif()
    endif()
endif()

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file" FORCE)
