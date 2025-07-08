CONFIG += console
CONFIG -= app_bundle
QT = core websockets

TARGET = simple_test
TEMPLATE = app

SOURCES += simple_test.cpp \
    Lion.cpp \
    Animal.cpp \
    Aliment.cpp \
    AlimentsConcrets.cpp \
    AlimentManager.cpp \
    LionManager.cpp \
    WebSocketServer.cpp \
    WebSocketClient.cpp \
    EffectHandler.cpp

HEADERS += Lion.h \
    Animal.h \
    Aliment.h \
    AlimentsConcrets.h \
    AlimentManager.h \
    LionManager.h \
    WebSocketServer.h \
    WebSocketClient.h \
    EffectHandler.h

CONFIG += c++17
