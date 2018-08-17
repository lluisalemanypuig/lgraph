#include <lgraph/data_structures/wdgraph.hpp>

namespace lgraph {
namespace utils {

// PROTECTED

template<class T>
void wdgraph<T>::get_unique_edges(set<pair<edge, T> >& unique_edges) const {
	for (node i = 0; i < this->n_nodes(); ++i) {
		const neighbourhood& ni = this->adjacency_list[i];
		const weight_list<T>& wi = this->weights[i];

		for (size_t ni_it = 0; ni_it < ni.n_elems(); ++ni_it) {

			// this graph is DIRECTED so an edge is the
			// pair of nodes (i,ni[ni_it]) interpreted as
			// "i points to ni[ni_it]"
			pair<edge, T> e(edge(i, ni[ni_it]), wi[ni_it]);

			bool new_edge = unique_edges.find(e) == unique_edges.end();
			if (new_edge) {
				unique_edges.insert(e);
			}

		}
	}
}

template<class T>
void wdgraph<T>::get_unique_edges(set<edge>& unique_edges) const {
	for (node i = 0; i < this->n_nodes(); ++i) {
		const neighbourhood& ni = this->adjacency_list[i];

		for (size_t ni_it = 0; ni_it < ni.n_elems(); ++ni_it) {

			// this graph is DIRECTED so an edge is the
			// pair of nodes (i,ni[it]) interpreted as
			// "i points to ni[it]"
			edge e(i, ni[ni_it]);

			bool new_edge = unique_edges.find(e) == unique_edges.end();
			if (new_edge) {
				unique_edges.insert(e);
			}

		}
	}
}

// PUBLIC

template<class T>
wdgraph<T>::wdgraph() : wxgraph<T>() {
}

template<class T>
wdgraph<T>::~wdgraph() { }

// MODIFIERS

template<class T>
void wdgraph<T>::add_edge(const edge& e, const T& w) {
	add_edge(e.first, e.second, w);
}

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
void wdgraph<T>::remove_edge(const edge& e) {
	remove_edge(e.first, e.second);
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
	if (posu < nu.n_elems()) {
		nu.remove(posu);
		wu.remove(posu);
		erased = true;
	}

	// decrease number of edges only if necessary
	if (erased) {
		this->num_edges -= 1;
	}
}

// GETTERS

template<class T>
bool wdgraph<T>::has_edge(node u, node v) const {
	assert( this->has_node(u) );
	assert( this->has_node(v) );

	const neighbourhood& nu = this->get_neighbours(u);
	return this->get_neighbour_position(nu, v) < nu.n_elems();
}

template<class T>
T wdgraph<T>::edge_weight(node u, node v) const {
	assert( this->has_node(u) );
	assert( this->has_node(v) );

	const neighbourhood& nu = this->adjacency_list[u];
	size_t cit_u = this->get_neighbour_position(nu, v);
	assert(cit_u < nu.n_elems());
	return this->weights[u][cit_u];
}

template<class T>
bool wdgraph<T>::is_directed() const {
	return true;
}

template<class T>
uxgraph *wdgraph<T>::to_unweighted() const {
	const size_t N = this->n_nodes();

	vector<edge> uedges;
	this->edges(uedges);

	for (const edge& e : uedges) {
		cout << e.first << " " << e.second << endl;
	}

	udgraph *g = new udgraph();
	g->init(N);
	g->add_edges(uedges);
	return g;
}

} // -- namespace utils
} // -- namespace lgraph
