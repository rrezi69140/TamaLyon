CONFIG += testcase
QT += testlib websockets qml quick

TARGET = TestTamaLyon
TEMPLATE = app

# Sources de test
SOURCES += \
    TestTamaLyon.cpp

HEADERS += \
    TestTamaLyon.h

# Sources principales du projet à tester
SOURCES += \
    ../Lion.cpp \
    ../Animal.cpp \
    ../Aliment.cpp \
    ../AlimentsConcrets.cpp \
    ../AlimentManager.cpp \
    ../LionManager.cpp \
    ../WebSocketServer.cpp \
    ../WebSocketClient.cpp \
    ../EffectHandler.cpp

HEADERS += \
    ../Lion.h \
    ../Animal.h \
    ../Aliment.h \
    ../AlimentsConcrets.h \
    ../AlimentManager.h \
    ../LionManager.h \
    ../WebSocketServer.h \
    ../WebSocketClient.h \
    ../EffectHandler.h

# Configuration du compilateur
CONFIG += c++17

# Inclure les chemins
INCLUDEPATH += ..

# Configuration MOC
MOC_DIR = .
OBJECTS_DIR = .
