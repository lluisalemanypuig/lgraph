# Testing the library

The algorithms in this library are thoroughly tested during their development.
However, this was used to be done only once. It is our intention to
continue extending the library, but also to make the algorithms more efficient
every day. For this reason, we need automated tests that free us from the
burden of carrying out the thousands of tests need to be as completely sure
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

runs the tester executable with all the tests in the folder

	inputs/unweighted/undirected/paths

## Compilation of the tester

It is highly recommended that the tester be compiled in _debug_ mode.
For this, one can use the QtCreator tool.
