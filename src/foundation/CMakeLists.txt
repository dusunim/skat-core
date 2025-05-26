get_filename_component(target_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB_RECURSE src_files CONFIGURE_DEPENDS *.cpp *.h)
file(GLOB_RECURSE include_files CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${target_name}/*.h)

add_library(${target_name} SHARED ${src_files} ${include_files})
add_library(skat-core::${target_name} ALIAS ${target_name})

file(REAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../.." project_root_dir)
cp_library_settings(${target_name} "library" ${project_root_dir})
