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
    driver.hpp

SOURCES += \
    graph_driver.cpp \
    unweighted_driver.cpp \
    weighted_driver.cpp
