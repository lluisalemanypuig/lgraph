#include "wugraph.hpp"

namespace lgraph {
namespace utils {

// PROTECTED

template<class T>
void wugraph<T>::get_unique_edges(set<pair<edge, T> >& unique_edges) const {
	for (node i = 0; i < this->n_nodes(); ++i) {

		auto w_it = this->weights[i].begin();
		const neighbourhood& neigh_i = this->adjacency_list[i];

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
	assert( this->has_node(u) );
	assert( this->has_node(v) );

	this->adjacency_list[u].push_back(v);
	this->adjacency_list[v].push_back(u);
	++(this->num_edges);

	this->weights[u].push_back(w);
	this->weights[v].push_back(w);
}

template<class T>
void wugraph<T>::remove_edge(const edge& e) {
	remove_edge(e.first, e.second);
}

template<class T>
void wugraph<T>::remove_edge(node u, node v) {
	assert( this->has_node(u) );
	assert( this->has_node(v) );

	bool erased = false;

	neighbourhood& nu = this->adjacency_list[u];
	nit it_u = this->get_neighbour_position(nu, v);
	if (it_u != nu.end()) {
		nu.erase(it_u);

		// compute the position (in 0, 1, 2, ...)
		size_t pos = it_u - this->adjacency_list[u].begin();
		// delete the element using an iterator
		this->weights[u].erase(this->weights[u].begin() + pos);

		erased = true;
	}

	neighbourhood& nv = this->adjacency_list[v];
	nit it_v = this->get_neighbour_position(nv, u);
	if (it_v != nv.end()) {
		nv.erase(it_v);

		// compute the position (in 0, 1, 2, ...)
		size_t pos = it_v - this->adjacency_list[v].begin();
		// delete the element using an iterator
		this->weights[v].erase(this->weights[v].begin() + pos);

		erased = true;
	}

	this->num_edges -= erased;
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

	this->init(max_vert_idx + 1);
	this->add_edges(edge_list, weights);
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
