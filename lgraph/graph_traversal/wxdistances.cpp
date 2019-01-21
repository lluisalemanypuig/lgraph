#include <lgraph/graph_traversal/traversal.hpp>

namespace lgraph {
namespace traversal {

/* VERTEX-VERTEX */

template<class T>
T wxdistance(const wxgraph<T> *G, node source, node target) {
	assert(G->has_node(source));
	assert(G->has_node(target));

	// distance from source to target. Set to infinite
	// for those targets not reachable from source.
	T st_dist = inf_t<T>();

	// DO terminate when target node is found. Dijkstra guarantees that
	// when this happens the shortest distance was found
	dijkstra::djka_terminate<T> terminate =
	[&target]
	(const wxgraph<T> *,const dijkstra::djka_node<T>& u, const std::vector<bool>&) -> bool
	{
		return u.second == target;
	};

	// function to retrieve the shortest distance from source to node v
	dijkstra::djka_process_current<T> proc_curr =
	[&target, &st_dist]
	(const wxgraph<T> *, const dijkstra::djka_node<T>& u, const std::vector<bool>&)
	{
		if (u.second == target) {
			st_dist = u.first;
		}
	};

	dijkstra::Dijkstra(G, source, terminate, proc_curr);

	return st_dist;
}

template<class T>
T wxdistance(const wxgraph<T> *G, node source, node target, size_t& n_paths) {
	assert(G->has_node(source));
	assert(G->has_node(target));

	std::vector<T> distances;
	std::vector<size_t> paths;
	wxdistance(G, source, distances, paths);
	n_paths = paths[target];
	return distances[target];
}

/* VERTEX-ALL */

template<class T>
void wxdistance(const wxgraph<T> *G, node source, std::vector<T>& ds) {
	assert(G->has_node(source));

	const size_t N = G->n_nodes();

	// distance from source to all nodes
	ds = std::vector<T>(N, inf_t<T>());
	ds[source] = 0;

	// do NOT terminate: iterate through all nodes
	dijkstra::djka_terminate<T> terminate =
	[](const wxgraph<T> *, const dijkstra::djka_node<T>&, const std::vector<bool>&) -> bool
	{ return false; };

	// don't need to process the currently visited node
	dijkstra::djka_process_current<T> proc_curr =
	[](const wxgraph<T> *, const dijkstra::djka_node<T>&, const std::vector<bool>&) { };

	// function to compute the shortest distance from source to node v
	dijkstra::djka_process_neighbour<T> proc_neig =
	[&ds](const wxgraph<T> *, node u, node v, T w, const std::vector<bool>&) -> bool
	{
		bool add = false;
		if (ds[u] + w < ds[v]) {
			ds[v] = ds[u] + w;
			add = true;
		}
		return add;
	};

	dijkstra::Dijkstra(G, source, terminate, proc_curr, proc_neig);
}

template<class T>
void wxdistance
(const wxgraph<T> *G, node source, std::vector<T>& ds, std::vector<size_t>& n_paths)
{
	assert(G->has_node(source));

	const size_t N = G->n_nodes();

	// distance from source to all nodes
	ds = std::vector<T>(N, inf_t<T>());
	ds[source] = 0;
	// number of paths between the source and the rest of nodes
	n_paths = std::vector<size_t>(N, 0);
	n_paths[source] = 1;

	// do NOT terminate: iterate through all nodes
	dijkstra::djka_terminate<T> terminate =
	[](const wxgraph<T> *, const dijkstra::djka_node<T>&, const std::vector<bool>&) -> bool
	{ return false; };

	// don't need to process the currently visited node
	dijkstra::djka_process_current<T> proc_curr =
	[](const wxgraph<T> *, const dijkstra::djka_node<T>&, const std::vector<bool>&) { };

	// function to compute the shortest distance from source to node v
	dijkstra::djka_process_neighbour<T> proc_neig =
	[&ds, &n_paths]
	(const wxgraph<T> *, node u, node v, const T& w, const std::vector<bool>&) -> bool
	{
		bool add = false;
		T d = ds[u] + w;
		if (d < ds[v]) {
			ds[v] = d;
			n_paths[v] = n_paths[u];
			add = true;
		}
		else if (d == ds[v]) {
			n_paths[v] += n_paths[u];
			add = true;
		}
		return add;
	};

	dijkstra::Dijkstra(G, source, terminate, proc_curr, proc_neig);
}

/* ALL-ALL */

template<class T>
void wxdistances(const wxgraph<T> *G, std::vector<std::vector<T> >& dist) {
	const size_t N = G->n_nodes();

	// initialise data
	dist = std::vector<std::vector<T> >(N, std::vector<T>(N, inf_t<T>()));

	// initialise with edge weights
	for (size_t u = 0; u < N; ++u) {
		const neighbourhood& Nu = G->get_neighbours(u);
		for (size_t v : Nu) {
			dist[u][v] = G->edge_weight(u,v);
		}
	}

	// find the all-to-all distance (N^3)
	for (size_t w = 0; w < N; ++w) {
		// distance from a vertex to itself is 0
		dist[w][w] = 0;

		for (size_t u = 0; u < N; ++u) {
			for (size_t v = 0; v < N; ++v) {

				if (u == v) continue;
				if (dist[v][w] == inf_t<T>()) continue;
				if (dist[w][u] == inf_t<T>()) continue;

				T d = dist[u][w] + dist[w][v];
				if (d < dist[u][v]) {
					dist[u][v] = d;
				}
			}
		}
	}
}

template<class T>
void wxdistances(const wxgraph<T> *G, std::vector<std::vector<T> >& dist, std::vector<std::vector<size_t> >& n_paths) {
	const size_t N = G->n_nodes();

	// initialise data
	dist = std::vector<std::vector<T> >(N, std::vector<T>(N, inf_t<T>()));
	n_paths = std::vector<std::vector<size_t> >(N, std::vector<size_t>(N, 0));

	// initialise with edge weights (here always 1) the distance and the
	// number of shortest-paths from u to all its neighbours
	for (size_t u = 0; u < N; ++u) {
		const neighbourhood& Nu = G->get_neighbours(u);
		for (size_t v : Nu) {
			dist[u][v] = G->edge_weight(u,v);
			n_paths[u][v] = 1;
		}
	}

	// find the all-to-all distance (N^3)
	for (size_t w = 0; w < N; ++w) {
		// distance from a vertex to itself is 0
		dist[w][w] = 0;
		n_paths[w][w] = 1;

		for (size_t u = 0; u < N; ++u) {
			for (size_t v = 0; v < N; ++v) {

				if (u == v) continue;
				if (dist[v][w] == inf_t<T>()) continue;
				if (dist[w][u] == inf_t<T>()) continue;

				T d = dist[u][w] + dist[w][v];
				if (d < dist[u][v]) {
					// this is a shorter path than the shortest found so far
					dist[u][v] = d;

					if (u != w and w != v) {
						n_paths[u][v] = n_paths[u][w]*n_paths[w][v];
					}
				}
				else if (d == dist[u][v]) {
					// this is a path as short as the shortest found so far
					if (u != w and w != v) {
						n_paths[u][v] += n_paths[u][w]*n_paths[w][v];
					}
				}
			}
		}
	}
}

} // -- namespace traversal
} // -- namespace lgraph
