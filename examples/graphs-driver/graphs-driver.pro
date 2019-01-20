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

HEADERS += \
	driver.hpp \
    time.hpp

SOURCES += \
	unweighted_driver.cpp \
	weighted_driver.cpp \
    time.cpp \
    main.cpp
