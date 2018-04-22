#include "uugraph.hpp"

namespace lgraph {
namespace utils {

/// PRIVATE

void uugraph::initialise_weights(size_t n) {
	UNUSED(n);
	// do nothing
}

void uugraph::clear_weights() {
	// do nothing
}

void uugraph::add_weight(node u, _new_ w) {
	UNUSED(u);
	UNUSED(w);
	// do nothing
}

void uugraph::remove_weight(node u, nit p) {
	UNUSED(u);
	UNUSED(p);
}

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

/// PUBLIC

uugraph::uugraph() {
	init(0);
}

uugraph::uugraph(size_t n) {
	init(n);
}

uugraph::~uugraph() { }

/// OPERATORS

uugraph& uugraph::operator= (const uugraph& g) {
	init(g.n_nodes());
	for (size_t i = 0; i < adjacency_list.size(); ++i) {
		adjacency_list[i] = g.adjacency_list[i];
	}
	num_edges = g.num_edges;
	return *this;
}

/// MODIFIERS

void uugraph::add_edges(const vector<edge>& edge_list, const vector<_new_>& ws) {
	UNUSED(ws);

	for (size_t i = 0; i < edge_list.size(); ++i) {
		const edge& e = edge_list[i];
		add_edge(e.first, e.second);
	}
}

/// GETTERS

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

bool uugraph::has_edge(node u, node v) const {
	const neighbourhood& nu = adjacency_list[u];
	const neighbourhood& nv = adjacency_list[v];

	if (nu.size() <= nv.size()) return cget_neighbour_position(nu, v) != nu.end();
	return cget_neighbour_position(nv, u) != nv.end();
}

_new_ uugraph::edge_weight(node u, node v) const {
	if (u == v) {
		// weight is trivially 0: self-loop
		return 0;
	}

	assert(u < adjacency_list.size());

	// even though it is assumed that edge (u,v) exists, it is better
	// to check that it exists anyway
	assert(cget_neighbour_position( adjacency_list[u] , v) != adjacency_list[u].end());

	// unweighted graphs are assumed to actually have weight
	// but all constant and equal to 1
	return 1;
}

void uugraph::get_weights(node u, vector<_new_>& ws) const {
	assert(this->has_node(u));

	ws = vector<_new_>(degree(u), 1);
}

/// I/O

bool uugraph::read_from_file(const string& filename) {
	return read_from_file(filename.c_str());
}

bool uugraph::read_from_file(const char *filename) {
	ifstream fin;
	fin.open(filename);

	// file could not be opened. return "error"
	if (not fin.is_open()) {
		return false;
	}

	size_t max_vert_idx = 0;
	vector<edge> edge_list;
	size_t u, v;
	while (fin >> u >> v) {
		edge_list.push_back(edge(u, v));
		max_vert_idx = max(max_vert_idx, u);
		max_vert_idx = max(max_vert_idx, v);
	}
	fin.close();

	init(max_vert_idx + 1);
	add_edges(edge_list);
	return true;
}

bool uugraph::store_in_file(const string& filename) {
	return store_in_file(filename.c_str());
}

bool uugraph::store_in_file(const char *filename) {
	ofstream fout;
	fout.open(filename);

	// file could not be opened. return "error"
	if (not fout.is_open()) {
		return false;
	}

	set<edge> unique_edges;
	get_unique_edges(unique_edges);
	for (const edge& e : unique_edges) {
		fout << e.first << " " << e.second << endl;
	}

	fout.close();
	return true;
}

} // -- namespace utils
} // -- namespace dsa

