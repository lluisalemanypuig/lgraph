# light-Graph (lgraph) library

lgraph is a light-weight library that contains a number of algorithms for Complex and Social networks.
It also implements algorithms on shortest-path finding, two types of graphs (undirected, weighted and
unweighted) graphs, and algorithms to find the value of several network metrics.

## Documentation

The documentation can be generated using Doxygen (version >= 1.8.11) by ussing the following commands

		cd /path/to/the/repository
		doxygen doxygen/doxyconfig

## Contents of the repository

Apart from the library with the algorithms, there are several examples showing how to use the library:

- [examples/complex-social-networks](https://github.com/lluisalemanypuig/lgraph/tree/master/examples/complex-social-networks):
contains a small project that compiles a simple driver for generating
social networks. The ones available are the ones specified in the lgraph::networks::random namespace
(several variants of the Barabasi-Albert model, the Switching model, and others).

- [examples/path-finding](https://github.com/lluisalemanypuig/lgraph/tree/master/examples/path-finding):
contains examples on how to use all the different path-finding functions
implemented. Shortest path in unweighted and weighted graphs between two pairs of nodes, adhoc
algorithms for finding shortest paths between a given node and all the other nodes in the graph,
and between any pair of nodes.

- [examples/graph-driver](https://github.com/lluisalemanypuig/lgraph/tree/master/examples/graphs-driver):
contains examples on how to call several functions of the library through a simple command-line
driver. It is mainly used for debugging.

Each example contains a README.md file detailing the contents, including their compilation.

## Dependencies

### Tools

In order to compile the library and the examples, it is required to have the
'qmake' tool in order to generate the Makefiles. Then, the 'make' tool is needed to
actually compile them.

Finally, a compiler that supports C++11 is mandatory.

## Compiling

The library is meant to be compiled for static compilation. In order to compile it issue the following
commands:

		cd /path/to/the/repository
		mkdir lgraph-release
		qmake -makefile lgraph/lgraph.pro -o lgraph-release/Makefile
		cd lgraph-release && make

This will generate the .a file necessary for static compilation.

