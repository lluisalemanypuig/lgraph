TEMPLATE = lib

CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

QMAKE_CXXFLAGS_RELEASE += -DNDEBUG
INCLUDEPATH += ..

HEADERS += \
    data_structures/xxgraph.hpp \
        data_structures/wxgraph.hpp \
        data_structures/wxgraph.cpp \
        data_structures/wugraph.hpp \
        data_structures/wugraph.cpp \
        data_structures/uxgraph.hpp \
        data_structures/uugraph.hpp \
        data_structures/udgraph.hpp \
        data_structures/wdgraph.cpp \
        data_structures/wdgraph.hpp \
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
    generate_graphs/classic/classic.hpp \
    generate_graphs/social/erdos_renyi.hpp \
        generate_graphs/social/erdos_renyi.cpp \
    generate_graphs/social/barabasi_albert.hpp \
        generate_graphs/social/ba_preferential_attachment.cpp \
        generate_graphs/social/ba_random_attachment.cpp \
        generate_graphs/social/ba_no_vertex_growth.cpp \
    generate_graphs/switching.hpp \
        generate_graphs/switching.cpp \
    metrics/clustering.hpp \
        metrics/wclustering.cpp \
    metrics/distance.hpp \
        metrics/wdistance.cpp \
    metrics/centralities.hpp \
        metrics/wcentralities.cpp \
    epidemics/models.hpp \
        epidemics/sir.cpp \
        epidemics/sir_immune.cpp \
        epidemics/sis.cpp \
        epidemics/sis_immune.cpp \
    graph_traversal/traversal.hpp \
        graph_traversal/dfs.hpp \
        graph_traversal/bfs.hpp \
        graph_traversal/dijkstra.hpp \
        graph_traversal/dijkstra.cpp \
        graph_traversal/wxdistances.cpp \
        graph_traversal/wxpaths.cpp \
        graph_traversal/wxpaths_boolean.cpp \
    utils/logger.hpp \
    utils/definitions.hpp \
    utils/static_bitset.hpp

SOURCES += \
    utils/static_bitset.cpp \
    metrics/uclustering.cpp \
    metrics/udistance.cpp \
    metrics/ucentralities.cpp \
    data_structures/xxgraph.cpp \
    data_structures/uxgraph.cpp \
    data_structures/uugraph.cpp \
    data_structures/udgraph.cpp \
    graph_traversal/bfs.cpp \
    graph_traversal/dfs.cpp \
    graph_traversal/uxdistances.cpp \
    graph_traversal/uxpaths.cpp \
    graph_traversal/uxpaths_boolean.cpp \
    generate_graphs/classic/linear_tree.cpp \
    generate_graphs/classic/star_graph.cpp \
    generate_graphs/classic/cycle_graph.cpp \
    generate_graphs/classic/complete_graph.cpp


