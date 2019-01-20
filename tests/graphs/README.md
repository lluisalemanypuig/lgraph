# Graphs for testing

This directory contains the graphs used for testing. Now follows a
general description of the naming conventions:

- First comes the name of the graph. If it is a classical graph, like
a cycle graph, or a linear tree, it is usually followed by its number
of vertices, as we may want to have many graphs like these. For example,
a cycle graph of 8 vertices will be named: _cycle-8_.

- Type of structure: a graph can be weighted/unweighted and directed/undirected.
In the library, the different combinations of those two properties has
been codified as pairs. A similar convention is used here. For example,
an unweighted and undirected cycle graph of 8 vertices will be named:
_cycle-8-uu_. The meaning of the pairs are:
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
	- cycle-8-uu-00
	- cycle-8-uu-01
	- cycle-8-uu-02

- File extensions: the library will be extended to support several file
formats. Storing the same type of graph with the same structure and labelling
can be done by using different extensions. For example, the same graphs
listed above can be stored using the 'edge list' format by using the
extension _.el_. Also, we can use the extension _.graph6_ to use the
binary format _graph6_:
	- cycle-8-uu-00.el, cycle-8-uu-00.graph6
	- cycle-8-uu-01.el, cycle-8-uu-01.graph6
	- cycle-8-uu-02.el, cycle-8-uu-02.graph6
