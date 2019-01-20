# General format

The general format of an input test file is simple:

	TYPE type
	INPUT n input_file_1 FORMAT_1 ... input_file_n FORMAT_n
	BODY body

## TYPE

This field MUST be the first in the file and contains a single string,
without spaces, with the tag of this test. This is the identifier of this
type of test. For example, if we wanted to test the algorithm for path
finding in unweighted graphs between two vertices of the graph, we could
write 

	TYPE unweighted-path-node-node

Then, the tester program would need to be modified so that it could
interpret what comes next.

The id of each test is made up of several "hyphenated" words. Each word
represents a category. In the example above the test is designed for
unweighted graphs, it is aimed at testing some path-finding algorithm,
particularly between pairs of nodes of a graph.

## INPUT

This field indicates the input files containing the necessary data to do
the test. Usually, these files will contain graphs describde in a certain
format. In order to indicate these input files we write:

- For three different input files

	INPUT 3 input_file_1 input_file_2 input_file_3

- For just one

	INPUT 1 input_file_1

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
	INPUT 1 big_graph
	BODY
		0 1
		1 2
		2 3
		4 5
		...

Therefore the BODY field is different for each test.

## All test types

The test types implemented so far are the following:

- For unweighted graphs:
	- Distances
	- Paths
		unweighted-path-node-node-single
		unweighted-path-node-node-all
		unweighted-path-node-all-single
		
- For weighted graphs:
	- Distances
	- Paths
