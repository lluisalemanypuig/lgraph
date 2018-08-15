#include <lgraph/data_structures/boolean_path.hpp>

namespace lgraph {
namespace utils {

// PUBLIC

template<class T>
boolean_path<T>::boolean_path() {
	n_nodes = 0;
	path_length = T(0);
}

template<class T>
boolean_path<T>::~boolean_path() { }

// INITIALISERS

template<class T>
void boolean_path<T>::init(size_t n) {
	nodes_in_path.init_unset(n);
	n_nodes = 0;
	path_length = 0;
}

template<class T>
void boolean_path<T>::init(size_t n, const node_path<T>& vp) {
	init(n);
	for (node u : vp.get_nodes()) {
		add_node(u);
	}
	path_length = vp.get_length();
}

template<class T>
void boolean_path<T>::clear() {
	nodes_in_path.clear();
	n_nodes = 0;
	path_length = 0;
}

// MODIFIERS

template<class T>
void boolean_path<T>::add_node(node u) {
	assert((0 <= u) and (u < nodes_in_path.size()));

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

// OPERATORS

template<class T>
bool boolean_path<T>::operator[] (node i) const {
	return nodes_in_path[i];
}

template<class T>
boolean_path<T>& boolean_path<T>::operator= (const boolean_path<T>& bp) {
	n_nodes = bp.n_nodes;
	nodes_in_path = bp.nodes_in_path;
	path_length = bp.path_length;
	return *this;
}

// GETTERS

template<class T>
size_t boolean_path<T>::size() const {
	return n_nodes;
}

template<class T>
T boolean_path<T>::get_length() const {
	return path_length;
}

template<class T>
size_t boolean_path<T>::potential_length() const {
	return nodes_in_path.size();
}

template<class T>
bool boolean_path<T>::closest_next(const xxgraph *G, node prev, node curr, node& next) const {
	assert(G != nullptr);
	assert((0 <= curr) and (curr < nodes_in_path.size()));

	bool found = false;

	const neighbourhood& Nu = G->get_neighbours(curr);
	if (G->is_weighted()) {
		weight_list<T> weights;
		(static_cast<const wxgraph<T> *>(G))->get_weights(curr, weights);
		T dist = utils::inf_t<T>();

		for (size_t i = 0; i < Nu.size(); ++i) {
			node v = Nu[i];
			if (nodes_in_path[v] and v != prev and weights[i] < dist) {
				next = v;
				dist = weights[i];
				found = true;
			}
		}
	}
	else {
		_new_ dist = utils::inf_t<_new_>();

		for (size_t i = 0; i < Nu.size(); ++i) {
			node v = Nu[i];
			if (nodes_in_path[v] and v != prev and 1 < dist) {
				next = v;
				dist = 1;
				found = true;
			}
		}
	}
	return found;
}

template<class T>
bool boolean_path<T>::closest_next(const xxgraph *G, const vector<bool>& prev, node curr, node& next) const {
	assert(G != nullptr);
	assert((0 <= curr) and (curr < nodes_in_path.size()));

	bool found = false;

	const neighbourhood& Nu = G->get_neighbours(curr);
	if (G->is_weighted()) {
		weight_list<T> weights;
		(static_cast<const wxgraph<T> *>(G))->get_weights(curr, weights);
		T dist = utils::inf_t<T>();

		for (size_t i = 0; i < Nu.size(); ++i) {
			node v = Nu[i];
			if (nodes_in_path[v] and not prev[v] and weights[i] < dist) {
				next = v;
				dist = weights[i];
				found = true;
			}
		}
	}
	else {
		_new_ dist = utils::inf_t<_new_>();

		for (size_t i = 0; i < Nu.size(); ++i) {
			node v = Nu[i];
			if (nodes_in_path[v] and not prev[v] and 1 < dist) {
				next = v;
				dist = 1;
				found = true;
			}
		}
	}
	return found;
}

// CONVERSIONS

template<class T>
node_path<T> boolean_path<T>::to_node_path(const xxgraph *G, node s) const {
	node_path<T> np;
	to_node_path(G, s, np);
	return np;
}

template<class T>
void boolean_path<T>::to_node_path(const xxgraph *G, node s, node_path<T>& np) const {
	if (n_nodes == 0) {
		// no vertices in the path
		return;
	}

	np = node_path<T>();
	np.add_node(s);

	size_t added_nodes = 1;
	node current = s;
	node next_node;

	vector<bool> vis(G->n_nodes(), false);
	vis[current] = true;

	bool next = closest_next(G, vis, current, next_node);
	while ( next ) {
		np.add_node(next_node);
		++added_nodes;

		current = next_node;
		vis[current] = true;

		next = closest_next(G, vis, current, next_node);
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

template<class T>
void from_nps_to_bps(const node_path_set<T>& nps, size_t N, boolean_path_set<T>& bps) {
	size_t n_paths = nps.size();

	bps = boolean_path_set<T>(n_paths);
	for (size_t j = 0; j < n_paths; ++j) {
		bps[j].init(N, nps[j]);
	}
}

} // -- namespace utils
} // -- namespace lgraph
