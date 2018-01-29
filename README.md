# Complex and Social Networks Algorithms

## Contents of the repository

It includes a few Social and Complex Network algorithms:
+ To generate random graphs:
	- Barabasi-Albert model: this includes the variants:
		- Preferential attachment
		- Random attachment
		- No vertex growth

+ To modify networks:
	- Switching model

+ To quantify properties of networks:
	- Clustering metrics:
		- Newman's global clustering coefficient
		- Watts & Strogatz's mean local clustering coefficient

+ To measure the importance of nodes (centralities)
	- Degree centrality

The project may be compiled using the qmake tool.

## Example of usage

+ Build a social network
	1. Compile the appropriate file
		- qmake -makefile make_random_graphs.pro
		- make
	2. See the complete usage issuing the command
		./make_random_graphs --help
	3. In order to build a social network following the Barabási-Albert
	model with Preferential Attachment, issue the command
		./make_random_graphs --seed -pa --n0 10 --m0 4 -T 20
	4. Applying the switching model is also easy
		./make_random_graphs --seed -pa --n0 10 --m0 4 -T 20 -sw -Q 10
	where Q is an optional parameter that determines the number of steps
	of the switching model algorithm.
