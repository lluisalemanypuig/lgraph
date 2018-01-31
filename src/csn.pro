
TEMPLATE = app

OBJECTS_DIR = ../bin
TARGET = ../csn

CONFIG += release
CONFIG += c++11
CONFIG -= qt

DEFINES -= QT_WEBKIT

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS_RELEASE -= -O -O1 -O2 -O3
QMAKE_CXXFLAGS_RELEASE += -Ofast

HEADERS +=												\
	data_structures/graph.hpp							\
	data_structures/random_generator.hpp				\
		data_structures/random_generator.cpp			\
		data_structures/drandom_generator.cpp			\
		data_structures/crandom_generator.cpp			\
	data_structures/random_generator.hpp				\
	data_structures/svector.hpp							\
		data_structures/svector.cpp						\
	random_graphs/barabasi_albert.hpp					\
		random_graphs/ba_preferential_attachment.cpp	\
		random_graphs/ba_random_attachment.cpp			\
		random_graphs/ba_no_vertex_growth.cpp			\
	random_graphs/switching.hpp							\
		random_graphs/switching.cpp						\
	metrics/clustering.hpp								\
	metrics/centralities.hpp							\
	epidemics/models.hpp								\
		epidemics/sir.cpp								\
		epidemics/sis.cpp

SOURCES +=							\
	complex_social_networks.cpp		\
	data_structures/graph.cpp		\
	metrics/clustering.cpp			\
	metrics/centralities.cpp
