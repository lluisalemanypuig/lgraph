#include "traversal.hpp"

namespace dsa {
namespace traversal {

	/// VERTEX-VERTEX

	size_t distance(const graph& G, node source, node target) {
		// distances from source to nodes
		queue<size_t> distances;
		distances.push(0);

		// current distance from source to u
		size_t current_dist;

		// distance from source to target. Set to infinite
		// for those targets not reachable from source.
		size_t st_dist = utils::inf;

		// DO terminate when target node is found. BFS guarantees that when this happens
		// the shortest distance was found
		bfs_terminate terminate =
		[&target](const graph&, node u, const vector<bool>&)
		{
			return u == target;
		};

		bfs_process_current process_current =
		[&distances, &current_dist, &target, &st_dist](const graph&, node u, const vector<bool>&)
		{
			current_dist = distances.front();
			distances.pop();
			if (u == target) {
				st_dist = current_dist;
			}
		};

		// function to compute the shortest distance from source to node v
		bfs_process_neighbour process_neighbour =
		[&distances, &current_dist](const graph&, node, node v, const vector<bool>& vis)
		{
			if (not vis[v]) {
				distances.push(current_dist + 1);
			}
		};

		BFS(G, source, terminate, process_current, process_neighbour);

		return st_dist;
	}

	size_t distance(const graph& G, node source, node target, size_t& n_paths) {
		vector<size_t> distances, paths;
		distance(G, source, distances, paths);
		n_paths = paths[target];
		return distances[target];
	}

	/// VERTEX-ALL

	void distance(const graph& G, node source, vector<size_t>& ds) {
		const size_t N = G.n_nodes();

		// distance from source to all nodes
		ds = vector<size_t>(N, inf);
		ds[source] = 0;

		// do NOT terminate: iterate through all nodes
		bfs_terminate terminate =
		[](const graph&, node, const vector<bool>&)
		{
			return false;
		};

		// don't need to process the currently visited node
		bfs_process_current process_current =
		[](const graph&, node, const vector<bool>&) { };

		// function to compute the shortest distance from source to node v
		bfs_process_neighbour process_neighbour =
		[&ds](const graph&, node u, node v, const vector<bool>&)
		{
			size_t d = ds[u] + 1;
			if (d < ds[v]) {
				ds[v] = d;
			}
		};

		BFS(G, source, terminate, process_current, process_neighbour);
	}

	void distance(const graph& G, node source, vector<size_t>& ds, vector<size_t>& n_paths) {
		const size_t N = G.n_nodes();

		// distance from source to all nodes
		ds = vector<size_t>(N, inf);
		ds[source] = 0;
		// number of paths between each pair of nodes
		n_paths = vector<size_t>(N, 0);
		n_paths[source] = 1;

		// do NOT terminate: iterate through all nodes
		bfs_terminate terminate =
		[](const graph&, node, const vector<bool>&)
		{
			return false;
		};

		// don't need to process the currently visited node
		bfs_process_current process_current =
		[](const graph&, node, const vector<bool>&) { };

		// function to compute the shortest distance from source to node v
		bfs_process_neighbour process_neighbour =
		[&ds, &n_paths](const graph&, node u, node v, const vector<bool>&)
		{
			size_t d = ds[u] + 1;
			if (d < ds[v]) {
				ds[v] = d;
				n_paths[v] = n_paths[u];
			}
			else if (d == ds[v]) {
				++n_paths[v];
			}
		};

		BFS(G, source, terminate, process_current, process_neighbour);
	}

	/// ALL-ALL

	void distances(const graph& G, vector<vector<size_t> >& dist) {
		const size_t N = G.n_nodes();

		// initialise data
		dist = vector<vector<size_t> >(N, vector<size_t>(N, utils::inf));

		// initialise with edge weights (here always 1)
		for (size_t u = 0; u < N; ++u) {
			const neighbourhood& Nu = G.get_neighbours(u);
			for (size_t v : Nu) {
				dist[u][v] = 1;
			}
		}

		// find the all-to-all distance (N^3)
		for (size_t w = 0; w < N; ++w) {
			// distance from a vertex to itself is 0
			dist[w][w] = 0;

			for (size_t u = 0; u < N; ++u) {
				for (size_t v = 0; v < N; ++v) {

					if (dist[v][w] == utils::inf or dist[w][u] == utils::inf) continue;
					if (u == v) continue;

					size_t d = dist[u][w] + dist[w][v];
					if (d < dist[u][v]) {
						dist[u][v] = dist[u][w] + dist[w][v];
					}
				}
			}
		}
	}

	void distances(const graph& G, vector<vector<size_t> >& dist, vector<vector<size_t> >& n_paths) {
		const size_t N = G.n_nodes();

		// initialise data
		dist = vector<vector<size_t> >(N, vector<size_t>(N, utils::inf));
		n_paths = vector<vector<size_t> >(N, vector<size_t>(N, 0));

		// initialise with edge weights (here always 1) the distance and the
		// number of shortest-paths from u to all its neighbours
		for (size_t u = 0; u < N; ++u) {
			const neighbourhood& Nu = G.get_neighbours(u);
			for (size_t v : Nu) {
				dist[u][v] = 1;
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

					if (dist[u][w] == utils::inf or dist[w][v] == utils::inf) continue;
					if (u == v) continue;

					size_t d = dist[u][w] + dist[w][v];
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
