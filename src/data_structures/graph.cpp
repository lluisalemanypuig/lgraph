#include "graph.hpp"

namespace dsa {
namespace utils {

/// PRIVATE

lcit graph::cget_neighbour_position(const neighbourhood& n, node u) const {
	bool found = false;
	lcit cit = n.begin();
	while (cit != n.end() and not found) {
		if (*cit == u) found = true;
		else ++cit;
	}
	return cit;
}

lit graph::get_neighbour_position(neighbourhood& n, node u) {
	bool found = false;
	lit it = n.begin();
	while (it != n.end() and not found) {
		if (*it == u) found = true;
		else ++it;
	}
	return it;
}

/// PUBLIC

graph::graph() {
	num_edges = 0;
}

graph::graph(size_t n) {
	num_edges = 0;
	adjacency_list = vector<neighbourhood>(n);
}

graph::~graph() { }

void graph::init(size_t n) {
	clear();
	adjacency_list = vector<neighbourhood>(n);
}

/// OPERATORS

graph& graph::operator= (const graph& g) {
	init(g.n_nodes());
	for (size_t i = 0; i < adjacency_list.size(); ++i) {
		adjacency_list[i] = g.adjacency_list[i];
	}
	num_edges = g.num_edges;
	return *this;
}

/// SETTERS

size_t graph::add_node() {
	adjacency_list.push_back(neighbourhood());
	return adjacency_list.size() - 1;
}

size_t graph::add_n_nodes(node n) {
	adjacency_list.insert(adjacency_list.end(), n, neighbourhood());
	return adjacency_list.size() - 1;
}

void graph::add_edge(const edge& e) {
	add_edge(e.first, e.second);
}

void graph::add_edge(node u, node v) {
	adjacency_list[u].push_back(v);
	adjacency_list[v].push_back(u);
	++num_edges;
}

void graph::remove_edge(const edge& e) {
	remove_edge(e.first, e.second);
}
	
void graph::remove_edge(node u, node v) {
	bool erased = false;
	
	neighbourhood& nu = adjacency_list[u];
	lit it_u = get_neighbour_position(nu, v);
	if (it_u != nu.end()) {
		nu.erase(it_u);
		erased = true;
	}
	
	neighbourhood& nv = adjacency_list[v];
	lit it_v = get_neighbour_position(nv, u);
	if (it_v != nv.end()) {
		nv.erase(it_v);
		erased = true;
	}
	
	num_edges -= erased;
}

void graph::clear() {
	num_edges = 0;
	for (size_t i = 0; i < adjacency_list.size(); ++i) {
		adjacency_list[i].clear();
	}
	adjacency_list.clear();
}

/// GETTERS

bool graph::has_node(node u) const {
	return u < adjacency_list.size();
}

bool graph::has_edge(node u, node v) const {
	const neighbourhood& nu = adjacency_list[u];
	const neighbourhood& nv = adjacency_list[v];
	
	if (nu.size() <= nv.size()) return cget_neighbour_position(nu, v) != nu.end();
	return cget_neighbour_position(nv, u) != nv.end();
}

size_t graph::n_nodes() const {
	return adjacency_list.size();
}

size_t graph::n_edges() const {
	return num_edges;
}

void graph::nodes(vector<node>& all_nodes) const {
	all_nodes.resize(adjacency_list.size());
	for (size_t u = 0; u < all_nodes.size(); ++u) all_nodes[u] = u;
}

void graph::edges(vector<edge>& all_edges) const {
	set<edge> unique_edges;
	
	// insert all edges into a set to get only those that are unique
	for (size_t i = 0; i < adjacency_list.size(); ++i) {
		lcit it = adjacency_list[i].begin();
		while (it != adjacency_list[i].end()) {
			
			edge e;
			if (i < *it) e = edge(i, *it);
			else e = edge(*it, i);
			
			bool new_edge = unique_edges.find(e) == unique_edges.end();
			if (new_edge) unique_edges.insert(e);
			++it;
		}
	}
	
	// Dump all unique edges from the set into the vector 'all_edges'.
	// The size of the vector is equal to 'num_edges'
	size_t i = 0;
	all_edges.resize(unique_edges.size());
	set<edge>::const_iterator it = unique_edges.begin();
	while (it != unique_edges.end()) {
		all_edges[i] = *it;
		++it;
		++i;
	}
}

const neighbourhood& graph::get_neighbours(node u) const {
	return adjacency_list[u];
}

size_t graph::degree(node u) const {
	return adjacency_list[u].size();
}

/// CHARCATERISTICS OF THE GRAPH

void graph::get_degree_sequence(map<node, node>& deg_seq) const {
	for (size_t u = 0; u < adjacency_list.size(); ++u) {
		size_t deg = degree(u);
		if (deg_seq.find(deg) == deg_seq.end()) deg_seq[deg] = 1;
		else ++deg_seq[deg];
	}
}

size_t graph::n_triangles() const {
	size_t tris = 0;
	const size_t N = n_nodes();
	
	for (size_t u = 0; u < N; ++u) {
		
		const neighbourhood& Nu = get_neighbours(u);
		lcit v = Nu.begin();
		for (; v != Nu.end(); ++v) {
			
			lcit w = v; ++w;
			for (; w != Nu.end(); ++w) {
				
				// existing edges: (u, v), (u, w)
				// check edge (v, w) for triangles
				
				if (has_edge(*v, *w)) ++tris;
			}
		}
		
	}
	
	// Each triangle is counted three times
	return tris/3;
}

void graph::dist_all_to_all(vector<vector<size_t> >& dist) const {
	const size_t N = adjacency_list.size();
	logger<null_stream>& LOG = logger<null_stream>::get_logger();

	auto print_dist_matrix = [&]() {

		const size_t max_node_length = std::to_string(N - 1).length();
		vector<size_t> max_column(N, 0);
		for (size_t u = 0; u < N; ++u) {
			for (size_t v = 0; v < N; ++v) {
				size_t dist_length = std::to_string(dist[v][u]).length();
				if (dist[v][u] == utils::inf) {
					dist_length = 2; // use '-1'
				}

				max_column[u] = max(max_column[u], dist_length);
			}
			max_column[u] = max(max_column[u], std::to_string(u).length());
		}
		LOG.log() << "Distance information:" << endl;
		LOG.log() << setw(max_node_length) << " " << " ";
		for (size_t u = 0; u < N; ++u) {
			LOG.log() << setw(max_column[u]) << u << " ";
		}
		LOG.log() << endl;

		for (size_t u = 0; u < N; ++u) {
			LOG.log() << setw(max_node_length) << u << " ";
			for (size_t v = 0; v < N; ++v) {
				LOG.log() << setw(max_column[v]);
				if (dist[u][v] == utils::inf) {
					LOG.log() << -1;
				}
				else {
					LOG.log() << dist[u][v];
				}

				LOG.log() << " ";
			}
			LOG.log() << endl;
		}
		LOG.log() << endl;
	};

	dist = vector<vector<size_t> >(N, vector<size_t>(N, utils::inf));

	// initialise with edge weights (here always 1)
	for (size_t u = 0; u < N; ++u) {
		const neighbourhood& Nu = get_neighbours(u);
		for (size_t v : Nu) {
			dist[u][v] = 1;
		}
	}

	LOG.log() << "After initialisation" << endl;
	print_dist_matrix();

	// find the all-to-all distance (N^3)
	for (size_t w = 0; w < N; ++w) {
		// distance from a vertex to itself is 0
		dist[w][w] = 0;

		for (size_t v = 0; v < N; ++v) {
			for (size_t u = 0; u < N; ++u) {

				if (dist[u][w] == utils::inf or dist[w][v] == utils::inf) continue;

				if (dist[u][v] > dist[u][w] + dist[w][v]) {
					dist[u][v] = dist[u][w] + dist[w][v];
				}
			}
		}
	}

	print_dist_matrix();

}

} // -- namespace utils
} // -- namespace dsa

