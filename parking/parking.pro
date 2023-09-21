TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        datamanager.cpp \
        graphics.cpp \
        init.cpp \
        main.cpp

HEADERS += \
    datamanager.h \
    graphics.h \
    init.h

unix|win32: LIBS += -lcurl
unix|win32: LIBS += -lgd

