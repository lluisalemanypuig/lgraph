# Testing the library

The algorithms in this library are thoroughly tested during their development.
However, this was used to be done only once. It is our intention to
continue extending the library, but also to make the algorithms more efficient
every day. For this reason, we need automated tests that free us from the
burden of carrying out the thousands of tests needed to be completely sure
that the algorithms work every time we make the slightest change.

Running the tests is simple. They have been classified into different
categories, each stored in a different folder within the main directory
_inputs_. The tester executable is run using a given test, and its output
is compared to the hand-made output stored in the directory _outputs_.

This procedure is automatised in the script _test.sh_. One can run it by
issuing the command:

	./test.sh --group=**

where _**_ is a string denoting the type of tests to be carried out. This
string, appended to _inputs/_ leads to folder containing all tests.
For example:

	./test.sh --group=unweighted/undirected/paths

runs the tester executable with all the tests in the directory

	inputs/unweighted/undirected/paths

## Compilation of the tester

It is highly recommended that the tester be compiled in _debug_ mode, in
order to make sure that no assertion fails. For this, issue the following
command:

	qmake -makefile tests.pro -o tests-debug/Makefile CONFIG+=debug

# Graphs for testing

This directory contains the graphs used for testing. Now follows a
general description of the naming conventions:

- First comes the name of the graph. If it is a classical graph, like
a cycle graph, or a linear tree, it is usually followed by its number
of vertices, as we may want to have many graphs like these. For example,
a cycle graph of 8 vertices will be named: _cycle-08_.

- Type of structure: a graph can be weighted/unweighted and directed/undirected.
In the library, the different combinations of those two properties has
been codified as pairs. A similar convention is used here. For example,
an unweighted and undirected cycle graph of 8 vertices will be named:
_cycle-08-uu_. The meaning of the pairs are:
	- _uu_: for unweighted and undirected
	- _ud_: for unweighted and directed
	- _wu_: for weighted and undirected
	- _wd_: for weighted and directed

- Thorough testing can be achieved by testing also that the algorithms
are independent of the labelling of the vertices of the graphs. If we wanted
to add the same graph but with different labellings, we will need different
names for the files. For this, we add yet another suffix to the name of
the file, that is a two-digit number (it is not likely that more than 100
different labellings of the same graph will ever be needed). For example,
we can add three different labellings of an unweighted and undirected cycle
graph of 8 vertices by naming the files as:
	- cycle-08-uu-00
	- cycle-08-uu-01
	- cycle-08-uu-02

- File extensions: the library will be extended to support several file
formats. Storing the same type of graph with the same structure and labelling
can be done by using different extensions. For example, the same graphs
listed above can be stored using the 'edge list' format by using the
extension _.el_:
	- cycle-08-uu-00.el
	- cycle-08-uu-01.el
	- cycle-08-uu-02.el

# Input files format

The general format of an input test file is simple:

	TYPE type
	INPUT n input_file_1 FORMAT_1 ... input_file_n FORMAT_n
	BODY body

## TYPE

This field MUST be the first in the file and contains a single string,
without spaces, with the tag of this test. This is the identifier of this
type of test. For example, if we wanted to test the algorithm for path
finding in unweighted undirected graphs between two vertices of the graph
then we write

	TYPE unweighted-undirected-path-node-node

Notice that for new tests, the tester program needs to be modified so that
it can interpret what comes next.

Therefore, the id of each test is made up of several "hyphenated" words.
Each word represents a category. In the example above the test is designed
for unweighted graphs, it is aimed at testing some path-finding algorithm,
particularly between pairs of nodes of a graph.

## INPUT

This field indicates the input files containing the necessary data to do
the test. Usually, these files will contain graphs describde in a certain
format. In order to indicate these input files we write:

- For three different input files

	INPUT 3 input_file_1 format_1 input_file_2 format_1 input_file_3

- For just one

	INPUT 1 input_file_1 format_1

The format of each file has to be given. The formats allowed are those
supported by the library:
- Edge list:	edge-list

Although other formats might be supported, they are not listed here due
to lack of proper debugging.

## BODY

This field is the most complicated of all, and it contains the instructions
necessary to perform the test. Following the example above, when testing
the path-finding algorithm in unweighted graphs, we might be interested
to find several paths at once. We could do this, for example, by writing
a list of 100 pairs:

	TYPE unweighted-path-node-node-single
	INPUT 1 big_graph edge_list
	BODY
		0 1
		1 2
		2 3
		4 5
		...

Therefore the 'BODY' field is different for each test. This means that some
tests may allow their 'BODY' field to be left empty.

## All test types

The test types implemented so far are the following:

- Distance finding:
	- unweighted-undirected-distance-node-node-single
	- unweighted-undirected-distance-node-node-all
	- unweighted-undirected-distance-node-all-single
	- unweighted-undirected-distance-node-all-all
	- unweighted-undirected-distance-all-all-single
	- unweighted-undirected-distance-all-all-all
	- unweighted-directed-distance-node-node-single
	- unweighted-directed-distance-node-node-all
	- unweighted-directed-distance-node-all-single
	- unweighted-directed-distance-node-all-all
	- unweighted-directed-distance-all-all-single
	- unweighted-directed-distance-all-all-all
	- weighted-undirected-distance-node-node-single
	- weighted-undirected-distance-node-node-all
	- weighted-undirected-distance-node-all-single
	- weighted-undirected-distance-node-all-all
	- weighted-undirected-distance-all-all-single
	- weighted-undirected-distance-all-all-all
	- weighted-directed-distance-node-node-single
	- weighted-directed-distance-node-node-all
	- weighted-directed-distance-node-all-single
	- weighted-directed-distance-node-all-all
	- weighted-directed-distance-all-all-single
	- weighted-directed-distance-all-all-all
- Path finding
	- unweighted-undirected-path-node-node-single
	- unweighted-undirected-path-node-node-all
	- unweighted-undirected-path-node-all-single
	- unweighted-undirected-path-node-all-all
	- unweighted-undirected-path-all-all-single
	- unweighted-undirected-path-all-all-all
	- unweighted-directed-path-node-node-single
	- unweighted-directed-path-node-node-all
	- unweighted-directed-path-node-all-single
	- unweighted-directed-path-node-all-all
	- unweighted-directed-path-all-all-single
	- unweighted-directed-path-all-all-all
	- weighted-undirected-path-node-node-single
	- weighted-undirected-path-node-node-all
	- weighted-undirected-path-node-all-single
	- weighted-undirected-path-node-all-all
	- weighted-undirected-path-all-all-single
	- weighted-undirected-path-all-all-all
	- weighted-directed-path-node-node-single
	- weighted-directed-path-node-node-all
	- weighted-directed-path-node-all-single
	- weighted-directed-path-node-all-all
	- weighted-directed-path-all-all-single
	- weighted-directed-path-all-all-all
