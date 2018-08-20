#include <lgraph/data_structures/uxgraph.hpp>

namespace lgraph {
namespace utils {

// PUBLIC

uxgraph::uxgraph() : xxgraph() { }
uxgraph::~uxgraph() { }

void uxgraph::init(size_t n) {
	initialise_parent_graph(n);
}

// OPERATORS

uxgraph& uxgraph::operator= (const uxgraph& g) {
	adjacency_list = g.adjacency_list;
	num_edges = g.num_edges;
	return *this;
}


// MODIFIERS

void uxgraph::add_edge(const edge& e) {
	add_edge(e.first, e.second);
}

void uxgraph::add_edges(const vector<edge>& edge_list) {
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

void uxgraph::edges(vector<edge>& all_edges) const {
	get_unique_edges(all_edges);
}

// I/O

bool uxgraph::read_from_file(const string& filename) {
	return read_from_file(filename.c_str());
}

bool uxgraph::read_from_file(const char *filename) {
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

bool uxgraph::store_in_file(const string& filename) {
	return store_in_file(filename.c_str());
}

bool uxgraph::store_in_file(const char *filename) {
	ofstream fout;
	fout.open(filename);

	// file could not be opened. return "error"
	if (not fout.is_open()) {
		return false;
	}

	vector<edge> unique_edges;
	get_unique_edges(unique_edges);
	for (const edge& e : unique_edges) {
		fout << e.first << " " << e.second << endl;
	}

	fout.close();
	return true;
}


} // -- namespace utils
} // -- namespace lgraph
