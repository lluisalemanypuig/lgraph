# Graph driver

This small, simple example provides a small program with which one can
manipulate all 4 types of graph implemented in the library (weighted/unweighted
directed/undirected graphs). It works by entering the appropriate commands
which affect some properties of the graph that is being manipulated (for
example: add or remove an edge, ask for the weight of such an edge - if
the graph is weighted -, ...).

## Build the example

Once the library lgraph has been compiled following the instructions in the
main [README.md](https://github.com/lluisalemanypuig/lgraph/blob/master/README.md)
file, while in the directory examples/ issue the following commands:

		mkdir graphs-driver-release
		qmake -makefile graphs-driver/graphs-driver.pro -o graphs-driver-release/Makefile
		cd graphs-driver-release && make

## How to use it

The usage is very simple. This example takes only two parameters:

- _--weighted_: indicate that the graph that will be manipulated is weighted
- _--unweighted_: indicate that the graph that will be manipulated is unweighted
- _--directed_: indicate that the graph that will be manipulated is directed
- _--undirected_: indicate that the graph that will be manipulated is undirected

Obviously, one can only use two of these parameters at a time: one of the
two _--weighted_/_--unweighted_, and one of the two _--directed_/_--undirected_.

The commands available for this driver can be seen by typing the 'help'
command while the driver is running:
		
		> help
		
The commands available when manipulating weighted graphs are different from
those available when manipulating unweighted graphs.
