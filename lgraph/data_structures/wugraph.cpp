#include <lgraph/data_structures/wugraph.hpp>

namespace lgraph {
namespace utils {

// PROTECTED

template<class T>
void wugraph<T>::get_unique_edges(vector<pair<edge, T> >& unique_edges) const {
	for (node i = 0; i < this->n_nodes(); ++i) {
		const neighbourhood& ni = this->adjacency_list[i];
		const weight_list<T>& wi = this->weights[i];

		auto ni_it = ni.begin();
		auto wi_it = wi.begin();
		for (; ni_it != ni.end(); ++ni_it, ++wi_it) {

			// since this graph is UNDIRECTED the order of the
			// indices in the pair does not matter
			if (i < *ni_it) {
				unique_edges.push_back( make_pair(edge(i, *ni_it), *wi_it) );
			}
		}
	}
}

template<class T>
void wugraph<T>::get_unique_edges(vector<edge>& unique_edges) const {
	for (node i = 0; i < this->n_nodes(); ++i) {

		const neighbourhood& ni = this->adjacency_list[i];
		for (node j : ni) {

			// since this graph is UNDIRECTED the order of the
			// indices in the pair does not matter
			if (i < j) {
				unique_edges.push_back( edge(i, j) );
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
	if (posu < nu.size()) {
		nu.remove(posu);
		wu.remove(posu);
		erased = true;
	}

	// find the position of node u in neighbourhood of v
	// delete the neighbour and the corresponding weight
	size_t posv = this->get_neighbour_position(nv, u);
	if (posv < nv.size()) {
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
		return this->get_neighbour_position(nu, v) < nu.size();
	}
	else {
		return this->get_neighbour_position(nv, u) < nv.size();
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
		assert(cit_u < nu.size());
		return this->weights[u][cit_u];
	}

	size_t cit_v = this->get_neighbour_position(nv, u);
	assert(cit_v < nv.size());
	return this->weights[v][cit_v];
}

template<class T>
bool wugraph<T>::is_directed() const {
	return false;
}

template<class T>
uxgraph *wugraph<T>::to_unweighted() const {
	const size_t N = this->n_nodes();

	vector<edge> uedges;
	this->edges(uedges);

	for (const edge& e : uedges) {
		cout << e.first << " " << e.second << endl;
	}

	uugraph *g = new uugraph();
	g->init(N);
	g->add_edges(uedges);
	return g;
}

} // -- namespace utils
} // -- namespace lgraph
