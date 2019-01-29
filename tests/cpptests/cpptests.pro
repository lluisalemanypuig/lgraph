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
INCLUDEPATH += ../..
DEPENDPATH += ../..

SOURCES += \
    main.cpp \
    parse_keywords.cpp \
    io_wrapper.cpp \
    test_utils.cpp \
    ux_path/ux_path_all_all.cpp \
    ux_path/ux_path_node_all.cpp \
    ux_path/ux_path_node_node.cpp \
    ux_dist/ux_dist_all_all.cpp \
    ux_dist/ux_dist_node_all.cpp \
    ux_dist/ux_dist_node_node.cpp \
    wx_dist/wx_dist_all_all.cpp \
    wx_dist/wx_dist_node_all.cpp \
    wx_dist/wx_dist_node_node.cpp \
    wx_path/wx_path_all_all.cpp \
    wx_path/wx_path_node_all.cpp \
    wx_path/wx_path_node_node.cpp \
    ux_metric/ux_metric_centrality.cpp \
    ux_metric/ux_metric_distance.cpp \
    wx_metric/wx_metric_centrality.cpp \
    wx_metric/wx_metric_distance.cpp \
    xu_metric/xu_metric_clustering.cpp \
    xd_metric/xd_metric_clustering.cpp

HEADERS += \
    definitions.hpp \
    parse_keywords.hpp \
    exe_tests.hpp \
    io_wrapper.hpp \
    test_utils.hpp

DISTFILES += \
