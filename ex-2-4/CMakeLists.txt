set(EDX_SOURCES ../edx-io/src)

add_executable(ex_2_4   ${EDX_SOURCES}/edx-io.h
                        src/main.c)

target_include_directories(ex_2_4 PUBLIC ${EDX_SOURCES})

target_link_libraries(ex_2_4 LINK_PUBLIC edx_io)
