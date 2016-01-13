HEADERS += \
    gameengine.h \
    test.h \
    sysgame.h \
    mytype.h \
    myconst.h \
    myfonctor.h \
    shadowclass.h \
    shadowoverloaded.h \
    shadowTool.h \
    configLoader.h \
    screengesture.h \
    lightinitilize.h \
    myscreentype.h

SOURCES += \
    main.cpp \
    gameengine.cpp \
    test.cpp \
    sysgame.cpp \
    configfile.cpp \
    shadowclass.cpp \
    shadowoverloaded.cpp \
    screengesture.cpp
CONFIG += console C++11

DEFINES +=

QMAKE_CXXFLAGS += -std=c++11
