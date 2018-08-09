#include "wugraph.hpp"

namespace lgraph {
namespace utils {

// PROTECTED

template<class T>
void wugraph<T>::get_unique_edges(set<pair<edge, T> >& unique_edges) const {
	for (size_t i = 0; i < wxgraph<T>::n_nodes(); ++i) {

		auto w_it = wxgraph<T>::weights[i].begin();
		const neighbourhood& neigh_i = wxgraph<T>::adjacency_list[i];

		for (ncit it = neigh_i.begin(); it != neigh_i.end(); ++it, ++w_it) {

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

// PUBLIC

template<class T>
wugraph<T>::wugraph() : wxgraph<T>() {
}

template<class T>
wugraph<T>::~wugraph() { }

// MODIFIERS

template<class T>
void wugraph<T>::add_edge(const edge& e, const T& w) {
	add_edge(e.first, e.second, w);
}

template<class T>
void wugraph<T>::add_edge(node u, node v, const T& w) {
	assert( wxgraph<T>::has_node(u) );
	assert( wxgraph<T>::has_node(v) );

	wxgraph<T>::adjacency_list[u].push_back(v);
	wxgraph<T>::adjacency_list[v].push_back(u);
	++(wxgraph<T>::num_edges);

	wxgraph<T>::add_weight(u, w);
	wxgraph<T>::add_weight(v, w);
}

template<class T>
void wugraph<T>::remove_edge(const edge& e) {
	remove_edge(e.first, e.second);
}

template<class T>
void wugraph<T>::remove_edge(node u, node v) {
	assert( wxgraph<T>::has_node(u) );
	assert( wxgraph<T>::has_node(v) );

	bool erased = false;

	neighbourhood& nu = wxgraph<T>::adjacency_list[u];
	nit it_u = wxgraph<T>::get_neighbour_position(nu, v);
	if (it_u != nu.end()) {
		nu.erase(it_u);
		wxgraph<T>::remove_weight(u, it_u);
		erased = true;
	}

	neighbourhood& nv = wxgraph<T>::adjacency_list[v];
	nit it_v = wxgraph<T>::get_neighbour_position(nv, u);
	if (it_v != nv.end()) {
		nv.erase(it_v);
		wxgraph<T>::remove_weight(v, it_v);
		erased = true;
	}

	wxgraph<T>::num_edges -= erased;
}

// GETTERS

template<class T>
void wugraph<T>::edges(vector<pair<edge, T> >& all_edges) const {
	set<pair<edge, T> > unique_edges;
	get_unique_edges(unique_edges);

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

// I/O

template<class T>
bool wugraph<T>::read_from_file(const string& filename) {
	return read_from_file(filename.c_str());
}

template<class T>
bool wugraph<T>::read_from_file(const char *filename) {

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

	wxgraph<T>::init(max_vert_idx + 1);
	wxgraph<T>::add_edges(edge_list, weights);
	fin.close();
	return true;
}

template<class T>
bool wugraph<T>::store_in_file(const string& filename) {
	return store_in_file(filename.c_str());
}

template<class T>
bool wugraph<T>::store_in_file(const char *filename) {

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
