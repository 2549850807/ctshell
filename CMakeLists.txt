set(CTSHELL_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if(ESP_PLATFORM)
    set(srcs
            "${CT_SHELL_DIR}/ctshell.c"
            "${CT_SHELL_DIR}/port/esp32/ctshell_esp32.c"
    )

    set(includes
            "${CT_SHELL_DIR}"
            "${CT_SHELL_DIR}/port/esp32"
    )

    idf_component_register(
            SRCS ${srcs}
            INCLUDE_DIRS ${includes}
            REQUIRES driver esp_timer freertos log
            LDFRAGMENTS "${CT_SHELL_DIR}/port/esp32/linker.lf"
    )

    target_link_libraries(${COMPONENT_LIB} INTERFACE "-T ${CTSHELL_DIR}/port/esp32/ctshell_cmd.ld")
endif()
