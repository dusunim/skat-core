get_filename_component(target_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB_RECURSE target_files CONFIGURE_DEPENDS
    *.cpp
    *.h
)

set(include_dirs PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/internal"
)

add_executable(${target_name} ${target_files})
set_target_properties(${target_name} PROPERTIES FOLDER "test")

target_include_directories(${target_name} PUBLIC ${include_dirs})

find_package(fmt CONFIG REQUIRED)

target_link_libraries(${target_name} PRIVATE fmt::fmt)
target_link_libraries(${target_name} PRIVATE foundation)
