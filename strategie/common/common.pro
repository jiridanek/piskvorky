TEMPLATE = lib
CONFIG = staticlib

SOURCES += \ #testnacitani.cpp \
    load.cpp \
    func.cpp \
    piskorky.cpp \
    board/cboard.cc \
    board/cmovegenerator.cc \
    board/smove.cc \
    strategie_x.cc \
    minimax.cpp
HEADERS += load.h \
    func.h \
    board/cboard.h \
    board/cmovegenerator.h \
    board/smove.h \
    piskorky.h \
    strategie_x.h \
    minimax.h
LIBS += -lrt


