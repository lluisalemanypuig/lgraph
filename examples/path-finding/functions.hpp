#pragma once

// C++ includes
#include <vector>
using namespace std;

// Custom includes
#include "data_structures/boolean_path.hpp"
#include "data_structures/uwgraph.hpp"
#include "data_structures/uugraph.hpp"
#include "graph_traversal/traversal.hpp"
using namespace lgraph;
using namespace utils;

namespace functions {

	template<class T>
	void print_distance_matrix(const vector<vector<T> >& dist, const vector<vector<size_t> >& n_paths);

	// weighted distances/paths

	template<class T>
	void deb_distances_t(const xxgraph<T> *G, node source, node target);
	template<class T>
	void deb_paths_t(const xxgraph<T> *G, node source, node target);
	template<class T>
	void deb_all_paths_t(const xxgraph<T> *G, node source, node target);
	template<class T>
	void deb_bpaths_t(const xxgraph<T> *G, node source, node target);
	template<class T>
	void deb_all_bpaths_t(const xxgraph<T> *G, node source, node target);

	// unweighted distances/pahts

	void deb_distances(const xxgraph<_new_> *G, node source, node target);
	void deb_paths(const xxgraph<_new_> *G, node source, node target);
	void deb_all_paths(const xxgraph<_new_> *G, node source, node target);
	void deb_bpaths(const xxgraph<_new_> *G, node source, node target);
	void deb_all_bpaths(const xxgraph<_new_> *G, node source, node target);

}

#include "display.cpp"
#include "weighted_dist_paths.cpp"
