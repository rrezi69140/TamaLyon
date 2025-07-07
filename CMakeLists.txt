cmake_minimum_required(VERSION 3.16)

project(TAMALYON VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core WebSockets)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appTAMALYON
    main.cpp
    LionManager.cpp
    LionManager.h
    WebSocketServer.cpp
    WebSocketServer.h
    WebSocketClient.cpp
    WebSocketClient.h
    Aliment.cpp
    Aliment.h
    Animal.cpp
    Animal.h
    Lion.cpp
    Lion.h
    AlimentsConcrets.cpp
    AlimentsConcrets.h
    AlimentManager.cpp
    AlimentManager.h
    EffectHandler.cpp
    EffectHandler.h
)

qt_add_resources(appTAMALYON "qml"
    PREFIX "/"
    FILES
        Main.qml
        MainOOP.qml
        MainSimple.qml
        LyonFace.qml
        DraggableIcon.qml
        DraggableAliment.qml
        MoodBar.qml
        FILES/lion_affame.png
        FILES/lion_endormi.png
        FILES/lion_tres_content.png
        FILES/lion_triste.png
)

set_target_properties(appTAMALYON PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTAMALYON
    PRIVATE Qt6::Quick Qt6::Core Qt6::WebSockets
)

include(GNUInstallDirs)
install(TARGETS appTAMALYON
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
