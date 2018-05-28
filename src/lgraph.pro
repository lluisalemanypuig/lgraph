TEMPLATE = lib

CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_RELEASE += -DNDEBUG

HEADERS += \
    data_structures/xxgraph.hpp \
        data_structures/xxgraph.cpp \
        data_structures/uxgraph.hpp \
        data_structures/uxgraph.cpp \
        data_structures/uwgraph.hpp \
        data_structures/uwgraph.cpp \
        data_structures/uugraph.hpp \
    data_structures/node_path.hpp \
        data_structures/node_path.cpp \
    data_structures/boolean_path.hpp \
        data_structures/boolean_path.cpp \
    data_structures/random_generator.hpp \
        data_structures/random_generator.cpp \
        data_structures/drandom_generator.cpp \
        data_structures/crandom_generator.cpp \
    data_structures/svector.hpp \
        data_structures/svector.cpp \
    random_graphs/barabasi_albert.hpp \
        random_graphs/ba_preferential_attachment.cpp \
        random_graphs/ba_random_attachment.cpp \
        random_graphs/ba_no_vertex_growth.cpp \
    random_graphs/switching.hpp \
        random_graphs/switching.cpp \
    metrics/clustering.hpp \
    metrics/distance.hpp \
    metrics/centralities.hpp \
    epidemics/models.hpp \
        epidemics/sir.cpp \
        epidemics/sis.cpp \
    utils/logger.hpp \
    utils/definitions.hpp \
    utils/static_bitset.hpp \
    graph_traversal/traversal.hpp \
        graph_traversal/dfs.hpp \
        graph_traversal/dfs.cpp \
        graph_traversal/bfs.hpp \
        graph_traversal/bfs.cpp \
        graph_traversal/dijkstra.hpp \
        graph_traversal/dijkstra.cpp \
        graph_traversal/xwpaths.cpp \
        graph_traversal/xwdistances.cpp \
        graph_traversal/xwpaths_boolean.cpp

SOURCES += \
    metrics/clustering.cpp \
    metrics/centralities.cpp \
    metrics/distance.cpp \
    utils/static_bitset.cpp \
    data_structures/uugraph.cpp \
    graph_traversal/xudistances.cpp \
    graph_traversal/xupaths.cpp \
    graph_traversal/xupaths_boolean.cpp
