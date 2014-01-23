project(keystroke-gui)
cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED QtCore QtGui QtDeclarative)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
include_directories(/usr/share/qt4/mkspecs/linux-g++)

include_directories(qmlapplicationviewer)
qt4_wrap_cpp(KEYSTROKE_MOC qmlapplicationviewer/qmlapplicationviewer.h keygrabber.h dialog.h)

qt4_add_resources(KEYSTROKE_RCC_SRCS keystroke.qrc)

add_definitions(-DGUI)
add_executable(keystroke-gui ${KEYSTROKE_MOC} ${KEYSTROKE_RCC_SRCS} ../main.c ../keymap.c
    gui.cpp keygrabber.cpp dialog.cpp
    qmlapplicationviewer/qmlapplicationviewer.cpp)
target_link_libraries(keystroke-gui ${QT_LIBRARIES})

install(TARGETS keystroke-gui
    DESTINATION bin
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                GROUP_EXECUTE GROUP_READ
                WORLD_EXECUTE WORLD_READ
                SETUID)

install(FILES qml/KeyStrokeOverlay.qml qml/Key.qml DESTINATION bin/qml)

file(GLOB PNG_FILES "png/*.png")
install(FILES ${PNG_FILES} DESTINATION bin/png)

