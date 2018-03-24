#include "graph.hpp"

namespace dsa {
namespace utils {

/// PRIVATE

void uugraph::__add_edge(const edge& e) {
	__add_edge(e.first, e.second);
}

void uugraph::__add_edges(const vector<edge>& edge_list) {
	for (const edge& E : edge_list) {
		__add_edge(E.first, E.second);
	}
}

void uugraph::__add_edge(node u, node v) {
	assert(u < adjacency_list.size());
	assert(v < adjacency_list.size());

	adjacency_list[u].push_back(v);
	adjacency_list[v].push_back(u);
	++num_edges;
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

uugraph::uugraph() : abstract_graph() {
}

uugraph::uugraph(size_t n) : abstract_graph(n) {

}

uugraph::~uugraph() { }

void uugraph::init(size_t n) {
	clear();
	adjacency_list = vector<neighbourhood>(n);
}

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

void uugraph::add_edge(const edge& e, char w) {
	UNUSED(w); __add_edge(e);
}

void uugraph::add_edges(const vector<edge>& edge_list, const vector<char>& ws) {
	UNUSED(ws); __add_edges(edge_list);
}

void uugraph::add_edge(node u, node v, char w) {
	UNUSED(w); __add_edge(u, v);
}

void uugraph::remove_edge(const edge& e) {
	remove_edge(e.first, e.second);
}

void uugraph::remove_edges(const vector<edge>& edge_list) {
	for (const edge& e : edge_list) {
		remove_edge(e.first, e.second);
	}
}
	
void uugraph::remove_edge(node u, node v) {
	assert(u < adjacency_list.size());
	assert(v < adjacency_list.size());

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

void uugraph::clear() {
	num_edges = 0;
	for (size_t i = 0; i < adjacency_list.size(); ++i) {
		adjacency_list[i].clear();
	}
	adjacency_list.clear();
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

