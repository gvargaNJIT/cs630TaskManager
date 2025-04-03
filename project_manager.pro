QT += core gui widgets

CONFIG += c++17

TARGET = project_manager
TEMPLATE = app

SOURCES += src/main.cpp src/app.cpp src/list.cpp src/commands.cpp
HEADERS += include/app.h include/commands.h include/list.h

INCLUDEPATH += . 
LIBS += -lpthread
