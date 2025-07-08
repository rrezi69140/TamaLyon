cmake_minimum_required(VERSION 3.16)

project(TAMALYON VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core WebSockets)

qt_standard_project_setup(REQUIRES 6.8)

# Définir les dossiers d'inclusion
include_directories(src src/core src/managers src/network)

qt_add_executable(appTAMALYON
    main.cpp
    
    # Core - Logique métier
    src/core/Animal.cpp
    src/core/Animal.h
    src/core/Lion.cpp
    src/core/Lion.h
    src/core/Aliment.cpp
    src/core/Aliment.h
    src/core/AlimentsConcrets.cpp
    src/core/AlimentsConcrets.h
    src/core/EffectHandler.cpp
    src/core/EffectHandler.h
    
    # Managers - Gestion de l'état
    src/managers/LionManager.cpp
    src/managers/LionManager.h
    src/managers/AlimentManager.cpp
    src/managers/AlimentManager.h
    
    # Network - Communication réseau
    src/network/WebSocketServer.cpp
    src/network/WebSocketServer.h
    src/network/WebSocketClient.cpp
)

# Utiliser le fichier qml.qrc existant
qt_add_resources(appTAMALYON "qml_resources"
    FILES
        qml.qrc
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
