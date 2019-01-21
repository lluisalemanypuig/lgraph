TEMPLATE = app

CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG += -DDEBUG
QMAKE_CXXFLAGS_RELEASE += -DNDEBUG

# lgraph library
CONFIG(debug, debug|release) {
	LIBS += -L../../lgraph-debug/ -llgraph
	PRE_TARGETDEPS += ../../lgraph-debug/liblgraph.a
}
CONFIG(release, debug|release) {
	LIBS += -L../../lgraph-release/ -llgraph
	PRE_TARGETDEPS += ../../lgraph-release/liblgraph.a
}
INCLUDEPATH += ..
DEPENDPATH += ..

SOURCES += \
	src/main.cpp \
	src/parse_keywords.cpp \
	src/io_wrapper.cpp \
	src/test_utils.cpp \
	src/ux_path/ux_path_all_all__all.cpp \
	src/ux_path/ux_path_all_all__single.cpp \
	src/ux_path/ux_path_node_all__all.cpp \
	src/ux_path/ux_path_node_all__single.cpp \
	src/ux_path/ux_path_node_node__all.cpp \
	src/ux_path/ux_path_node_node__single.cpp \
	src/ux_dist/ux_dist_all_all__all.cpp \
	src/ux_dist/ux_dist_all_all__single.cpp \
	src/ux_dist/ux_dist_node_all__all.cpp \
	src/ux_dist/ux_dist_node_all__single.cpp \
	src/ux_dist/ux_dist_node_node__all.cpp \
	src/ux_dist/ux_dist_node_node__single.cpp

HEADERS += \
	src/definitions.hpp \
    src/parse_keywords.hpp \
    src/exe_tests.hpp \
	src/io_wrapper.hpp \
    src/test_utils.hpp

DISTFILES += \
