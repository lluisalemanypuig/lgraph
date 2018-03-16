#include "weighted_graph.hpp"

namespace dsa {
namespace utils {

/// PRIVATE

/// PUBLIC

uwgraph::uwgraph() : abstract_graph() {
	weights = vector<T>();
}

uwgraph::uwgraph(size_t n) : abstract_graph(n) {
	weights = vector<T>(n);
}

uwgraph::~uwgraph() { }

/// OPERATORS

uwgraph& uwgraph::operator= (const uwgraph& g) {
	init(g.n_nodes());
	for (size_t i = 0; i < adjacency_list.size(); ++i) {
		adjacency_list[i] = g.adjacency_list[i];
		weights[i] = g.weights[i];
	}
	num_edges = g.num_edges;
	return *this;
}

/// MODIFIERS

void uwgraph::add_edge(const edge& e, char w) {
	__add_edge(e.first, e.second, w);
}

void uwgraph::add_edges(const vector<edge>& edge_list, const vector<T>& ws) {
	assert(edge_list.size() == ws.size());

	for (size_t i = 0; i < edge_list.size(); ++i) {
		add_edge(e.first, e.second, ws[i]);
	}
}

void uwgraph::add_edge(node u, node v, char w) {

	cout << "void uwgraph::add_edge(node u, node v, char w)" << endl;
	cout << "    -> Method not implemented yet" << endl;

}

void uwgraph::remove_edge(const edge& e) {
	remove_edge(e.first, e.second);
}

void uwgraph::remove_edges(const vector<edge>& edge_list) {
	for (const edge& e : edge_list) {
		remove_edge(e.first, e.second);
	}
}

void uwgraph::remove_edge(node u, node v) {

	cout << "void uwgraph::remove_edge(node u, node v)" << endl;
	cout << "    -> Method not implemented yet" << endl;

}

void uwgraph::clear() {
	num_edges = 0;
	for (size_t i = 0; i < adjacency_list.size(); ++i) {
		adjacency_list[i].clear();
	}
	adjacency_list.clear();
}

/// GETTERS

bool uwgraph::has_edge(node u, node v) const {
	const neighbourhood& nu = adjacency_list[u];
	const neighbourhood& nv = adjacency_list[v];

	if (nu.size() <= nv.size()) return cget_neighbour_position(nu, v) != nu.end();
	return cget_neighbour_position(nv, u) != nv.end();
}

/// I/O

bool uwgraph::read_from_file(const string& filename) {
	return read_from_file(filename.c_str());
}

bool uwgraph::read_from_file(const char *filename) {

	cout << "bool uwgraph::read_from_file(const char *filename)" << endl;
	cout << "    -> Method not implemented yet" << endl;

}

bool uwgraph::store_in_file(const string& filename) {
	return store_in_file(filename.c_str());
}

bool uwgraph::store_in_file(const char *filename) {

	cout << "bool uwgraph::store_in_file(const char *filename)" << endl;
	cout << "    -> Method not implemented yet" << endl;

}

} // -- namespace utils
} // -- namespace dsa

