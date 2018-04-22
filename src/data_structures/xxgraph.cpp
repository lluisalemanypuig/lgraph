#include "xxgraph.hpp"

namespace lgraph {
namespace utils {

/// PROTECTED

template<class T>
ncit xxgraph<T>::cget_neighbour_position(const neighbourhood& n, node u) const {
	bool found = false;
	ncit cit = n.begin();
	while (cit != n.end() and not found) {
		if (*cit == u) found = true;
		else ++cit;
	}
	return cit;
}

template<class T>
nit xxgraph<T>::get_neighbour_position(neighbourhood& n, node u) {
	bool found = false;
	nit it = n.begin();
	while (it != n.end() and not found) {
		if (*it == u) found = true;
		else ++it;
	}
	return it;
}

/// PUBLIC

template<class T>
xxgraph<T>::xxgraph() {
	num_edges = 0;
}

template<class T>
xxgraph<T>::~xxgraph() { }

template<class T>
void xxgraph<T>::init(size_t n) {
	num_edges = 0;
	initialise_adjacency_list(n);
	initialise_weights(n);
}

/// OPERATORS

/// MODIFIERS

template<class T>
size_t xxgraph<T>::add_node() {
	adjacency_list.push_back(neighbourhood());
	return adjacency_list.size() - 1;
}

template<class T>
size_t xxgraph<T>::add_n_nodes(node n) {
	adjacency_list.insert(adjacency_list.end(), n, neighbourhood());
	return adjacency_list.size() - 1;
}

/// MODIFIERS

template<class T>
void xxgraph<T>::clear() {
	clear_adjacency_list();
	clear_weights();
}

/// GETTERS

template<class T>
bool xxgraph<T>::has_node(node u) const {
	return u < adjacency_list.size();
}

template<class T>
size_t xxgraph<T>::n_nodes() const {
	return adjacency_list.size();
}

template<class T>
size_t xxgraph<T>::n_edges() const {
	return num_edges;
}

template<class T>
void xxgraph<T>::nodes(vector<node>& all_nodes) const {
	all_nodes.resize(adjacency_list.size());
	for (size_t u = 0; u < all_nodes.size(); ++u) all_nodes[u] = u;
}

template<class T>
const neighbourhood& xxgraph<T>::get_neighbours(node u) const {
	return adjacency_list[u];
}

template<class T>
size_t xxgraph<T>::degree(node u) const {
	return adjacency_list[u].size();
}

/// I/O

/// FEATURES OF GRAPHS

template<class T>
void xxgraph<T>::get_adjacency_matrix(vector<vector<bool> >& adj_mat) const {
	const size_t N = n_nodes();
	adj_mat = vector<vector<bool> >(N, vector<bool>(N, false));
	for (size_t u = 0; u < N; ++u) {
		const neighbourhood& Nu = get_neighbours(u);
		for (size_t v : Nu) {
			adj_mat[u][v] = true;
		}
	}
}

template<class T>
void xxgraph<T>::get_degree_sequence(map<node, node>& deg_seq) const {
	for (size_t u = 0; u < adjacency_list.size(); ++u) {
		size_t deg = degree(u);
		if (deg_seq.find(deg) == deg_seq.end()) deg_seq[deg] = 1;
		else ++deg_seq[deg];
	}
}

template<class T>
size_t xxgraph<T>::n_triangles() const {
	size_t tris = 0;
	const size_t N = n_nodes();

	for (size_t u = 0; u < N; ++u) {

		const neighbourhood& Nu = get_neighbours(u);
		ncit v = Nu.begin();
		for (; v != Nu.end(); ++v) {

			ncit w = v; ++w;
			for (; w != Nu.end(); ++w) {

				// existing edges: (u, v), (u, w)
				// check edge (v, w) for triangles

				if (has_edge(*v, *w)) ++tris;
			}
		}

	}

	// Each triangle is counted three times
	return tris/3;
}

} // -- namespace utils
} // -- namespace lgraph
