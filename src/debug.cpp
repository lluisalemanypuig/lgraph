/// C includes
#include <string.h>

/// C++ includes
#include <iostream>
using namespace std;

/// Custom includes
#include "debug/debug.hpp"
using namespace dsa;
using namespace traversal;

int debug_path_finding(int argc, char *argv[]) {
	string file = "none";
	bool weighted = false;

	node S, T;
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "--source") == 0) {
			S = atoi(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "--target") == 0) {
			T = atoi(argv[i + 1]);
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

	if (weighted) {
		uwgraph<float> G;

		G.read_from_file(file);
		cout << "graph read:" << endl;
		cout << G << endl;
		cout << endl;

		debug::deb_distances_t(&G, S, T);
		debug::deb_paths_t(&G, S, T);
		//debug::deb_all_paths(G, S, T);

		//debug::deb_bpaths(G, S, T);
		//debug::deb_all_bpaths(G, S, T);
	}
	else {
		uugraph G;

		G.read_from_file(file);
		cout << "graph read:" << endl;
		cout << G << endl;
		cout << endl;

		debug::deb_distances(&G, S, T);
		debug::deb_paths(&G, S, T);
		debug::deb_all_paths(&G, S, T);
		debug::deb_bpaths(&G, S, T);
		debug::deb_all_bpaths(&G, S, T);
	}

	return 0;
}

void debug_graphs() {
	uwgraph<float> Gw;
	uugraph Gu;

	Gw.init(10);
	Gu.init(10);

	string g, filename, option;
	cin >> g;

	size_t u, v;
	float w;

	while (cin >> option and option != "exit") {
		if (option == "add-edge") {
			cin >> u >> v;
			if (g == "weighted") {
				cin >> w;
				Gw.add_edge(u, v, w);
			}
			else {
				Gu.add_edge(u, v);
			}
		}
		else if (option == "remove-edge") {
			cin >> u >> v;
			if (g == "weighted") {
				Gw.remove_edge(u, v);
			}
			else {
				Gu.remove_edge(u, v);
			}
		}
		else if (option == "get-weight") {
			cin >> u >> v;
			if (g == "weighted") {
				cout << Gw.edge_weight(u, v) << endl;
			}
			else {
				cout << Gu.edge_weight(u, v) << endl;
			}
		}
		else if (option == "store") {
			cin >> filename;
			if (g == "weighted") {
				Gw.store_in_file(filename);
			}
			else {
				Gu.store_in_file(filename);
			}
		}
		else if (option == "read") {
			cin >> filename;
			if (g == "weighted") {
				Gw.read_from_file(filename);
			}
			else {
				Gu.read_from_file(filename);
			}
		}
		else if (option == "print") {
			if (g == "weighted") {
				cout << Gw << endl;
			}
			else {
				cout << Gu << endl;
			}
		}
	}

	Gw.clear();
	Gu.clear();
}

int main(int argc, char *argv[]) {
	//debug_graphs();
	return debug_path_finding(argc, argv);
}

