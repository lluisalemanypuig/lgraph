#include <lgraph/data_structures/wxgraph.hpp>

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
wxgraph<T>::wxgraph(size_t n) : xxgraph() {
	init(n);
}

template<class T>
wxgraph<T>::wxgraph
(
	const vector<neighbourhood>& adj,
	const vector<weight_list<T> >& wl,
	size_t n_edges
)
: xxgraph()
{
	init(adj, wl, n_edges);
}

template<class T>
wxgraph<T>::~wxgraph() { }

template<class T>
void wxgraph<T>::init(size_t n) {
	clear();
	initialise_parent_graph(n);
	initialise_weights(n);
}

template<class T>
void wxgraph<T>::init
(
	const vector<neighbourhood>& adj,
	const vector<weight_list<T> >& wl,
	size_t n_edges
)
{
	clear();
	this->adjacency_list = adj;
	this->weights = wl;
	this->num_edges = n_edges;
}

// OPERATORS

template<class T>
wxgraph<T>& wxgraph<T>::operator= (const wxgraph<T>& g) {
	clear();
	adjacency_list = g.adjacency_list;
	weights = g.weights;
	num_edges = g.num_edges;
	return *this;
}

// MODIFIERS

template<class T>
void wxgraph<T>::add_edge(const edge& e, const T& w) {
	add_edge(e.first, e.second, w);
}

template<class T>
void wxgraph<T>::add_edges(const vector<edge>& edge_list, const vector<T>& ws) {
	for (size_t i = 0; i < edge_list.size(); ++i) {
		const edge& e = edge_list[i];
		add_edge(e.first, e.second, ws[i]);
	}
}

template<class T>
void wxgraph<T>::set_edge_weight(const edge& e, const T& w) {
	set_edge_weight(e.first, e.second, w);
}

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
const weight_list<T>& wxgraph<T>::get_weights(node u) const {
	return weights[u];
}

template<class T>
void wxgraph<T>::get_weights(node u, weight_list<T>& ws) const {
	assert( has_node(u));

	ws = weights[u];
}

template<class T>
void wxgraph<T>::edges(vector<pair<edge, T> >& all_edges) const {
	this->get_unique_edges(all_edges);
}

template<class T>
void wxgraph<T>::edges(vector<edge>& all_edges) const {
	this->get_unique_edges(all_edges);
}

} // -- namespace utils
} // -- namespace lgraph
