#include <lgraph/data_structures/wugraph.hpp>

namespace lgraph {
namespace utils {

// PROTECTED

template<class T>
void wugraph<T>::get_unique_edges(set<pair<edge, T> >& unique_edges) const {
	for (node i = 0; i < this->n_nodes(); ++i) {
		const neighbourhood& ni = this->adjacency_list[i];
		const weight_list<T>& wi = this->weights[i];

		for (size_t it = 0; it < ni.n_elems(); ++it) {

			// since this graph is UNDIRECTED the order of the
			// indices in the pair does not matter
			pair<edge, T> e;
			if (i < ni[it]) {
				e = make_pair(edge(i, ni[it]), wi[i]);
			}
			else {
				e = make_pair(edge(ni[it], i), wi[i]);
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
	assert( not this->has_edge(u,v) );

	this->adjacency_list[u].add(v);
	this->adjacency_list[v].add(u);
	this->weights[u].add(w);
	this->weights[v].add(w);

	this->num_edges += 1;
}

template<class T>
void wugraph<T>::remove_edge(const edge& e) {
	remove_edge(e.first, e.second);
}

template<class T>
void wugraph<T>::remove_edge(node u, node v) {
	assert( this->has_node(u) );
	assert( this->has_node(v) );
	assert( this->has_edge(u,v) );

	bool erased = false;

	neighbourhood& nu = this->adjacency_list[u];
	weight_list<T>& wu = this->weights[u];
	neighbourhood& nv = this->adjacency_list[v];
	weight_list<T>& wv = this->weights[v];

	// find the position of node v in neighbourhood of u
	// delete the neighbour and the corresponding weight
	size_t posu = this->get_neighbour_position(nu, v);
	if (posu < nu.n_elems()) {
		nu.remove(posu);
		wu.remove(posu);
		erased = true;
	}

	// find the position of node u in neighbourhood of v
	// delete the neighbour and the corresponding weight
	size_t posv = this->get_neighbour_position(nv, u);
	if (posv < nv.n_elems()) {
		nv.remove(posv);
		wv.remove(posv);
		erased = true;
	}

	// decrease number of edges only if necessary
	if (erased) {
		this->num_edges -= 1;
	}
}

// GETTERS

template<class T>
bool wugraph<T>::has_edge(node u, node v) const {
	assert( this->has_node(u) );
	assert( this->has_node(v) );

	// since this graph is undirected, look for the neighbour
	// in the shortest neighbourhood list:
	// if u's list is the shortest then look for 'v' in it
	// if v's list is the shortest then look for 'u' in it

	const neighbourhood& nu = this->get_neighbours(u);
	const neighbourhood& nv = this->get_neighbours(v);

	if (nu.size() < nv.size()) {
		return this->get_neighbour_position(nu, v) < nu.n_elems();
	}
	else {
		return this->get_neighbour_position(nv, u) < nv.n_elems();
	}
}

template<class T>
T wugraph<T>::edge_weight(node u, node v) const {
	assert( this->has_node(u) );
	assert( this->has_node(v) );

	const neighbourhood& nu = this->adjacency_list[u];
	const neighbourhood& nv = this->adjacency_list[v];

	// find neighbour position in the node that has less neighbours
	// then:
	// - find neighbour position
	// - even though it is assumed that edge (u,v) exists, check it anyway
	// - return the weight

	if (nu.size() < nv.size()) {
		size_t cit_u = this->get_neighbour_position(nu, v);
		assert(cit_u < nu.n_elems());
		return this->weights[u][cit_u];
	}

	size_t cit_v = this->get_neighbour_position(nv, u);
	assert(cit_v < nv.n_elems());
	return this->weights[v][cit_v];
}

template<class T>
bool wugraph<T>::is_directed() const {
	return false;
}

} // -- namespace utils
} // -- namespace lgraph
