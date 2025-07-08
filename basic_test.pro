CONFIG += console
CONFIG -= app_bundle
QT = core websockets testlib

TARGET = basic_test
TEMPLATE = app

SOURCES += basic_test.cpp \
    Lion.cpp \
    Animal.cpp \
    Aliment.cpp \
    AlimentsConcrets.cpp \
    WebSocketServer.cpp \
    WebSocketClient.cpp \
    EffectHandler.cpp

HEADERS += Lion.h \
    Animal.h \
    Aliment.h \
    AlimentsConcrets.h \
    WebSocketServer.h \
    WebSocketClient.h \
    EffectHandler.h

CONFIG += c++17
