#include "graph_path.hpp"

namespace dsa {
namespace utils {

/// CLASS node_path

node_path::node_path() : vector<size_t>() {

}

node_path::node_path(size_t n) : vector<size_t>(n) {

}

node_path::node_path(size_t n, node u) : vector<size_t>(n, u) {

}

void node_path::concatenate(const node_path& p) {
	insert(
		end(),
		p.begin() + 1, p.end()
	);
}

/// CLASS boolean_node_path

boolean_path::boolean_path() {
	n_nodes = 0;
}

boolean_path::~boolean_path() {

}

void boolean_path::init(size_t n) {
	nodes_in_path = vector<bool>(n, false);
}

void boolean_path::init(const node_path &vp) {
	init(vp.size());
	for (size_t u : vp) {
		add_node(u);
	}
}

void boolean_path::clear() {
	nodes_in_path.clear();
}

void boolean_path::add_node(node u) {
	if (not nodes_in_path[u]) {
		++n_nodes;
		nodes_in_path[u] = true;
	}
}

void boolean_path::remove_node(node u) {
	if (nodes_in_path[u]) {
		--n_nodes;
		nodes_in_path[u] = false;
	}
}

bool boolean_path::operator[] (size_t i) const {
	return nodes_in_path[i];
}

node boolean_path::next(const graph& G, node prev, node u) const {
	node next = u;
	bool found = false;
	size_t i = 0;

	const neighbourhood& Nu = G.get_neighbours(u);
	while (i < Nu.size() and not found) {
		node v = Nu[i];
		if (nodes_in_path[v] and v != prev) {
			next = v;
			found = true;
		}
		++i;
	}

	return next;
}

} // -- namespace utils
} // -- namespace dsa
