
TEMPLATE = app

OBJECTS_DIR = bin
TARGET = random_graphs

CONFIG += release
CONFIG += c++11
CONFIG -= qt

QMAKESPEC =
DEFINES -= QT_WEBKIT

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS_RELEASE -= -O -O1 -O2 -O3
QMAKE_CXXFLAGS_RELEASE += -Ofast

HEADERS +=									\
	src/digraph.hpp							\
	src/random_generator.hpp				\
		src/random_generator.cpp			\
		src/drandom_generator.cpp			\
	src/barabasi_albert.hpp					\
		src/rg_preferential_attachment.cpp	\
		src/rg_random_attachment.cpp		\
		src/rg_no_vertex_growth.cpp

SOURCES +=				\
	random_graphs.cpp	\
	src/digraph.cpp
