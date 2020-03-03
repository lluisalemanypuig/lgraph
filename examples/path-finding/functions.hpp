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

#pragma once

// C++ includes
#include <vector>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/wxgraph.hpp>
#include <lgraph/data_structures/uxgraph.hpp>
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
