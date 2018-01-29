# Complex and Social Networks Algorithms

## Contents of the repository

It includes a few algorithms for Complex and Social Networks:
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

+ To simulate the spread of an infection over a network:
	- Model SIR
	- Model SIS

The project may be compiled using the qmake tool.

## Examples of usage

+ Build a social network
	1. Compile the appropriate file
		- qmake -makefile csn.pro
		- make
		
	2. See the complete usage issuing the command
		- ./csn --help
		
	3. In order to build a social network following the Barabási-Albert
	model with Preferential Attachment, issue the specified command.
	The other variants of the same model can be found in the usage.
		- ./csn --seed -pa --n0 10 --m0 4 --T 20
	
	4. Applying the switching model is also easy: use the option -sw and give
	a value to Q to determine the number of steps of the switching model algorithm.
		- ./csn (..) -sw --Q 10 

	5. Centrality  and clustering metrics can be calculated if the appropriate
	parameters are passed to the program.
		- ./csn (..) --gcc		: Global Clustering Coefficient (Newman 2010)
		- ./csn (..) --mlcc		: Mean Local Clustering Coefficient (Watts & Strogatz 1998)
		- ./csn (..) --dc		: degree centrality

	6. One can also execute the epidemic models on the generated network.
	The selection of the model is done by adding --sir or --sis for the
	SIR and SIS models. Their configuration is done in the same way:
		- ./csn (..) --p0 0.1 --beta 0.7 --gamma 0.55 --T 1000
