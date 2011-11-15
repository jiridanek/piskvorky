SOURCES += \ #testnacitani.cpp \
    load.cpp \
    strategie_x.cpp \
  \  #strategie_prvnivolne.cpp \
    func.cpp \
    piskorky.cpp \
    minimax.cpp \
    game_tree/igametreenode.cc \
    game_tree/clocalgametreenode.cc \
    game_tree/cgametree.cc \
    board/cboard.cc \
    board/cmovegenerator.cc \
    board/smove.cc \
    main.cc \
    CAlfaBeta/calfabeta.cc
HEADERS += load.h \
    func.h \
    game_tree/igametreenode.h \
    game_tree/clocalgametreenode.h \
    game_tree/cgametree.h \
    board/cboard.h \
    board/cmovegenerator.h \
    board/smove.h \
    piskorky.h \
    CAlfaBeta/calfabeta.h \
    minimax.h \
    strategie_x.h

LIBS += -lrt

QMAKE_CXXFLAGS_DEBUG += -ggdb

QMAKE_CXXFLAGS_RELEASE = -O3




















