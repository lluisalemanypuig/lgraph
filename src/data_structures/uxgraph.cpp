#include "uxgraph.hpp"

namespace dsa {
namespace utils {

/// PROTECTED

/// MODIFIERS

template<class T>
void uxgraph<T>::initialise_adjacency_list(size_t n) {
	xxgraph<T>::adjacency_list = vector<neighbourhood>(n);
}

template<class T>
void uxgraph<T>::clear_adjacency_list() {
	xxgraph<T>::adjacency_list.clear();
}

/// PUBLIC

template<class T>
uxgraph<T>::uxgraph() : xxgraph<T>() { }

template<class T>
uxgraph<T>::~uxgraph() {

}

/// OPERATORS

/// MODIFIERS

template<class T>
void uxgraph<T>::add_edge(const edge& e, T w) {
	add_edge(e.first, e.second, w);
}

template<class T>
void uxgraph<T>::add_edge(node u, node v, T w) {
	assert(u < xxgraph<T>::adjacency_list.size());
	assert(v < xxgraph<T>::adjacency_list.size());

	xxgraph<T>::adjacency_list[u].push_back(v);
	xxgraph<T>::adjacency_list[v].push_back(u);
	++(xxgraph<T>::num_edges);

	add_weight(u, w);
	add_weight(v, w);
}

template<class T>
void uxgraph<T>::remove_edge(const edge& e) {
	remove_edge(e.first, e.second);
}

template<class T>
void uxgraph<T>::remove_edges(const vector<edge>& edge_list) {
	for (size_t i = 0; i < edge_list.size(); ++i) {
		const edge& e = edge_list[i];
		remove_edge(e.first, e.second);
	}
}

template<class T>
void uxgraph<T>::remove_edge(node u, node v) {
	assert(u < xxgraph<T>::adjacency_list.size());
	assert(v < xxgraph<T>::adjacency_list.size());

	bool erased = false;

	neighbourhood& nu = xxgraph<T>::adjacency_list[u];
	nit it_u = xxgraph<T>::get_neighbour_position(nu, v);
	if (it_u != nu.end()) {
		nu.erase(it_u);
		remove_weight(u, it_u);
		erased = true;
	}

	neighbourhood& nv = xxgraph<T>::adjacency_list[v];
	nit it_v = xxgraph<T>::get_neighbour_position(nv, u);
	if (it_v != nv.end()) {
		nv.erase(it_v);
		remove_weight(v, it_v);
		erased = true;
	}

	xxgraph<T>::num_edges -= erased;
}

/// GETTERS

template<class T>
bool uxgraph<T>::has_edge(node u, node v) const {
	assert(u < xxgraph<T>::adjacency_list.size());
	assert(v < xxgraph<T>::adjacency_list.size());

	const vector<neighbourhood>& al = xxgraph<T>::adjacency_list;
	if (al[u].size() <= al[v].size()) {
		return xxgraph<T>::cget_neighbour_position(al[u], v) != al[u].end();
	}
	return xxgraph<T>::cget_neighbour_position(al[v], u) != al[v].end();
}


} // -- namespace utils
} // -- namespace dsa
