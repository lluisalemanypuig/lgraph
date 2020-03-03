/*********************************************************************
 * lgraph
 * Copyright (C) 2018-2019 Lluís Alemany Puig
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contact: Lluís Alemany Puig (lluis.alemany.puig@gmail.com)
 *
 ********************************************************************/

// C includes
#include <string.h>

// C++ includes
#include <iostream>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/wugraph.hpp>
#include <lgraph/data_structures/uugraph.hpp>
using namespace lgraph;
using namespace utils;

#include <lgraph/io/io.hpp>
using namespace io;

// Custom includes
#include "functions.hpp"

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
	cout << "lgraph Copyright (C) 2018-2019 Lluís Alemany Puig" << endl;
	cout << "This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'." << endl;
	cout << "This is free software, and you are welcome to redistribute it" << endl;
	cout << "under certain conditions; type `show c' for details." << endl;

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

		bool res = edge_list::read(file, &G);
		if (not res) {
			cerr << "Could not read graph from file '" << file << "'" << endl;
			return 1;
		}

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

		bool res = edge_list::read(file, &G);
		if (not res) {
			cerr << "Could not read graph from file '" << file << "'" << endl;
			return 1;
		}

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

