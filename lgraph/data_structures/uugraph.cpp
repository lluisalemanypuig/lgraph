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

#include <lgraph/data_structures/uugraph.hpp>

// C includes
#include <assert.h>

namespace lgraph {

// PROTECTED

void uugraph::get_unique_edges(std::vector<edge>& unique_edges) const {
	// insert all edges into a set to get only those that are unique
	for (node i = 0; i < n_nodes(); ++i) {

		const neighbourhood& ni = adjacency_list[i];
		for (node j : ni) {

			// since this graph is UNDIRECTED the order of the
			// indices in the pair does not matter. Use the
			// lexicographic order
			if (i < j) {
				unique_edges.push_back( edge(i, j) );
			}
		}
	}
}

// PUBLIC

uugraph::uugraph() : uxgraph() { }

uugraph::uugraph(const std::vector<neighbourhood>& adj) : uxgraph() {
	init(adj);
}

uugraph::uugraph(const std::vector<neighbourhood>& adj, size_t n_edges) : uxgraph(adj, n_edges) { }

uugraph::~uugraph() { }

void uugraph::init(const std::vector<neighbourhood>& adj) {
	adjacency_list = adj;

	// count the amount of edges for only those pairs
	// of nodes (u,v) such that u < v (because this graph
	// is undirected)
	for (node u = 0; u < adjacency_list.size(); ++u) {
		for (node v : adjacency_list[u]) {
			if (u < v) {
				++num_edges;
			}
		}
	}
}

// MODIFIERS

void uugraph::add_edge(node u, node v) {
	assert( has_node(u) );
	assert( has_node(v) );
	assert( not has_edge(u,v) );

	adjacency_list[u].add(v);
	adjacency_list[v].add(u);
	++num_edges;
}

void uugraph::remove_edge(node u, node v) {
	assert( has_node(u) );
	assert( has_node(v) );
	assert( has_edge(u,v) );

	bool erased = false;

	neighbourhood& nu = adjacency_list[u];
	neighbourhood& nv = adjacency_list[v];

	// find the position of node v in neighbourhood of u
	// delete the neighbour
	size_t posu = get_neighbour_position(nu, v);
	if (posu < nu.size()) {
		nu.remove(posu);
		erased = true;
	}

	// find the position of node v in neighbourhood of u
	// delete the neighbour
	size_t posv = get_neighbour_position(nv, u);
	if (posv < nv.size()) {
		nv.remove(posv);
		erased = true;
	}

	// decrease number of edges only if necessary
	if (erased) {
		num_edges -= 1;
	}
}

void uugraph::remove_node(node u) {
	assert( has_node(u) );

	std::vector<neighbourhood>& adj = adjacency_list;

	// decrease number of edges
	num_edges -= adj[u].size();
	// remove node u's entry from adjacency list
	adj.erase( adj.begin() + u );

	// Remove u from every node's neighbourhood.
	// Note that since this graph is undirected there is no
	// need to decrease the number of edges anymore.
	for (node v = 0; v < adj.size(); ++v) {
		neighbourhood& Nv = adj[v];

		// find u in the list and decrease the index of
		// the corresponding nodes
		for (size_t p = Nv.size(); p > 0; --p) {
			if (Nv[p - 1] == u) {
				Nv.remove(p - 1);
			}
			else if (Nv[p - 1] > u) {
				// decrease index of node
				Nv[p - 1] -= 1;
			}
		}
	}
}

// GETTERS

bool uugraph::has_edge(node u, node v) const {
	assert( has_node(u) );
	assert( has_node(v) );

	// since this graph is undirected, look for the neighbour
	// in the shortest neighbourhood list:
	// if u's list is the shortest then look for 'v' in it
	// if v's list is the shortest then look for 'u' in it

	const neighbourhood& nu = get_neighbours(u);
	const neighbourhood& nv = get_neighbours(v);

	if (nu.size() < nv.size()) {
		return get_neighbour_position(nu, v) < nu.size();
	}
	else {
		return get_neighbour_position(nv, u) < nv.size();
	}
}

bool uugraph::is_directed() const {
	return false;
}

} // -- namespace lgraph
