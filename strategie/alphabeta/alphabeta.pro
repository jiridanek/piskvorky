TARGET = alphabeta
SOURCES = main.cc
INCLUDEPATH += ../common
LIBS += -L../common -lcommon -lrt

include(../flags.pri)
