project(keystroke-gui)
cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED QtCore QtGui QtDeclarative)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
include_directories(/usr/share/qt4/mkspecs/linux-g++)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(qmlapplicationviewer)
qt4_wrap_cpp(KEYSTROKE_MOC qmlapplicationviewer/qmlapplicationviewer.h keygrabber.h dialog.h file.h)
qt4_wrap_ui(KEYSTROKE_FORMS_HEADERS dialog.ui)
qt4_add_resources(KEYSTROKE_RCC_SRCS keystroke.qrc)

add_definitions(-DGUI)
add_executable(keystroke-gui ${KEYSTROKE_MOC} ${KEYSTROKE_RCC_SRCS} ${KEYSTROKE_FORMS_HEADERS}
    ../main.c ../keymap.c
    gui.cpp keygrabber.cpp dialog.cpp file.cpp
    qmlapplicationviewer/qmlapplicationviewer.cpp)
target_link_libraries(keystroke-gui ${QT_LIBRARIES})

install(TARGETS keystroke-gui
    DESTINATION bin
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                GROUP_EXECUTE GROUP_READ
                WORLD_EXECUTE WORLD_READ
                SETUID)

install(FILES qml/KeyStrokeOverlay.qml qml/Key.qml DESTINATION bin/qml)

