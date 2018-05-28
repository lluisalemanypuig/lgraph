# Path finding Algorithms

## Features of the example

It includesa series of calls to a number of path-finding algorithms, for undirected
graphs. Both weighted and unweighted versions of a graph are allowed. The algorithms
called are the necessary variants of a Breadth-First search algorithm (for the
case of unweighted graphs), the necessary variants of Dijkstra's algorithm
for shortest-path finding (for the case of weighted graphs), and, last but not
least, the necessary variants of the Floyd-Warshall's algorithm for _all-to-all_
shortest distance/path finding.

## Build the example

Once the library lgraph has been compiled following the instructions in the
main README.md file, while in the directory examples/ issue the following commands:

		mkdir build-path-finding
		qmake -makefile path-finding/path-finding.pro -o build-path-finding/Makefile
		cd build-path-finding && make

## How to use it

The usage is very simple. This example takes only four parameters:

- _[-i, --input] file_: indicate the file where the graph is stored
- _source_, _--target_: indicate the source and target for node-node shortest
paths.
- _[-w, --weighted]_: indicate whether the input graph is weighted or not.

## Displayed information

The amount of displayed information for any input graph is quite large. Here follows
a rough description of it.

### Distances

For any graph, it is first displayed several distance values: first, the shortest
distance between the source and target nodes. Then, the distance between the source
node and all the other nodes in the graph, and, finally, the shortest distance
between each pair of nodes in the graph.

### Paths

Then follows the paths found between several pairs of nodes. This information is
repeated as the example first finds these paths as 'node_paths' and then as
'boolean_paths'. Therefore, it is first displayed one of the shortest paths between
the source and target nodes. Then, one of the shortest path between the source node
and all the other nodes of the graph. Finally, it is displayed one of the shortest
paths between each pair of nodes of the graph.

The next information displayed are all the shortest paths between the source and
target nodes, between the source and all the other nodes in the graph, and between
each pair of nodes in the graph.
	
