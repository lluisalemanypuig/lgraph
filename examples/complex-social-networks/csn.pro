TEMPLATE = app

CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_LFLAGS += -static
QMAKE_CXXFLAGS_RELEASE += -DNDEBUG

INCLUDEPATH += ../..

CONFIG(release, debug|release) {
    LIBS += -L../../lgraph-release/ -llgraph
}
CONFIG(debug, debug|release) {
    LIBS += -L../../lgraph-debug/ -llgraph
}

SOURCES += \
    complex_social_networks.cpp \
    csn_utils.cpp

HEADERS += \
    csn_utils.hpp
