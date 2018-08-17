#include <lgraph/data_structures/udgraph.hpp>

namespace lgraph {
namespace utils {

// PROTECTED

void udgraph::get_unique_edges(set<edge>& unique_edges) const {
	// insert all edges into a set to get only those that are unique
	for (node i = 0; i < n_nodes(); ++i) {
		const neighbourhood& ni = adjacency_list[i];

		for (size_t ni_it = 0; ni_it < ni.n_elems(); ++ni_it) {

			// this graph is DIRECTED so an edge is the
			// pair of nodes (i,ni[ni_it]) interpreted as
			// "i points to ni[ni_it]"
			edge e(i, ni[ni_it]);

			bool new_edge = unique_edges.find(e) == unique_edges.end();
			if (new_edge) {
				unique_edges.insert(e);
			}

		}
	}
}

// PUBLIC

udgraph::udgraph() : uxgraph() { }
udgraph::~udgraph() { }

// MODIFIERS

void udgraph::add_edge(const edge& e) {
	add_edge(e.first, e.second);
}

void udgraph::add_edge(node u, node v) {
	assert( has_node(u) );
	assert( has_node(v) );
	assert( not has_edge(u,v) );

	adjacency_list[u].add(v);
	++num_edges;
}

void udgraph::remove_edge(const edge& e) {
	remove_edge(e.first, e.second);
}

void udgraph::remove_edge(node u, node v) {
	assert( has_node(u) );
	assert( has_node(v) );
	assert( has_edge(u,v) );

	bool erased = false;

	neighbourhood& nu = adjacency_list[u];

	// find the position of node v in neighbourhood of u
	// delete the neighbour
	size_t posu = get_neighbour_position(nu, v);
	if (posu < nu.n_elems()) {
		nu.remove(posu);
		erased = true;
	}

	// decrease number of edges only if necessary
	if (erased) {
		num_edges -= 1;
	}
}

// GETTERS

bool udgraph::has_edge(node u, node v) const {
	assert( has_node(u) );
	assert( has_node(v) );

	const neighbourhood& nu = get_neighbours(u);
	return get_neighbour_position(nu, v) < nu.n_elems();
}

bool udgraph::is_directed() const {
	return true;
}

} // -- namespace utils
} // -- namespace lgraph
