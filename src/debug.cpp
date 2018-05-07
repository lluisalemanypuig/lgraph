/// C includes
#include <string.h>

/// C++ includes
#include <iostream>
using namespace std;

/// Custom includes
#include "debug/debug.hpp"
#include "utils/logger.hpp"
using namespace lgraph;
using namespace traversal;

int debug_path_finding(int argc, char *argv[]) {
	logger<cout_stream>& outLOG = logger<cout_stream>::get_logger();
	logger<cerr_stream>& errLOG = logger<cerr_stream>::get_logger();

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
		errLOG.log() << "No file specified!" << endl;
		return 1;
	}

	if (not source_set or not target_set) {
		errLOG.log() << "Error: source or target not specified" << endl;
		return 1;
	}

	if (weighted) {
		outLOG.log() << "Debugging weighted graphs" << endl;

		uwgraph<float> G;

		G.read_from_file(file);
		outLOG.log() << "graph read:" << endl;
		outLOG.log() << G << endl;
		outLOG.log() << endl;

		debug::deb_distances_t(&G, S, T);
		debug::deb_paths_t(&G, S, T);
		debug::deb_all_paths_t(&G, S, T);
		debug::deb_bpaths_t(&G, S, T);
		debug::deb_all_bpaths_t(&G, S, T);
	}
	else {
		outLOG.log() << "Debugging unweighted graphs" << endl;

		uugraph G;

		G.read_from_file(file);
		outLOG.log() << "graph read:" << endl;
		outLOG.log() << G << endl;
		outLOG.log() << endl;

		debug::deb_distances(&G, S, T);
		debug::deb_paths(&G, S, T);
		debug::deb_all_paths(&G, S, T);
		debug::deb_bpaths(&G, S, T);
		debug::deb_all_bpaths(&G, S, T);
	}

	return 0;
}

void debug_graphs() {
	logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

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
				LOG.log() << Gw.edge_weight(u, v) << endl;
			}
			else {
				LOG.log() << Gu.edge_weight(u, v) << endl;
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
				LOG.log() << Gw << endl;
			}
			else {
				LOG.log() << Gu << endl;
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

