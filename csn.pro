
TEMPLATE = app

OBJECTS_DIR = bin
TARGET = csn

CONFIG += release
CONFIG += c++11
CONFIG -= qt

DEFINES -= QT_WEBKIT

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS_RELEASE -= -O -O1 -O2 -O3
QMAKE_CXXFLAGS_RELEASE += -Ofast

HEADERS +=													\
    src/graph.hpp											\
    src/random_generator.hpp								\
        src/random_generator.cpp							\
        src/drandom_generator.cpp							\
        src/crandom_generator.cpp							\
    src/random_graphs/barabasi_albert.hpp					\
        src/random_graphs/ba_preferential_attachment.cpp	\
        src/random_graphs/ba_random_attachment.cpp			\
        src/random_graphs/ba_no_vertex_growth.cpp			\
    src/random_graphs/switching.hpp							\
        src/random_graphs/switching.cpp						\
    src/metrics/clustering.hpp								\
    src/metrics/centralities.hpp							\
    src/epidemics/models.hpp								\
		src/epidemics/sir.cpp								\
		src/epidemics/sis.cpp

SOURCES +=							\
    complex_social_networks.cpp		\
    src/graph.cpp					\
    src/metrics/clustering.cpp		\
    src/metrics/centralities.cpp
