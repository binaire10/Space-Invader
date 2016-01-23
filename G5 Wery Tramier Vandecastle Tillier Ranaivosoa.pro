TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Correc_prof/spaceinavder_ml.cpp \
    Correc_prof/SpaceInvader_AC.cpp \
    Nos_fichiers/SpaceInvader.cpp \
    Nos_fichiers/readconfig.cpp

QMAKE_MAC_SDK = macosx10.11

HEADERS += \
    Correc_prof/MyConst_AC.h \
    Correc_prof/MyConst_ML.h \
    Correc_prof/MyType_AC.h \
    Correc_prof/MyType_ML.h \
    Correc_prof/SpaceInvader_AC.h \
    Correc_prof/SpaceInvader_ML.h \
    Nos_fichiers/MyConst.h \
    Nos_fichiers/MyType.h \
    Nos_fichiers/SpaceInvader.h \
    Nos_fichiers/readconfig.h
