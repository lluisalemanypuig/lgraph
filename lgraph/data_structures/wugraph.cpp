#include <lgraph/data_structures/wugraph.hpp>

// C includes
#include <assert.h>

namespace lgraph {

// PROTECTED

template<class T>
void wugraph<T>::get_unique_edges(std::vector<std::pair<edge, T> >& unique_edges) const {
	for (node i = 0; i < this->n_nodes(); ++i) {
		const neighbourhood& ni = this->adjacency_list[i];
		const weight_list<T>& wi = this->weights[i];

		auto ni_it = ni.begin();
		auto wi_it = wi.begin();
		for (; ni_it != ni.end(); ++ni_it, ++wi_it) {

			// since this graph is UNDIRECTED the order of the
			// indices in the pair does not matter
			if (i < *ni_it) {
				unique_edges.push_back( std::make_pair(edge(i, *ni_it), *wi_it) );
			}
		}
	}
}

template<class T>
void wugraph<T>::get_unique_edges(std::vector<edge>& unique_edges) const {
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
wugraph<T>::wugraph() : wxgraph<T>() { }

template<class T>
wugraph<T>::wugraph
(
	const std::vector<neighbourhood>& adj,
	const std::vector<weight_list<T> >& wl
)
: wxgraph<T>()
{
	init(adj, wl);
}

template<class T>
wugraph<T>::wugraph
(
	const std::vector<neighbourhood>& adj,
	const std::vector<weight_list<T> >& wl,
	size_t n_edges
)
: wxgraph<T>(adj,wl,n_edges)
{ }

template<class T>
wugraph<T>::~wugraph() { }

template<class T>
void wugraph<T>::init
(
	const std::vector<neighbourhood>& adj,
	const std::vector<weight_list<T> >& wl
)
{
	this->adjacency_list = adj;
	this->weights = wl;

	// count the amount of edges for only those pairs
	// of nodes (u,v) such that u < v (because this graph
	// is undirected)
	for (node u = 0; u < this->adjacency_list.size(); ++u) {
		for (node v : this->adjacency_list[u]) {
			if (u < v) {
				++this->num_edges;
			}
		}
	}
}

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
void wugraph<T>::set_edge_weight(node u, node v, const T& w) {
	assert( this->has_node(u) );
	assert( this->has_node(v) );
	assert( this->has_edge(u,v) );

	neighbourhood& nu = this->adjacency_list[u];
	weight_list<T>& wu = this->weights[u];
	neighbourhood& nv = this->adjacency_list[v];
	weight_list<T>& wv = this->weights[v];

	size_t posu = this->get_neighbour_position(nu, v);
	if (posu < nu.size()) {
		wu[posu] = w;
	}

	size_t posv = this->get_neighbour_position(nv, u);
	if (posv < nu.size()) {
		wv[posv] = w;
	}
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
void wugraph<T>::remove_node(node u) {
	assert( this->has_node(u) );

	std::vector<neighbourhood>& adj = this->adjacency_list;
	std::vector<weight_list<T> >& wei = this->weights;

	// decrease number of edges
	this->num_edges -= adj[u].size();
	// remove node u's entry from adjacency list and
	// from weight list
	adj.erase( adj.begin() + u );
	wei.erase( wei.begin() + u );

	// Remove u from every node's neighbourhood.
	// If node u is at position 'p' of node v neighbourhood
	// then delete the weight at position 'p' for the
	// weight list of node v.
	// Note that since this graph is undirected there is no
	// need to decrease the number of edges anymore.
	for (node v = 0; v < adj.size(); ++v) {
		neighbourhood& Nv = adj[v];
		weight_list<T>& Wv = wei[v];

		// find u in the list and decrease the index of
		// the corresponding nodes
		for (size_t p = Nv.size(); p > 0; --p) {
			if (Nv[p - 1] == u) {
				Nv.remove(p - 1);
				Wv.remove(p - 1);
			}
			else if (Nv[p - 1] > u) {
				// decrease index of node
				Nv[p - 1] -= 1;
			}
		}
	}
}

// GETTERS

template<class T>
bool wugraph<T>::is_directed() const {
	return false;
}

template<class T>
uxgraph *wugraph<T>::to_unweighted() const {
	uugraph *g = new uugraph(this->adjacency_list, this->num_edges);
	return g;
}

} // -- namespace lgraph
