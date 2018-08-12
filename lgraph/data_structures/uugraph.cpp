#include "uugraph.hpp"

namespace lgraph {
namespace utils {

// PROTECTED

void uugraph::get_unique_edges(set<edge>& unique_edges) const {
	// insert all edges into a set to get only those that are unique
	for (node i = 0; i < n_nodes(); ++i) {
		const neighbourhood& ni = adjacency_list[i];

		for (size_t it = 0; it < ni.n_elems(); ++it) {

			// since this graph is UNDIRECTED the order of the
			// indices in the pair does not matter
			edge e;
			if (i < ni[it]) {
				e = edge(i, ni[it]);
			}
			else {
				e = edge(ni[it], i);
			}

			bool new_edge = unique_edges.find(e) == unique_edges.end();
			if (new_edge) {
				unique_edges.insert(e);
			}

		}
	}
}

// PUBLIC

uugraph::uugraph() : uxgraph() { }
uugraph::~uugraph() { }

// MODIFIERS

void uugraph::add_edge(const edge& e) {
	add_edge(e.first, e.second);
}

void uugraph::add_edge(node u, node v) {
	assert( has_node(u) );
	assert( has_node(v) );
	assert( not has_edge(u,v) );

	adjacency_list[u].add(v);
	adjacency_list[v].add(u);
	++num_edges;
}

void uugraph::remove_edge(const edge& e) {
	remove_edge(e.first, e.second);
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
	if (posu < nu.n_elems()) {
		nu.remove(posu);
		erased = true;
	}

	// find the position of node v in neighbourhood of u
	// delete the neighbour
	size_t posv = get_neighbour_position(nv, u);
	if (posv < nv.n_elems()) {
		nv.remove(posv);
		erased = true;
	}

	// decrease number of edges only if necessary
	if (erased) {
		num_edges -= 1;
	}
}

// GETTERS

void uugraph::edges(vector<edge>& all_edges) const {
	set<edge> unique_edges;
	get_unique_edges(unique_edges);

	// Dump all unique edges from the set into the vector 'all_edges'.
	// The size of the vector is equal to 'num_edges'
	size_t i = 0;
	all_edges.resize(unique_edges.size());
	set<edge>::const_iterator it = unique_edges.begin();
	while (it != unique_edges.end()) {
		all_edges[i] = *it;
		++it;
		++i;
	}
}

} // -- namespace utils
} // -- namespace lgraph
