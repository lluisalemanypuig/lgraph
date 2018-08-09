#pragma once

// C++ includes
#include <vector>
using namespace std;

// Custom includes
#include <lgraph/data_structures/boolean_path.hpp>
#include <lgraph/data_structures/wxgraph.hpp>
#include <lgraph/data_structures/uxgraph.hpp>
#include <lgraph/graph_traversal/traversal.hpp>
using namespace lgraph;
using namespace utils;

namespace functions {

	template<class T>
	void print_distance_matrix(const vector<vector<T> >& dist, const vector<vector<size_t> >& n_paths);

	// weighted distances/paths

	template<class T>
	void deb_distances_t(const wxgraph<T> *G, node source, node target);
	template<class T>
	void deb_paths_t(const wxgraph<T> *G, node source, node target);
	template<class T>
	void deb_all_paths_t(const wxgraph<T> *G, node source, node target);
	template<class T>
	void deb_bpaths_t(const wxgraph<T> *G, node source, node target);
	template<class T>
	void deb_all_bpaths_t(const wxgraph<T> *G, node source, node target);

	// unweighted distances/pahts

	void deb_distances(const uxgraph *G, node source, node target);
	void deb_paths(const uxgraph *G, node source, node target);
	void deb_all_paths(const uxgraph *G, node source, node target);
	void deb_bpaths(const uxgraph *G, node source, node target);
	void deb_all_bpaths(const uxgraph *G, node source, node target);

}

#include "display.cpp"
#include "weighted_dist_paths.cpp"
