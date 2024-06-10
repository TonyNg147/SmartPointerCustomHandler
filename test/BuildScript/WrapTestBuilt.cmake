function(WrapBuilt)
    set(option)
    set(one_val BuiltName)
    set(mul_val Sources LinkedLibs LinkedFolders)
    cmake_parse_arguments(Inner "${option}" "${one_val}" "${mul_val}" ${ARGN})

    qt_add_executable(${Inner_BuiltName} ${Inner_Sources})

    set(DEFAULT_LIBS
        PRIVATE
            SmartPtr
            Qt6::Core
            Qt6::Gui
            Qt6::Test
            Qt6::Widgets
    )

    target_link_libraries(${Inner_BuiltName}
        PRIVATE
            ${Inner_LinkedLibs}
        ${DEFAULT_LIBS}
    )

    target_link_libraries(${Inner_BuiltName}
        PRIVATE
            ${Inner_LinkedFolders}
    )
endfunction(WrapBuilt)
