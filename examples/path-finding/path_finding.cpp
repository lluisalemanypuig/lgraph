// C includes
#include <string.h>

// C++ includes
#include <iostream>
using namespace std;

// Custom includes
#include "functions.hpp"
using namespace lgraph;
using namespace traversal;

int main(int argc, char *argv[]) {
	string file = "none";
	bool source_set, target_set, weighted;
	source_set = target_set = weighted = false;

	node S, T;
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "--source") == 0) {
			S = atoi(argv[i + 1]);
			source_set = true;
			++i;
		}
		else if (strcmp(argv[i], "--target") == 0) {
			T = atoi(argv[i + 1]);
			target_set = true;
			++i;
		}
		else if (strcmp(argv[i], "-i") == 0 or strcmp(argv[i], "--input") == 0) {
			file = string(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "-w") == 0 or strcmp(argv[i], "--weighted") == 0) {
			weighted = true;
		}
	}

	if (file == "none") {
		cerr << "No file specified!" << endl;
		return 1;
	}

	if (not source_set or not target_set) {
		cerr << "Error: source or target not specified" << endl;
		return 1;
	}

	if (weighted) {
		cout << "Debugging weighted graphs" << endl;

		uwgraph<float> G;

		G.read_from_file(file);
		cout << "graph read:" << endl;
		cout << G << endl;
		cout << endl;

		functions::deb_distances_t(&G, S, T);
		functions::deb_paths_t(&G, S, T);
		functions::deb_all_paths_t(&G, S, T);
		functions::deb_bpaths_t(&G, S, T);
		functions::deb_all_bpaths_t(&G, S, T);
	}
	else {
		cout << "Debugging unweighted graphs" << endl;

		uugraph G;

		G.read_from_file(file);
		cout << "graph read:" << endl;
		cout << G << endl;
		cout << endl;

		functions::deb_distances(&G, S, T);
		functions::deb_paths(&G, S, T);
		functions::deb_all_paths(&G, S, T);
		functions::deb_bpaths(&G, S, T);
		functions::deb_all_bpaths(&G, S, T);
	}
}

