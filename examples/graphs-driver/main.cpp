// C includes
#include <string.h>

// C++ includes
#include <iostream>
using namespace std;

// Custom includes
#include "driver.hpp"

#include <lgraph/data_structures/xxgraph.hpp>
#include <lgraph/data_structures/wxgraph.hpp>
#include <lgraph/data_structures/wugraph.hpp>
#include <lgraph/data_structures/wdgraph.hpp>
#include <lgraph/data_structures/uxgraph.hpp>
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>

int main(int argc, char *argv[]) {
	bool directed = false;
	bool weighted = false;

	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "--weighted") == 0) {
			weighted = true;
		}
		else if (strcmp(argv[i], "--unweighted") == 0) {
			weighted = false;
		}
		else if (strcmp(argv[i], "--directed") == 0) {
			directed = true;
		}
		else if (strcmp(argv[i], "--undirected") == 0) {
			directed = false;
		}
		else {
			cerr << "Error: option not recognised" << endl;
			return 1;
		}
	}

	if (weighted) {
		cout << "Execute driver for weighted graphs" << endl;
		graph_driver::driver_weighted(directed);
	}
	else {
		cout << "Execute driver for unweighted graphs" << endl;
		graph_driver::driver_unweighted(directed);
	}
}
