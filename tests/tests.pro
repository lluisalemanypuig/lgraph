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
    src/ux_path/ux_path_all_all.cpp \
    src/ux_path/ux_path_node_all.cpp \
    src/ux_path/ux_path_node_node.cpp \
    src/ux_dist/ux_dist_all_all.cpp \
    src/ux_dist/ux_dist_node_all.cpp \
    src/ux_dist/ux_dist_node_node.cpp \
    src/wx_dist/wx_dist_all_all.cpp \
    src/wx_dist/wx_dist_node_all.cpp \
    src/wx_dist/wx_dist_node_node.cpp \
    src/wx_path/wx_path_all_all.cpp \
    src/wx_path/wx_path_node_all.cpp \
    src/wx_path/wx_path_node_node.cpp \
    src/ux_metric/ux_metric_centrality.cpp \
    src/ux_metric/ux_metric_clustering.cpp \
    src/ux_metric/ux_metric_distance.cpp \
    src/wx_metric/wx_metric_centrality.cpp \
    src/wx_metric/wx_metric_clustering.cpp \
    src/wx_metric/wx_metric_distance.cpp

HEADERS += \
	src/definitions.hpp \
    src/parse_keywords.hpp \
    src/exe_tests.hpp \
	src/io_wrapper.hpp \
    src/test_utils.hpp

DISTFILES += \
