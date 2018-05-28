TEMPLATE = app

CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_LFLAGS += -static
QMAKE_CXXFLAGS_RELEASE += -DNDEBUG

INCLUDEPATH += ../../src

CONFIG(release, debug|release) {
    LIBS += -L../../build-lgraph-release/ -llgraph
}
CONFIG(debug, debug|release) {
    LIBS += -L../../build-lgraph-debug/ -llgraph
}

HEADERS += \
    display.cpp \
    weighted_dist_paths.cpp \
    functions.hpp

SOURCES += \
    path-finding.cpp \
    unweighted_dist_paths.cpp
