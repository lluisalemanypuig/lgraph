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
	set<pair<edge, T> > unique_edges;
	this->get_unique_edges(unique_edges);

	// Dump all unique edges from the set into the vector 'all_edges'.
	// The size of the vector is equal to 'num_edges'
	size_t i = 0;
	all_edges.resize(unique_edges.size());
	typename set<pair<edge, T> >::const_iterator it = unique_edges.begin();
	while (it != unique_edges.end()) {
		all_edges[i] = *it;
		++it;
		++i;
	}
}

template<class T>
void wxgraph<T>::edges(vector<edge>& all_edges) const {
	set<edge> unique_edges;
	this->get_unique_edges(unique_edges);

	// Dump all unique edges from the set into the vector 'all_edges'.
	// The size of the vector is equal to 'num_edges'
	size_t i = 0;
	all_edges.resize(unique_edges.size());
	typename set<edge>::const_iterator it = unique_edges.begin();
	while (it != unique_edges.end()) {
		all_edges[i] = *it;
		++it;
		++i;
	}
}

// I/O

template<class T>
bool wxgraph<T>::read_from_file(const string& filename) {
	return read_from_file(filename.c_str());
}

template<class T>
bool wxgraph<T>::read_from_file(const char *filename) {
	ifstream fin;
	fin.open(filename);
	if (not fin.is_open()) {
		return false;
	}

	size_t max_vert_idx = 0;
	vector<edge> edge_list;
	vector<T> weights;
	size_t u, v;
	T w;
	while (fin >> u >> v) {
		fin >> w;
		edge_list.push_back(edge(u, v));
		weights.push_back(w);
		max_vert_idx = max(max_vert_idx, u);
		max_vert_idx = max(max_vert_idx, v);
	}
	fin.close();

	this->init(max_vert_idx + 1);
	this->add_edges(edge_list, weights);
	return true;
}

template<class T>
bool wxgraph<T>::store_in_file(const string& filename) {
	return store_in_file(filename.c_str());
}

template<class T>
bool wxgraph<T>::store_in_file(const char *filename) {
	ofstream fout;
	fout.open(filename);
	if (not fout.is_open()) {
		return false;
	}

	set<pair<edge, T> > all_edges;
	get_unique_edges(all_edges);

	for (auto& p : all_edges) {
		fout << p.first.first << " " << p.first.second << " " << p.second << endl;
	}

	fout.close();
	return true;
}

} // -- namespace utils
} // -- namespace lgraph
