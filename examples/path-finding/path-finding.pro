TEMPLATE = app

CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG += -DDEBUG
QMAKE_CXXFLAGS_RELEASE += -DNDEBUG

HEADERS += \
	display.cpp \
	weighted_dist_paths.cpp \
    functions.hpp

SOURCES += \
	unweighted_dist_paths.cpp \
    main.cpp

# lgraph library
CONFIG(debug, debug|release) {
	LIBS += -L../../../lgraph-debug/ -llgraph
	PRE_TARGETDEPS += ../../../lgraph-debug/liblgraph.a
}
CONFIG(release, debug|release) {
	LIBS += -L../../../lgraph-release/ -llgraph
	PRE_TARGETDEPS += ../../../lgraph-release/liblgraph.a
}
INCLUDEPATH += ../..
DEPENDPATH += ../..
