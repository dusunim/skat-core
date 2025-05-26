function(cp_executable_settings target_name folder_name)
    set_target_properties(${target_name} PROPERTIES FOLDER ${folder_name})
    set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)

    file(GLOB_RECURSE src_files CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX src FILES ${src_files})
endfunction()

function(cp_library_settings target_name folder_name project_root_dir)
    set(cp_include_dir "${project_root_dir}/include")

    set_target_properties(${target_name} PROPERTIES FOLDER ${folder_name})
    set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)

    file(GLOB_RECURSE src_files CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
    file(GLOB_RECURSE include_files CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/include/*.h ${CMAKE_SOURCE_DIR}/include/*.hpp)

    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX src FILES ${src_files})
    if(EXISTS ${cp_include_dir}/${target_name})
        source_group(TREE ${cp_include_dir}/${target_name} PREFIX include FILES ${include_files})
    endif()

    target_compile_definitions(${target_name} PRIVATE "${target_name}_EXPORTS")
    target_include_directories(${target_name} PUBLIC
        $<BUILD_INTERFACE:${cp_include_dir}>
        $<INSTALL_INTERFACE:include>
    )

    install(TARGETS ${target_name} EXPORT skat-coreTargets)
endfunction()
