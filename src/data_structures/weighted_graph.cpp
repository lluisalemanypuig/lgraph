#include "weighted_graph.hpp"

namespace dsa {
namespace utils {

/// PRIVATE

template<class T>
void uwgraph<T>::get_unique_edges(set<pair<edge, T> >& unique_edges) const {
	const vector<neighbourhood>& ad_list = abstract_graph<T>::adjacency_list;

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

/// PUBLIC

template<class T>
uwgraph<T>::uwgraph() : abstract_graph<T>() {
	weights = vector<vector<T> >();
}

template<class T>
uwgraph<T>::uwgraph(size_t n) : abstract_graph<T>(n) {
	weights = vector<vector<T> >(n);
}

template<class T>
uwgraph<T>::~uwgraph() { }

template<class T>
void uwgraph<T>::init(size_t n) {
	clear();
	abstract_graph<T>::adjacency_list = vector<neighbourhood>(n);
	weights = vector<vector<T> >(n);
}

/// OPERATORS

template<class T>
uwgraph<T>& uwgraph<T>::operator= (const uwgraph& g) {
	init(g.n_nodes());
	for (size_t i = 0; i < abstract_graph<T>::adjacency_list.size(); ++i) {
		abstract_graph<T>::adjacency_list[i] = g.adjacency_list[i];
		weights[i] = g.weights[i];
	}
	abstract_graph<T>::num_edges = g.num_edges;
	return *this;
}

/// MODIFIERS

template<class T>
void uwgraph<T>::add_edge(const edge& e, T w) {
	add_edge(e.first, e.second, w);
}

template<class T>
void uwgraph<T>::add_edges(const vector<edge>& edge_list, const vector<T>& ws) {
	assert(edge_list.size() == ws.size());

	for (size_t i = 0; i < edge_list.size(); ++i) {
		const edge& e = edge_list[i];
		add_edge(e.first, e.second, ws[i]);
	}
}

template<class T>
void uwgraph<T>::add_edge(node u, node v, T w) {
	abstract_graph<T>::adjacency_list[u].push_back(v);
	abstract_graph<T>::adjacency_list[v].push_back(u);

	weights[u].push_back(w);
	weights[v].push_back(w);
}

template<class T>
void uwgraph<T>::remove_edge(const edge& e) {
	remove_edge(e.first, e.second);
}

template<class T>
void uwgraph<T>::remove_edges(const vector<edge>& edge_list) {
	for (const edge& e : edge_list) {
		remove_edge(e.first, e.second);
	}
}

template<class T>
void uwgraph<T>::remove_edge(node u, node v) {

	cout << "void uwgraph<T>::remove_edge(node u, node v)" << endl;
	cout << "    -> Method not implemented yet" << endl;

}

template<class T>
void uwgraph<T>::clear() {
	abstract_graph<T>::num_edges = 0;
	for (size_t i = 0; i < abstract_graph<T>::adjacency_list.size(); ++i) {
		abstract_graph<T>::adjacency_list[i].clear();
	}
	abstract_graph<T>::adjacency_list.clear();
	weights.clear();
}

/// GETTERS

template<class T>
bool uwgraph<T>::has_edge(node u, node v) const {
	const neighbourhood& nu = abstract_graph<T>::adjacency_list[u];
	const neighbourhood& nv = abstract_graph<T>::adjacency_list[v];

	if (nu.size() <= nv.size()) {
		return abstract_graph<T>::cget_neighbour_position(nu, v) != nu.end();
	}
	return abstract_graph<T>::cget_neighbour_position(nv, u) != nv.end();
}

/// I/O

template<class T>
bool uwgraph<T>::read_from_file(const string& filename) {
	return read_from_file(filename.c_str());
}

template<class T>
bool uwgraph<T>::read_from_file(const char *filename) {

	cout << "bool uwgraph<T>::read_from_file(const char *filename)" << endl;
	cout << "    -> Method not implemented yet" << endl;

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

