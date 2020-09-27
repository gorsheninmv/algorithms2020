set(EDX_SOURCES ../edx-io/src)

add_executable(ex_2_2   ${EDX_SOURCES}/edx-io.h
                        src/main.c)

target_include_directories(ex_2_2 PUBLIC ${EDX_SOURCES})

target_link_libraries(ex_2_2 LINK_PUBLIC edx_io)
