QT += core websockets qml
CONFIG += c++17

TARGET = test_unit_aliment
TEMPLATE = app

SOURCES += test_unit_aliment.cpp \
    LionManager.cpp \
    AlimentManager.cpp \
    Lion.cpp \
    Animal.cpp \
    Aliment.cpp \
    AlimentsConcrets.cpp \
    EffectHandler.cpp \
    WebSocketServer.cpp \
    WebSocketClient.cpp

HEADERS += LionManager.h \
    AlimentManager.h \
    Lion.h \
    Animal.h \
    Aliment.h \
    AlimentsConcrets.h \
    EffectHandler.h \
    WebSocketServer.h \
    WebSocketClient.h
