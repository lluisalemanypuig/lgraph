// C includes
#include <string.h>

// C++ includes
#include <iostream>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/wugraph.hpp>
#include <lgraph/data_structures/uugraph.hpp>

// Custom includes
#include "functions.hpp"
using namespace lgraph;
using namespace traversal;

void print_usage() {
	cout << "Path finding debugger" << endl;
	cout << "Finds:" << endl;
	cout << "    -> one path between a source and a target nodes" << endl;
	cout << "    -> all paths between a source and a target nodes" << endl;
	cout << "    -> one path between a source node and the rest of nodes" << endl;
	cout << "    -> all paths between a source node and the rest of nodes" << endl;
	cout << "    -> one path between all pairs of nodes in the graph" << endl;
	cout << "    -> all paths between all pairs of nodes in the graph" << endl;
	cout << endl;
	cout << "Options:" << endl;
	cout << "    [-h, --help]: prints this usage and exits" << endl;
	cout << "    --source: indicate source node" << endl;
	cout << "    --target: indicate target node" << endl;
	cout << "    [-i, --input]: indicate input file with the graph" << endl;
	cout << "    --weighted: indicate the graph is weighted" << endl;
	cout << "    --unweighted: indicate the graph is weighted" << endl;
	cout << endl;
}

int main(int argc, char *argv[]) {
	string file = "none";
	bool source_set;
	bool target_set;
	bool weighted;
	source_set = target_set = weighted = false;

	node S, T;
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-h") == 0 or strcmp(argv[i], "--help") == 0) {
			print_usage();
			return 0;
		}
		else if (strcmp(argv[i], "--source") == 0) {
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
		else if (strcmp(argv[i], "--weighted") == 0) {
			weighted = true;
		}
		else if (strcmp(argv[i], "--unweighted") == 0) {
			weighted = false;
		}
	}

	if (file == "none") {
		cerr << "No file specified!" << endl;
		return 1;
	}

	if (not source_set) {
		cerr << "Error: source not specified" << endl;
		return 1;
	}
	if (not target_set) {
		cerr << "Error: target not specified" << endl;
		return 1;
	}

	if (weighted) {
		cout << "Debugging weighted graphs" << endl;

		wugraph<float> G;

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

