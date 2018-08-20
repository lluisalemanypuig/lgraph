#include <lgraph/data_structures/udgraph.hpp>

namespace lgraph {
namespace utils {

// PROTECTED

void udgraph::get_unique_edges(vector<edge>& unique_edges) const {
	// insert all edges into a set to get only those that are unique
	for (node i = 0; i < n_nodes(); ++i) {

		const neighbourhood& ni = this->adjacency_list[i];
		for (node j : ni) {

			// this graph is DIRECTED so an edge is the
			// pair of nodes (i,j) interpreted as
			// "i points to j"
			unique_edges.push_back( edge(i,j) );
		}
	}
}

// PUBLIC

udgraph::udgraph() : uxgraph() { }
udgraph::~udgraph() { }

// MODIFIERS

void udgraph::add_edge(node u, node v) {
	assert( has_node(u) );
	assert( has_node(v) );
	assert( not has_edge(u,v) );

	adjacency_list[u].add(v);
	++num_edges;
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
	if (posu < nu.size()) {
		nu.remove(posu);
		erased = true;
	}

	// decrease number of edges only if necessary
	if (erased) {
		num_edges -= 1;
	}
}

void udgraph::remove_node(node u) {
	assert( has_node(u) );

	vector<neighbourhood>& adj = adjacency_list;

	// decrease number of edges
	num_edges -= adj[u].size();
	// remove node u's entry from adjacency list
	adj.erase( adj.begin() + u );

	// Remove u from every node's neighbourhood.
	// Note that since this graph is directed we need to
	// decrease the number of edges at each step
	for (node v = 0; v < adj.size(); ++v) {
		neighbourhood& Nv = adj[v];

		// find u in the list and decrease the index of
		// the corresponding nodes
		for (size_t p = Nv.size(); p > 0; --p) {
			if (Nv[p - 1] == u) {
				Nv.remove(p - 1);
				num_edges -= 1;
			}
			else if (Nv[p - 1] > u) {
				// decrease index of node
				Nv[p - 1] -= 1;
			}
		}
	}
}

// GETTERS

bool udgraph::has_edge(node u, node v) const {
	assert( has_node(u) );
	assert( has_node(v) );

	const neighbourhood& nu = get_neighbours(u);
	return get_neighbour_position(nu, v) < nu.size();
}

bool udgraph::is_directed() const {
	return true;
}

} // -- namespace utils
} // -- namespace lgraph
