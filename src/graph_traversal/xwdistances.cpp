#include "traversal.hpp"

namespace dsa {
namespace traversal {

	/// VERTEX-VERTEX

	template<class T>
	T xwdistance(const xxgraph<T> *G, node source, node target) {
		assert(G->has_node(source));
		assert(G->has_node(target));

		// distance from source to target. Set to infinite
		// for those targets not reachable from source.
		T st_dist = utils::inf_t<T>();

		// DO terminate when target node is found. Dijkstra guarantees that
		// when this happens the shortest distance was found
		djka_terminate<T> terminate =
		[&target](const xxgraph<T> *, const djka_dist_node<T>& u, const vector<bool>&) -> bool
		{
			return u.second == target;
		};

		// function to retrieve the shortest distance from source to node v
		djka_process_current<T> proc_curr =
		[&target, &st_dist]
		(const xxgraph<T> *, const djka_dist_node<T>& u, const vector<bool>&)
		{
			if (u.second == target) {
				st_dist = u.first;
			}
		};

		Dijkstra(G, source, terminate, proc_curr);

		return st_dist;
	}

	template<class T>
	T xwdistance(const xxgraph<T> *G, node source, node target, size_t& n_paths) {
		assert(G->has_node(source));
		assert(G->has_node(target));

		vector<T> distances;
		vector<size_t> paths;
		xwdistance(G, source, distances, paths);
		n_paths = paths[target];
		return distances[target];
	}

	/// VERTEX-ALL

	template<class T>
	void xwdistance(const xxgraph<T> *G, node source, vector<T>& ds) {
		assert(G->has_node(source));

		const size_t N = G->n_nodes();

		// distance from source to all nodes
		ds = vector<T>(N, utils::inf_t<T>());
		ds[source] = 0;

		// do NOT terminate: iterate through all nodes
		djka_terminate<T> terminate =
		[](const xxgraph<T> *, const djka_dist_node<T>&, const vector<bool>&) -> bool
		{ return false; };

		// don't need to process the currently visited node
		djka_process_current<T> proc_curr =
		[](const xxgraph<T> *, const djka_dist_node<T>&, const vector<bool>&) { };

		// function to compute the shortest distance from source to node v
		djka_process_neighbour<T> proc_neig =
		[&ds](const xxgraph<T> *, node u, node v, T w, const vector<bool>&) -> bool
		{
			bool add = false;
			if (ds[u] + w < ds[v]) {
				ds[v] = ds[u] + w;
				add = true;
			}
			return add;
		};

		Dijkstra(G, source, terminate, proc_curr, proc_neig);
	}

	template<class T>
	void xwdistance(const xxgraph<T> *G, node source, vector<T>& ds, vector<size_t>& n_paths) {
		assert(G->has_node(source));

		const size_t N = G->n_nodes();

		// distance from source to all nodes
		ds = vector<T>(N, utils::inf_t<T>());
		ds[source] = 0;
		// number of paths between the source and the rest of nodes
		n_paths = vector<size_t>(N, 0);
		n_paths[source] = 1;

		// do NOT terminate: iterate through all nodes
		djka_terminate<T> terminate =
		[](const xxgraph<T> *, const djka_dist_node<T>&, const vector<bool>&) -> bool
		{ return false; };

		// don't need to process the currently visited node
		djka_process_current<T> proc_curr =
		[](const xxgraph<T> *, const djka_dist_node<T>&, const vector<bool>&) { };

		logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

		// function to compute the shortest distance from source to node v
		djka_process_neighbour<T> proc_neig =
		[&ds, &n_paths, &LOG](const xxgraph<T> *, node u, node v, const T& w, const vector<bool>&) -> bool
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

		Dijkstra(G, source, terminate, proc_curr, proc_neig);
	}

	/// ALL-ALL

	template<class T>
	void xwdistances(const xxgraph<T> *G, vector<vector<T> >& dist) {
		const size_t N = G->n_nodes();

		// initialise data
		dist = vector<vector<T> >(N, vector<T>(N, utils::inf_t<T>()));

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

					if (dist[v][w] == utils::inf_t<T>() or dist[w][u] == utils::inf_t<T>()) {
						continue;
					}
					if (u == v) {
						continue;
					}

					T d = dist[u][w] + dist[w][v];
					if (d < dist[u][v]) {
						dist[u][v] = dist[u][w] + dist[w][v];
					}
				}
			}
		}
	}

	template<class T>
	void xwdistances(const xxgraph<T> *G, vector<vector<T> >& dist, vector<vector<size_t> >& n_paths) {
		const size_t N = G->n_nodes();

		// initialise data
		dist = vector<vector<T> >(N, vector<T>(N, utils::inf_t<T>()));
		n_paths = vector<vector<size_t> >(N, vector<size_t>(N, 0));

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

					if (dist[u][w] == utils::inf_t<T>() or dist[w][v] == utils::inf_t<T>()) {
						continue;
					}
					if (u == v) {
						continue;
					}

					T d = dist[u][w] + dist[w][v];
					if (d < dist[u][v]) {
						// this is a shorter path than the shortest found so far
						dist[u][v] = dist[u][w] + dist[w][v];

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
} // -- namespace dsa
