#include "xxgraph.hpp"

namespace lgraph {
namespace utils {

// PROTECTED

size_t xxgraph::get_neighbour_position(const neighbourhood& n, node u) const {
	bool found = false;
	size_t p = 0;
	while (p < n.n_elems() and not found) {
		if (n[p] == u) {
			found = true;
		}
		else {
			++p;
		}
	}
	return p;
}

void xxgraph::initialise_adjacency_list(size_t n) {
	adjacency_list = vector<neighbourhood>(n);
}

void xxgraph::clear_adjacency_list() {
	adjacency_list.clear();
}

void xxgraph::initialise_parent_graph(size_t n) {
	initialise_adjacency_list(n);
	num_edges = 0;
}

void xxgraph::clear_parent_graph() {
	clear_adjacency_list();
	num_edges = 0;
}

// PUBLIC

xxgraph::xxgraph() {
	num_edges = 0;
}

xxgraph::~xxgraph() {
}

// OPERATORS

// MODIFIERS

size_t xxgraph::add_node() {
	adjacency_list.push_back(neighbourhood());
	return adjacency_list.size() - 1;
}

size_t xxgraph::add_n_nodes(node n) {
	adjacency_list.insert(adjacency_list.end(), n, neighbourhood());
	return adjacency_list.size() - 1;
}

// GETTERS

bool xxgraph::has_node(node u) const {
	return u < adjacency_list.size();
}

bool xxgraph::has_edge(node u, node v) const {
	assert( has_node(u) );
	assert( has_node(v) );

	const neighbourhood& nu = get_neighbours(u);
	return get_neighbour_position(nu, v) < nu.n_elems();
}

size_t xxgraph::n_nodes() const {
	return adjacency_list.size();
}

size_t xxgraph::n_edges() const {
	return num_edges;
}

void xxgraph::nodes(vector<node>& all_nodes) const {
	all_nodes.resize(adjacency_list.size());
	for (size_t u = 0; u < all_nodes.size(); ++u) {
		all_nodes[u] = u;
	}
}

const neighbourhood& xxgraph::get_neighbours(node u) const {
	return adjacency_list[u];
}

size_t xxgraph::degree(node u) const {
	return adjacency_list[u].size();
}

// I/O

// FEATURES OF GRAPHS

void xxgraph::get_adjacency_matrix(vector<vector<bool> >& adj_mat) const {
	const size_t N = n_nodes();
	adj_mat = vector<vector<bool> >(N, vector<bool>(N, false));
	for (size_t u = 0; u < N; ++u) {
		const neighbourhood& Nu = get_neighbours(u);
		for (size_t v : Nu) {
			adj_mat[u][v] = true;
		}
	}
}

void xxgraph::get_degree_sequence(map<size_t, size_t>& deg_seq) const {
	for (size_t u = 0; u < adjacency_list.size(); ++u) {
		size_t deg = degree(u);
		if (deg_seq.find(deg) == deg_seq.end()) deg_seq[deg] = 1;
		else ++deg_seq[deg];
	}
}

size_t xxgraph::n_triangles() const {
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
