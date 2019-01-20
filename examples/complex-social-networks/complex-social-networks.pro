TEMPLATE = app

CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG += -DDEBUG
QMAKE_CXXFLAGS_RELEASE += -DNDEBUG

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

SOURCES += \
	csn_utils.cpp \
	main.cpp

HEADERS += \
	csn_utils.hpp
