TARGET = tests
SOURCES = ./*.cc
INCLUDEPATH += ../common
LIBS += -L../common -lcommon

CONFIG +=link_pkgconfig
PKGCONFIG = unittest++
