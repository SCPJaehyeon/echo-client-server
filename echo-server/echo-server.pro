TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -pthread

HEADERS += \
        header/echo-server.h

SOURCES += \
        cpp/main.cpp \
        cpp/echo-server.cpp \
