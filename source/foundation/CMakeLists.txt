get_filename_component(target_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB_RECURSE target_files CONFIGURE_DEPENDS
    *.cpp
    *.h
)

set(include_dirs PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/internal"
)

add_library(${target_name} SHARED ${target_files})
set_target_properties(${target_name} PROPERTIES FOLDER "library")

target_compile_definitions(${target_name} PRIVATE "${target_name}_EXPORTS")
target_include_directories(${target_name} PUBLIC ${include_dirs})
