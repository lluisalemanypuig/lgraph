# Complex and Social Networks Algorithms

## Features of the example

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
	- Distance metrics:
		- Diameter
		- Mean vertex-vertex distance
		- Mean closeness centrality

+ To measure the importance of nodes (centrality measures)
	- Degree centrality
	- Closeness centrality

+ To simulate the spread of an infection over a network:
	- Model SIR
	- Model SIS

The project may be compiled using the qmake tool.

## Build the example

Once the library lgraph has been compiled following the instructions in the
main README.md file, while in the directory examples/ issue the following commands:

		mkdir csn-release
		qmake -makefile complex-social-networks/csn.pro -o csn-release/Makefile
		cd csn-release && make

## How to use it

1. See the complete usage issuing the command
	
		./csn --help
		
2. Generate a random network. In order to build a social network following the
Barabási-Albert model with Preferential Attachment, issue the specified command.
The other variants of the same model can be found in the usage.
	
		./csn --seed --barabasi-albert -pa --n0 10 --m0 4 --T 20
	
3. Applying the switching model to a network: use the option -sw and give
a value to Q to determine the number of steps of the switching model algorithm.
	
		./csn (..) -sw --Q 10 

4. Centrality and clustering metrics can be calculated if the appropriate
parameters are passed to the program.

		./csn (..) --gcc	: Global Clustering Coefficient (Newman 2010)
		./csn (..) --mlcc	: Mean Local Clustering Coefficient (Watts & Strogatz 1998)
		./csn (..) --dc		: degree centrality
		./csn (..) --cc		: closeness centrality

5. One can also execute the epidemic models on the generated network.
The selection of the model is done by adding --sir or --sis for the
SIR and SIS models. Their configuration is done in the same way:
	
		--p0 0.1 --beta 0.7 --gamma 0.55 --T-epidemics 1000
		
6. To simulate the SIR model, issue the command:
	
		./csn (..) --sir --p0 0.1 --beta 0.7 --gamma 0.55 --T-epidemics 1000
		
7. To simulate the SIS model, issue the command:
	
		./csn (..) --sis --p0 0.1 --beta 0.7 --gamma 0.55 --T-epidemics 1000
