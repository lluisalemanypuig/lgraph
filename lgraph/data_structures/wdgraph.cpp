#include <lgraph/data_structures/wdgraph.hpp>

namespace lgraph {

// PROTECTED

template<class T>
void wdgraph<T>::get_unique_edges(std::vector<std::pair<edge, T> >& unique_edges) const {
	for (node i = 0; i < this->n_nodes(); ++i) {
		const neighbourhood& ni = this->adjacency_list[i];
		const weight_list<T>& wi = this->weights[i];

		auto ni_it = ni.begin();
		auto wi_it = wi.begin();
		for (; ni_it != ni.end(); ++ni_it, ++wi_it) {

			// this graph is DIRECTED so an edge is the
			// pair of nodes (i,ni[ni_it]) interpreted as
			// "i points to ni[ni_it]"
			unique_edges.push_back( std::make_pair(edge(i, *ni_it), *wi_it) );
		}
	}
}

template<class T>
void wdgraph<T>::get_unique_edges(std::vector<edge>& unique_edges) const {
	for (node i = 0; i < this->n_nodes(); ++i) {

		const neighbourhood& ni = this->adjacency_list[i];
		for (node j : ni) {

			// this graph is DIRECTED so an edge is the
			// pair of nodes (i, j) interpreted as
			// "i points to j"
			unique_edges.push_back( std::make_pair(i,j) );
		}
	}
}

// PUBLIC

template<class T>
wdgraph<T>::wdgraph() : wxgraph<T>() { }

template<class T>
wdgraph<T>::wdgraph
(
	const std::vector<neighbourhood>& adj,
	const std::vector<weight_list<T> >& wl
)
: wxgraph<T>()
{
	init(adj, wl);
}

template<class T>
wdgraph<T>::wdgraph
(
	const std::vector<neighbourhood>& adj,
	const std::vector<weight_list<T> >& wl,
	size_t n_edges
)
: wxgraph<T>(adj,wl,n_edges)
{ }

template<class T>
wdgraph<T>::~wdgraph() { }

template<class T>
void wdgraph<T>::init
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
		this->num_edges += this->adjacency_list[u].size();
	}
}

// MODIFIERS

template<class T>
void wdgraph<T>::add_edge(node u, node v, const T& w) {
	assert( this->has_node(u) );
	assert( this->has_node(v) );
	assert( not this->has_edge(u,v) );

	this->adjacency_list[u].add(v);
	this->weights[u].add(w);

	this->num_edges += 1;
}

template<class T>
void wdgraph<T>::set_edge_weight(node u, node v, const T& w) {
	assert( this->has_node(u) );
	assert( this->has_node(v) );
	assert( this->has_edge(u,v) );

	neighbourhood& nu = this->adjacency_list[u];
	weight_list<T>& wu = this->weights[u];

	size_t posu = this->get_neighbour_position(nu, v);
	if (posu < nu.size()) {
		wu[posu] = w;
	}
}

template<class T>
void wdgraph<T>::remove_edge(node u, node v) {
	assert( this->has_node(u) );
	assert( this->has_node(v) );
	assert( this->has_edge(u,v) );

	bool erased = false;

	neighbourhood& nu = this->adjacency_list[u];
	weight_list<T>& wu = this->weights[u];

	// find the position of node v in neighbourhood of u
	// delete the neighbour and the corresponding weight
	size_t posu = this->get_neighbour_position(nu, v);
	if (posu < nu.size()) {
		nu.remove(posu);
		wu.remove(posu);
		erased = true;
	}

	// decrease number of edges only if necessary
	if (erased) {
		this->num_edges -= 1;
	}
}

template<class T>
void wdgraph<T>::remove_node(node u) {
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
	// Note that since this graph is directed we need to
	// decrease the number of edges at each step
	for (node v = 0; v < adj.size(); ++v) {
		neighbourhood& Nv = adj[v];
		weight_list<T>& Wv = wei[v];

		// find u in the list and decrease the index of
		// the corresponding nodes
		for (size_t p = Nv.size(); p > 0; --p) {
			if (Nv[p - 1] == u) {
				Nv.remove(p - 1);
				Wv.remove(p - 1);
				this->num_edges -= 1;
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
bool wdgraph<T>::has_edge(node u, node v) const {
	assert( this->has_node(u) );
	assert( this->has_node(v) );

	const neighbourhood& nu = this->get_neighbours(u);
	return this->get_neighbour_position(nu, v) < nu.size();
}

template<class T>
T wdgraph<T>::edge_weight(node u, node v) const {
	assert( this->has_node(u) );
	assert( this->has_node(v) );

	const neighbourhood& nu = this->adjacency_list[u];
	size_t cit_u = this->get_neighbour_position(nu, v);
	assert(cit_u < nu.size());

	return this->weights[u][cit_u];
}

template<class T>
bool wdgraph<T>::is_directed() const {
	return true;
}

template<class T>
uxgraph *wdgraph<T>::to_unweighted() const {
	udgraph *g = new udgraph(this->adjacency_list, this->num_edges);
	return g;
}

} // -- namespace lgraph
