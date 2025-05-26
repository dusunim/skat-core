get_filename_component(target_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB_RECURSE src_files CONFIGURE_DEPENDS *.cpp *.h)

add_executable(${target_name} ${src_files})
cp_executable_settings(${target_name} "test")

find_package(fmt CONFIG REQUIRED)

target_link_libraries(${target_name} PRIVATE fmt::fmt)
target_link_libraries(${target_name} PRIVATE foundation)
