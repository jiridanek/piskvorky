TARGET = prvni_volne
SOURCES = strategie_prvnivolne.cpp \
    main.cc
INCLUDEPATH += ../common
LIBS += -L../common -lcommon

include(../flags.pri)

