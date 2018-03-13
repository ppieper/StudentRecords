TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    StudentDatabase.cpp \
    StudentApp.cpp

HEADERS += \
    StudentRecord.h \
    StudentDatabase.h \
    StudentApp.h
