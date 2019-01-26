TEMPLATE = lib

CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

QMAKE_CXXFLAGS_DEBUG += -DDEBUG -g
QMAKE_CXXFLAGS_RELEASE += -DNDEBUG
INCLUDEPATH += ..

HEADERS += \
    data_structures/xxgraph.hpp \
    data_structures/wxgraph.hpp \
    data_structures/wxgraph.cpp \
    data_structures/wugraph.hpp \
    data_structures/wugraph.cpp \
    data_structures/wdgraph.cpp \
    data_structures/wdgraph.hpp \
    data_structures/uxgraph.hpp \
    data_structures/uugraph.hpp \
    data_structures/udgraph.hpp \
    data_structures/node_path.hpp \
    data_structures/node_path.cpp \
    data_structures/boolean_path.hpp \
    data_structures/boolean_path.cpp \
    generate_graphs/classic/classic.hpp \
    generate_graphs/classic/regular.hpp \
    generate_graphs/random/erdos_renyi.hpp \
    generate_graphs/random/erdos_renyi.cpp \
    generate_graphs/random/barabasi_albert.hpp \
    generate_graphs/random/ba_preferential_attachment.cpp \
    generate_graphs/random/ba_random_attachment.cpp \
    generate_graphs/random/ba_no_vertex_growth.cpp \
    generate_graphs/random/watts_strogatz.hpp \
    generate_graphs/random/watts_strogatz.cpp \
    generate_graphs/switching.hpp \
    generate_graphs/switching.cpp \
    epidemics/models.hpp \
    epidemics/sir.cpp \
    epidemics/sir_immune.cpp \
    epidemics/sis.cpp \
    epidemics/sis_immune.cpp \
    graph_traversal/dfs.hpp \
    graph_traversal/bfs.hpp \
    graph_traversal/dijkstra.hpp \
    graph_traversal/dijkstra.cpp \
    utils/logger.hpp \
    utils/definitions.hpp \
    utils/static_bitset.hpp \
    communities/communities.hpp \
    io/io.hpp \
    io/gsd6.hpp \
    utils/svector.hpp \
    utils/svector.cpp \
    utils/random_generator.hpp \
    utils/random_generator.cpp \
    utils/drandom_generator.cpp \
    utils/crandom_generator.cpp \
    graph_traversal/traversal_wx.hpp \
    graph_traversal/traversal_ux.hpp \
    metrics/centralities_ux.hpp \
    metrics/centralities_wx.hpp \
    graph_traversal/distances_wx.cpp \
    graph_traversal/paths_wx.cpp \
    graph_traversal/paths_boolean_wx.cpp \
    metrics/clustering_ux.hpp \
    metrics/clustering_wx.hpp \
    metrics/distance_ux.hpp \
    metrics/distance_wx.hpp \
    metrics/centralities_wx.cpp \
    metrics/clustering_wx.cpp \
    metrics/distance_wx.cpp \
    io/edge_list_ux.hpp \
	io/edge_list_wx.hpp \
	io/edge_list_wx.cpp

SOURCES += \
    utils/static_bitset.cpp \
    data_structures/xxgraph.cpp \
    data_structures/uxgraph.cpp \
    data_structures/uugraph.cpp \
    data_structures/udgraph.cpp \
    graph_traversal/bfs.cpp \
    graph_traversal/dfs.cpp \
    generate_graphs/classic/linear_tree.cpp \
    generate_graphs/classic/star_graph.cpp \
    generate_graphs/classic/cycle_graph.cpp \
    generate_graphs/classic/complete_graph.cpp \
    generate_graphs/classic/regular.cpp \
    communities/connected_components.cpp \
    io/graph6.cpp \
    io/sparse6.cpp \
    io/digraph6.cpp \
    io/gsd6.cpp \
    graph_traversal/distances_ux.cpp \
    graph_traversal/paths_ux.cpp \
    graph_traversal/paths_boolean_ux.cpp \
    metrics/distance_ux.cpp \
    metrics/centralities_ux.cpp \
    metrics/clustering_ux.cpp \
	io/edge_list_ux.cpp


