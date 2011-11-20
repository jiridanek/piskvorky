TEMPLATE = subdirs
SUBDIRS = common alphabetaparallel alphabeta strategie_x prvni_volne tests \
    alphabetaparallel \
    alphabetastack

prvni_volne.depends = common
alphabeta.depends = common
alphabetaparallel.depends = common
alphabetastack.depends = common
strategie_x.depends = common
tests.depends = common

include(flags.pri)

