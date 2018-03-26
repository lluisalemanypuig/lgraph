#include "graph_path.hpp"

namespace dsa {
namespace utils {

/// -----------
/// CLASS node_path

template<class T>
node_path<T>::node_path() {
	 nodes = vector<node>();
	 path_length = 0;
}

template<class T>
node_path<T>::node_path(node n) {
	nodes = vector<node>(1, n);
	path_length = 0;
}

template<class T>
node_path<T>::~node_path() { }

template<class T>
void node_path<T>::empty() {
	nodes = vector<node>();
	path_length = 0;
}

/// OPERATORS

template<class T>
node node_path<T>::operator[] (size_t i) const {
	return nodes[i];
}

template<class T>
node& node_path<T>::operator[] (size_t i) {
	return nodes[i];
}

template<class T>
bool node_path<T>::operator< (const node_path<T>& p) const {
	return path_length < p.path_length;
}

template<class T>
bool node_path<T>::operator> (const node_path<T>& p) const {
	return path_length > p.path_length;
}

template<class T>
node_path<T>& node_path<T>::operator= (const node_path<T>& np) {
	nodes = np.nodes;
	path_length = np.path_length;
	return *this;
}

/// MODIFIERS

template<class T>
void node_path<T>::concatenate(const node_path<T>& p) {
	nodes.insert(
		nodes.end(),
		p.nodes.begin() + 1, p.nodes.end()
	);
	path_length += p.path_length;
}

template<class T>
void node_path<T>::add_node(node u) {
	nodes.push_back(u);
}

template<class T>
void node_path<T>::add_length(const T& l) {
	path_length += l;
}

template<class T>
void node_path<T>::set_length(const T& l) {
	path_length = l;
}

template<class T>
void node_path<T>::reverse() {
	std::reverse(nodes.begin(), nodes.end());
}

template<class T>
void node_path<T>::delete_last() {
	nodes.pop_back();
}

/// GETTERS

template<class T>
size_t node_path<T>::size() const {
	return nodes.size();
}

template<class T>
T node_path<T>::get_length() const {
	return path_length;
}

template<class T>
size_t node_path<T>::last_node() const {
	return nodes.back();
}

/// -----------------------
/// CLASS boolean_node_path

template<class T>
boolean_path<T>::boolean_path(size_t n) {
	init(n);
}

template<class T>
boolean_path<T>::~boolean_path() { }

/// INITIALISERS

template<class T>
void boolean_path<T>::init(size_t n) {
	nodes_in_path.init_unset(n);
	n_nodes = 0;
	path_length = 0;
}

template<class T>
void boolean_path<T>::init(size_t n, const node_path<T>& vp) {
	init(n);
	for (size_t u : vp) {
		add_node(u);
	}
	path_length = vp.path_length;
}

template<class T>
void boolean_path<T>::clear() {
	nodes_in_path.clear();
	n_nodes = 0;
	path_length = 0;
}

/// MODIFIERS

template<class T>
void boolean_path<T>::add_node(node u) {
	if (not nodes_in_path[u]) {
		nodes_in_path.set_bit(u);
		++n_nodes;
	}
}

template<class T>
void boolean_path<T>::add_length(const T& l) {
	path_length += l;
}

template<class T>
void boolean_path<T>::set_length(const T& l) {
	path_length = l;
}

template<class T>
void boolean_path<T>::concatenate(const boolean_path<T>& bp) {
	if (bp.size() > 0) {
		for (size_t i = 0; i < bp.potential_length(); ++i) {
			if (bp.nodes_in_path[i]) {
				add_node(i);
			}
		}
		add_length(bp.path_length);
	}
}

/// OPERATORS

template<class T>
bool boolean_path<T>::operator[] (size_t i) const {
	return nodes_in_path[i];
}

template<class T>
boolean_path<T>& boolean_path<T>::operator= (const boolean_path<T>& bp) {
	n_nodes = bp.n_nodes;
	nodes_in_path = bp.nodes_in_path;
	path_length = bp.path_length;
	return *this;
}

/// GETTERS

template<class T>
size_t boolean_path<T>::size() const {
	return n_nodes;
}

template<class T>
size_t boolean_path<T>::potential_length() const {
	return nodes_in_path.size();
}

template<class T>
node boolean_path<T>::next(const xxgraph<T> *G, node prev, node u) const {
	node next = u;
	bool found = false;

	const neighbourhood& Nu = G->get_neighbours(u);
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

template<class T>
node_path<T> boolean_path<T>::to_node_path(const xxgraph<T> *G, node s) const {
	node_path<T> np;
	to_node_path(G, s, np);
	return np;
}

template<class T>
void boolean_path<T>::to_node_path(const xxgraph<T> *G, node s, node_path<T>& np) const {
	if (n_nodes == 0) {
		// no vertices in the path
		return;
	}

	np = node_path<T>();
	np.add_node(s);

	size_t added_nodes = 1;
	node prev_node = -1;
	node current = s;
	node next_node;

	while ( (next_node = next(G, prev_node, current)) != current ) {
		np.add_node(next_node);
		++added_nodes;

		prev_node = current;
		current = next_node;
	}

	np.set_length(path_length);
}

template<class T>
string boolean_path<T>::pretty_string() const {
	string s;
	pretty_string(s);
	return s;
}

template<class T>
void boolean_path<T>::pretty_string(string& s) const {
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

template<class T>
string boolean_path<T>::to_string() const {
	string s;
	to_string(s);
	return s;
}

template<class T>
void boolean_path<T>::to_string(string& s) const {
	if (n_nodes > 0) {
		s = std::to_string(nodes_in_path[0]);
		for (size_t i = 1; i < nodes_in_path.size(); ++i) {
			s += " " + std::to_string(nodes_in_path[i]);
		}
	}
}

} // -- namespace utils
} // -- namespace dsa
