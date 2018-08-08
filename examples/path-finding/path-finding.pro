TEMPLATE = app

CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_LFLAGS += -static
QMAKE_CXXFLAGS_RELEASE += -DNDEBUG

INCLUDEPATH += ../..

CONFIG(debug, debug|release) {
    LIBS += -L../../lgraph-debug/ -llgraph
}
CONFIG(release, debug|release) {
    LIBS += -L../../lgraph-release/ -llgraph
}

HEADERS += \
    display.cpp \
    weighted_dist_paths.cpp \
    functions.hpp

SOURCES += \
    unweighted_dist_paths.cpp \
    path_finding.cpp
