#include "uugraph.hpp"

namespace lgraph {
namespace utils {

// PROTECTED

void uugraph::get_unique_edges(set<edge>& unique_edges) const {
	// insert all edges into a set to get only those that are unique
	for (size_t i = 0; i < adjacency_list.size(); ++i) {

		for (ncit it = adjacency_list[i].begin(); it != adjacency_list[i].end(); ++it) {

			edge e;
			if (i < *it) {
				e = edge(i, *it);
			}
			else {
				e = edge(*it, i);
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

	adjacency_list[u].push_back(v);
	adjacency_list[v].push_back(u);
	++num_edges;
}

void uugraph::remove_edge(const edge& e) {
	remove_edge(e.first, e.second);
}

void uugraph::remove_edge(node u, node v) {
	assert( has_node(u) );
	assert( has_node(v) );

	bool erased = false;

	neighbourhood& nu = adjacency_list[u];
	nit it_u = get_neighbour_position(nu, v);
	if (it_u != nu.end()) {
		nu.erase(it_u);
		erased = true;
	}

	neighbourhood& nv = adjacency_list[v];
	nit it_v = get_neighbour_position(nv, u);
	if (it_v != nv.end()) {
		nv.erase(it_v);
		erased = true;
	}

	num_edges -= erased;
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
