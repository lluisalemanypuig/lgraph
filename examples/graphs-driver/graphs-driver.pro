TEMPLATE = app

CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG += -DDEBUG -g
QMAKE_CXXFLAGS_RELEASE += -DNDEBUG

HEADERS +=					\
	driver.hpp				\
    time.hpp

SOURCES +=					\
	graphs_driver.cpp		\
	unweighted_driver.cpp	\
	weighted_driver.cpp		\
    time.cpp

# lgraph library
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lgraph-release/ -llgraph
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lgraph-debug/ -llgraph
else:unix: LIBS += -L$$PWD/../../lgraph-debug/ -llgraph

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lgraph-release/liblgraph.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lgraph-debug/liblgraph.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lgraph-release/lgraph.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lgraph-debug/lgraph.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../lgraph-debug/liblgraph.a
