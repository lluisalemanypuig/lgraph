
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    data_structures/graph.hpp \
    data_structures/random_generator.hpp \
        data_structures/random_generator.cpp \
        data_structures/drandom_generator.cpp \
        data_structures/crandom_generator.cpp \
    data_structures/random_generator.hpp \
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
    graph_traversal/traversal.hpp

SOURCES += \
    complex_social_networks.cpp \
    data_structures/graph.cpp \
    metrics/clustering.cpp \
    metrics/centralities.cpp \
    metrics/distance.cpp \
    graph_traversal/bfs.cpp \
    graph_traversal/graph_distances.cpp \
    graph_traversal/graph_paths.cpp

DISTFILES += \
    update-to-master \
    TODO
