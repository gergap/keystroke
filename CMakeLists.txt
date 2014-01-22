project(keystroke C)
cmake_minimum_required(VERSION 2.8)

add_executable(keystroke main.c keymap.c)

add_subdirectory(gui)

install(TARGETS keystroke
    DESTINATION bin
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                GROUP_EXECUTE GROUP_READ  SETUID)

