TEMPLATE = subdirs
SUBDIRS = common alphabeta strategie_x prvni_volne tests

prvni_volne.depends = common
alphabeta.depends = common
strategie_x.depends = common
tests.depends = common

QMAKE_CXXFLAGS_DEBUG += -ggdb

QMAKE_CXXFLAGS_RELEASE = -O3
