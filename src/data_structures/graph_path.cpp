#include "graph_path.hpp"

namespace dsa {
namespace utils {

	/// -----------
/// CLASS node_path

node_path::node_path() : vector<size_t>() { }
node_path::node_path(size_t n) : vector<size_t>(n) { }
node_path::node_path(size_t n, node u) : vector<size_t>(n, u) { }

void node_path::concatenate(const node_path& p) {
	insert(
		end(),
		p.begin() + 1, p.end()
	);
}

/// -----------------------
/// CLASS boolean_node_path

boolean_path::boolean_path(size_t n) {
	init(n);
}

boolean_path::~boolean_path() {

}

/// INITIALISERS

void boolean_path::init(size_t n) {
	nodes_in_path.init_unset(n);
	n_nodes = 0;
}

void boolean_path::init(size_t n, const node_path &vp) {
	init(n);
	for (size_t u : vp) {
		add_node(u);
	}
}

void boolean_path::clear() {
	nodes_in_path.clear();
	n_nodes = 0;
}

/// MODIFIERS

void boolean_path::add_node(node u) {
	if (not nodes_in_path[u]) {
		nodes_in_path.set_bit(u);
		++n_nodes;
	}
}

void boolean_path::remove_node(node u) {
	if (nodes_in_path[u]) {
		nodes_in_path.unset_bit(u);
		--n_nodes;
	}
}

void boolean_path::concatenate(const boolean_path& bp) {
	if (bp.size() > 0) {
		for (size_t i = 0; i < bp.potential_length(); ++i) {
			if (bp.nodes_in_path[i]) {
				add_node(i);
			}
		}
	}
}

/// OPERATORS

bool boolean_path::operator[] (size_t i) const {
	return nodes_in_path[i];
}

boolean_path& boolean_path::operator= (const boolean_path& bp) {
	n_nodes = bp.n_nodes;
	nodes_in_path = bp.nodes_in_path;
	return *this;
}

/// GETTERS

size_t boolean_path::size() const {
	return n_nodes;
}

size_t boolean_path::potential_length() const {
	return nodes_in_path.size();
}

node boolean_path::next(const graph& G, node prev, node u) const {
	node next = u;
	bool found = false;

	const neighbourhood& Nu = G.get_neighbours(u);
	size_t i = 0;
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

/// CONVERSIONS

node_path boolean_path::to_node_path(const graph& G, node s) const {
	node_path np;
	to_node_path(G, s, np);
	return np;
}

void boolean_path::to_node_path(const graph& G, node s, node_path& np) const {
	if (n_nodes == 0) {
		// no vertices in the path
		return;
	}

	np = node_path(0);
	np.push_back(s);

	size_t added_nodes = 1;
	node prev_node = -1;
	node current = s;
	node next_node;

	while ( (next_node = next(G, prev_node, current)) != current ) {
		np.push_back(next_node);
		++added_nodes;

		prev_node = current;
		current = next_node;
	}
}

string boolean_path::pretty_string() const {
	string s;
	pretty_string(s);
	return s;
}

void boolean_path::pretty_string(string& s) const {
	if (n_nodes > 0) {
		stringstream ss;

		ss << "0";
		for (size_t i = 1; i < nodes_in_path.size(); ++i) {
			ss << " " << i;
		}
		ss << "\n";
		ss << std::to_string(nodes_in_path[0]);
		for (size_t i = 1; i < nodes_in_path.size(); ++i) {
			const bool& ni = nodes_in_path[i];
			ss << " " << setw(std::to_string(i).length()) << (ni ? "1" : "0");
		}

		s = ss.str();
	}
}

string boolean_path::to_string() const {
	string s;
	to_string(s);
	return s;
}

void boolean_path::to_string(string& s) const {
	if (n_nodes > 0) {
		s = std::to_string(nodes_in_path[0]);
		for (size_t i = 1; i < nodes_in_path.size(); ++i) {
			s += " " + std::to_string(nodes_in_path[i]);
		}
	}
}

} // -- namespace utils
} // -- namespace dsa
