#include <lgraph/data_structures/uxgraph.hpp>

// C includes
#include <assert.h>

namespace lgraph {

// PUBLIC

uxgraph::uxgraph() : xxgraph() { }

uxgraph::uxgraph(size_t n) : xxgraph() {
	init(n);
}

uxgraph::uxgraph(const std::vector<neighbourhood>& adj, size_t n_edges) : xxgraph() {
	init(adj, n_edges);
}

uxgraph::~uxgraph() { }

void uxgraph::init(size_t n) {
	clear();
	initialise_parent_graph(n);
}

void uxgraph::init(const std::vector<neighbourhood>& adj, size_t n_edges) {
	clear();
	adjacency_list = adj;
	num_edges = n_edges;
}

// OPERATORS

uxgraph& uxgraph::operator= (const uxgraph& g) {
	clear();
	adjacency_list = g.adjacency_list;
	num_edges = g.num_edges;
	return *this;
}


// MODIFIERS

void uxgraph::add_edge(const edge& e) {
	add_edge(e.first, e.second);
}

void uxgraph::add_edges(const std::vector<edge>& edge_list) {
	for (const edge& e : edge_list) {
		add_edge(e.first, e.second);
	}
}

void uxgraph::clear() {
	clear_parent_graph();
}

// GETTERS

bool uxgraph::is_weighted() const {
	return false;
}

void uxgraph::edges(std::vector<edge>& all_edges) const {
	get_unique_edges(all_edges);
}

} // -- namespace lgraph
