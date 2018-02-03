
TEMPLATE = app

OBJECTS_DIR = bin
TARGET = csn-debug

CONFIG += debug
CONFIG += c++11
CONFIG -= qt

DEFINES -= QT_WEBKIT

QMAKE_CXXFLAGS += -std=c++0x

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
		epidemics/sis.cpp								\
	utils/logger.hpp

SOURCES +=							\
	complex_social_networks.cpp		\
	data_structures/graph.cpp		\
	metrics/clustering.cpp			\
	metrics/centralities.cpp
