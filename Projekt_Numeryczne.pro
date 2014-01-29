TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    core.cpp


LIBS     += -lblas
LIBS     += -llapack

HEADERS += \
    import.h \
    core.h
