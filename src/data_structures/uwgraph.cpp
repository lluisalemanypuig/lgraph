#include "uwgraph.hpp"

namespace dsa {
namespace utils {

/// PRIVATE

template<class T>
void uwgraph<T>::get_unique_edges(set<pair<edge, T> >& unique_edges) const {
	const vector<neighbourhood>& ad_list = uxgraph<T>::adjacency_list;

	for (size_t i = 0; i < ad_list.size(); ++i) {

		auto w_it = weights[i].begin();
		for (ncit it = ad_list[i].begin(); it != ad_list[i].end(); ++it, ++w_it) {

			pair<edge, T> e;
			if (i < *it) {
				e = make_pair(edge(i, *it), *w_it);
			}
			else {
				e = make_pair(edge(*it, i), *w_it);
			}

			bool new_edge = unique_edges.find(e) == unique_edges.end();
			if (new_edge) {
				unique_edges.insert(e);
			}

		}
	}
}

/// MODIFIERS

template<class T>
void uwgraph<T>::initialise_weights(size_t n) {
	weights = vector<vector<T> >(n);
}

template<class T>
void uwgraph<T>::clear_weights() {
	weights.clear();
}

template<class T>
void uwgraph<T>::add_weight(node u, T w) {
	assert(u < weights.size());

	weights[u].push_back(w);
}

template<class T>
void uwgraph<T>::remove_weight(node u, nit it) {
	assert(u < weights.size());

	size_t pos = it - uxgraph<T>::adjacency_list[u].begin();
	weights[u].erase( weights[u].begin() + pos );
}

/// PUBLIC

template<class T>
uwgraph<T>::uwgraph() : uxgraph<T>() {
	uxgraph<T>::init(0);
}

template<class T>
uwgraph<T>::uwgraph(size_t n) {
	uxgraph<T>::init(n);
}

template<class T>
uwgraph<T>::~uwgraph() { }

/// OPERATORS

template<class T>
uwgraph<T>& uwgraph<T>::operator= (const uwgraph& g) {
	init(g.n_nodes());
	for (size_t i = 0; i < uxgraph<T>::adjacency_list.size(); ++i) {
		uxgraph<T>::adjacency_list[i] = g.adjacency_list[i];
		weights[i] = g.weights[i];
	}
	uxgraph<T>::num_edges = g.num_edges;
	return *this;
}

/// MODIFIERS

template<class T>
void uwgraph<T>::add_edges(const vector<edge>& edge_list, const vector<T>& ws) {
	assert(edge_list.size() == ws.size());

	for (size_t i = 0; i < edge_list.size(); ++i) {
		const edge& e = edge_list[i];
		uxgraph<T>::add_edge(e.first, e.second, ws[i]);
	}
}

/// GETTERS

template<class T>
T uwgraph<T>::edge_weight(node u, node v) const {
	assert(u < uxgraph<T>::adjacency_list.size());
	assert(v < uxgraph<T>::adjacency_list.size());
	assert(u < weights.size());
	assert(v < weights.size());

	const neighbourhood& nu = uxgraph<T>::adjacency_list[u];
	const neighbourhood& nv = uxgraph<T>::adjacency_list[v];

	// find neighbour position in u's neighbourhood
	if (nu.size() <= nv.size()) {
		// find neighbour position
		ncit cit_u = uxgraph<T>::cget_neighbour_position(nu, v);

		// even though it is assumed that edge (u,v) exists, it better check it anyway
		assert(cit_u != nu.end());

		const vector<T>& wu = weights[u];
		return wu[cit_u - nu.begin()];
	}

	// find neighbour position in v's neighbourhood
	ncit cit_v = uxgraph<T>::cget_neighbour_position(nv, u);

	// even though it is assumed that edge (u,v) exists, it better check it anyway
	assert(cit_v != nv.end());

	// return the weight
	const vector<T>& wv = weights[v];
	return wv[cit_v - nv.begin()];
}

template<class T>
void uwgraph<T>::get_weights(node u, vector<T>& ws) const {
	assert(this->has_node(u));
	assert(u < weights.size());

	ws = weights[u];
}

template<class T>
const vector<T>& uwgraph<T>::get_weights(node u) const {
	assert(this->has_node(u));
	assert(u < weights.size());

	return weights[u];
}

/// I/O

template<class T>
bool uwgraph<T>::read_from_file(const string& filename) {
	return read_from_file(filename.c_str());
}

template<class T>
bool uwgraph<T>::read_from_file(const char *filename) {

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

	uxgraph<T>::init(max_vert_idx + 1);
	add_edges(edge_list, weights);
	fin.close();
	return true;
}

template<class T>
bool uwgraph<T>::store_in_file(const string& filename) {
	return store_in_file(filename.c_str());
}

template<class T>
bool uwgraph<T>::store_in_file(const char *filename) {

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
} // -- namespace dsa

