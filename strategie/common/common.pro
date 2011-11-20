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
    minimax.cpp \
    alphabeta/calfabeta.cc \
    alphabeta/calphabetaparallel.cc \
    alphabeta/calphabetastack.cc \
    game_tree/clocalgametreenode.cc \
    game_tree/cgametree.cc
HEADERS += load.h \
    func.h \
    board/cboard.h \
    board/cmovegenerator.h \
    board/smove.h \
    piskorky.h \
    strategie_x.h \
    minimax.h \
    alphabeta/calfabeta.h \
    alphabeta/calphabetaparallel.h \
    alphabeta/calphabetastack.h \
    game_tree/clocalgametreenode.h \
    game_tree/cgametree.h
LIBS += -lrt

include(../flags.pri)


