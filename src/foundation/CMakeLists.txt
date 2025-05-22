get_filename_component(target_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB_RECURSE src_files CONFIGURE_DEPENDS *.cpp *.h)
file(GLOB_RECURSE include_files CONFIGURE_DEPENDS ${cp_include_dir}/*.h)

add_library(${target_name} SHARED ${src_files} ${include_files})
cp_common_settings(${target_name} "library")
