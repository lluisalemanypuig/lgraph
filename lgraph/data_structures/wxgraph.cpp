#include "wxgraph.hpp"

namespace lgraph {
namespace utils {

// PRIVATE

template<class T>
void wxgraph<T>::initialise_weights(size_t n) {
	weights = vector<vector<T> >(n);
}

template<class T>
void wxgraph<T>::clear_weights() {
	weights.clear();
}

template<class T>
void wxgraph<T>::add_weight(node u, T w) {
	assert( xxgraph::has_node(u) );

	weights[u].push_back(w);
}

template<class T>
void wxgraph<T>::remove_weight(node u, nit it) {
	assert( xxgraph::has_node(u) );

	size_t pos = it - adjacency_list[u].begin();
	weights[u].erase( weights[u].begin() + pos );
}

// PUBLIC

template<class T>
wxgraph<T>::wxgraph() : xxgraph() { }

template<class T>
wxgraph<T>::~wxgraph() { }

template<class T>
void wxgraph<T>::init(size_t n) {
	initialise_parent_graph(n);
	initialise_weights(n);
}

// OPERATORS

template<class T>
wxgraph<T>& wxgraph<T>::operator= (const wxgraph<T>& g) {
	adjacency_list = g.adjacency_list;
	weights = g.weights;
	num_edges = g.num_edges;
	return *this;
}

template<class T>
void wxgraph<T>::add_edges(const vector<edge>& edge_list, const vector<T>& ws) {
	for (size_t i = 0; i < edge_list.size(); ++i) {
		const edge& e = edge_list[i];
		add_edge(e.first, e.second, ws[i]);
	}
}

template<class T>
void wxgraph<T>::remove_edges(const vector<edge>& edge_list) {
	for (const edge& e : edge_list) {
		remove_edge(e.first, e.second);
	}
}

// MODIFIERS

template<class T>
void wxgraph<T>::clear() {
	clear_parent_graph();
	clear_weights();
}

// GETTERS

template<class T>
bool wxgraph<T>::is_weighted() const {
	return true;
}

template<class T>
T wxgraph<T>::edge_weight(node u, node v) const {
	assert( has_node(u) );
	assert( has_node(v) );

	const neighbourhood& nu = adjacency_list[u];
	const neighbourhood& nv = adjacency_list[v];

	// find neighbour position in u's neighbourhood
	if (nu.size() <= nv.size()) {
		// find neighbour position
		ncit cit_u = cget_neighbour_position(nu, v);

		// even though it is assumed that edge (u,v) exists, it better check it anyway
		assert(cit_u != nu.end());

		const vector<T>& wu = weights[u];
		return wu[cit_u - nu.begin()];
	}

	// find neighbour position in v's neighbourhood
	ncit cit_v = cget_neighbour_position(nv, u);

	// even though it is assumed that edge (u,v) exists, it better check it anyway
	assert(cit_v != nv.end());

	// return the weight
	const vector<T>& wv = weights[v];
	return wv[cit_v - nv.begin()];
}

template<class T>
void wxgraph<T>::get_weights(node u, vector<T>& ws) const {
	assert( has_node(u));

	ws = weights[u];
}

template<class T>
const vector<T>& wxgraph<T>::get_weights(node u) const {
	assert(this->has_node(u));
	assert(u < weights.size());

	return weights[u];
}

} // -- namespace utils
} // -- namespace lgraph
