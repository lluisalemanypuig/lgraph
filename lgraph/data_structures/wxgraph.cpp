#include "wxgraph.hpp"

namespace lgraph {
namespace utils {

// PRIVATE

template<class T>
void wxgraph<T>::initialise_weights(size_t n) {
	weights = vector<weight_list<T> >(n);
}

template<class T>
void wxgraph<T>::clear_weights() {
	weights.clear();
}

// PUBLIC

template<class T>
wxgraph<T>::wxgraph() : xxgraph() { }

template<class T>
wxgraph<T>::~wxgraph() {

}

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

	// find neighbour position in the node that has less neighbours
	if (degree(u) <= degree(v)) {
		// - find neighbour position
		// - even though it is assumed that edge (u,v) exists, check it anyway
		// - return the weight
		const neighbourhood& nu = adjacency_list[u];
		size_t cit_u = get_neighbour_position(nu, v);
		assert(cit_u != nu.n_elems());
		return weights[u][cit_u];
	}

	// - find neighbour position in v's neighbourhood
	// - even though it is assumed that edge (u,v) exists, check it anyway
	// - return the weight
	const neighbourhood& nv = adjacency_list[v];
	size_t cit_v = get_neighbour_position(nv, u);
	assert(cit_v != nv.n_elems());
	return weights[v][cit_v];
}

template<class T>
const vector<T>& wxgraph<T>::get_weights(node u) const {
	vector<T> wu;
	get_weights(u, wu);
	return wu;
}

template<class T>
void wxgraph<T>::get_weights(node u, vector<T>& ws) const {
	assert( has_node(u));

	ws = weights[u];
}

} // -- namespace utils
} // -- namespace lgraph
