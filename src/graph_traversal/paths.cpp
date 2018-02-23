#include "traversal.hpp"

namespace dsa {
namespace traversal {

	/// VERTEX-VERTEX

	void path(const graph& G, node source, node target, node_path& p) {
		// terminate when target is found
		bfs_terminate terminate =
		[&target](const graph&, node u, const vector<bool>&)
		{
			return u == target;
		};

		// path from source to target starts at source
		p.push_back(source);

		// distances from source to nodes
		queue<node_path> paths;
		paths.push(p);

		// current distance from source to u
		node_path current_path;

		bfs_process_current process_current =
		[&paths, &p, &current_path, &target](const graph&, node u, const vector<bool>&)
		{
			current_path = paths.front();
			paths.pop();

			if (u == target) {
				p = current_path;
			}
		};

		// function to compute the shortest distance from source to node v
		bfs_process_neighbour process_neighbour =
		[&paths, &current_path](const graph&, node, node v, const vector<bool>& vis)
		{
			if (not vis[v]) {
				node_path path_to_v = current_path;
				path_to_v.push_back(v);
				paths.push(path_to_v);
			}
		};

		BFS(G, source, terminate, process_current, process_neighbour);
	}

	void path(const graph& G, node source, node target, node_path_set& ps) {
		vector<node_path_set> node_all_paths;
		path(G, source, node_all_paths);
		ps = node_all_paths[target];
	}

	/// VERTEX-ALL

	void path(const graph& G, node source, vector<node_path>& ps) {
		const size_t N = G.n_nodes();

		bfs_terminate terminate =
		[](const graph&, node, const vector<bool>&)
		{
			return false;
		};

		// path from source to target
		ps = vector<node_path>(N);
		ps[source] = node_path(1);
		ps[source][0] = source;

		bfs_process_current process_current =
		[](const graph&, node, const vector<bool>&)
		{ };

		// function to compute the shortest distance from source to node v
		bfs_process_neighbour process_neighbour =
		[&ps](const graph&, node u, node v, const vector<bool>&)
		{
			// add one node, count the number of edges
			size_t d_u = ps[u].size() + 1 - 1;
			// number of edges
			size_t d_v = ps[v].size() - 1;
			if (d_u < d_v) {
				ps[v] = ps[u];
				ps[v].push_back(v);
			}
		};

		BFS(G, source, terminate, process_current, process_neighbour);
	}

	void path(const graph& G, node source, vector<node_path_set>& ps) {
		const size_t N = G.n_nodes();

		bfs_terminate terminate =
		[](const graph&, node, const vector<bool>&)
		{
			return false;
		};

		// all paths from source to a target
		ps = vector<node_path_set>(N);

		// only one path from source to source
		ps[source] = node_path_set(1);
		ps[source][0] = node_path(1, source);

		bfs_process_current process_current =
		[](const graph&, node, const vector<bool>&)
		{ };

		// function to compute the shortest distance from source to node v
		bfs_process_neighbour process_neighbour =
		[&ps](const graph&, node u, node v, const vector<bool>&)
		{
			// distance from 'source' to 'u'
			size_t d_u;
			if (ps[u].size() == 0) {
				// not a single path from 'source' to 'u'
				d_u = utils::inf;
			}
			else {
				// at least one path from 'source' to 'u'

				// add one node, count the number of edges,
				// path from 'source' to 'u' to 'v'
				d_u = ps[u][0].size() + 1 - 1;
			}

			// distance from 'source' to 'v'
			size_t d_v;
			if (ps[v].size() == 0) {
				// not a single path from 'source' to 'u'
				d_v = utils::inf;
			}
			else {
				// at least one path from 'source' to 'u'

				// number of edges
				// path from 'source' to 'v'
				d_v = ps[v][0].size() - 1;
			}

			if (d_u < d_v) {
				// if shorter path found, clear all paths to 'v' and add the new ones.
				ps[v] = ps[u];
				for (node_path& np : ps[v]) {
					np.push_back(v);
				}
			}
			else if (d_u == d_v) {
				// if the path found is as long as the shortest, just add it
				size_t prev_size = ps[v].size();
				ps[v].insert( ps[v].end(), ps[u].begin(), ps[u].end() );
				for (size_t i = prev_size; i < ps[v].size(); ++i) {
					ps[v][i].push_back(v);
				}
			}
		};

		BFS(G, source, terminate, process_current, process_neighbour);
	}

	/// ALL-ALL

	void paths(const graph& G, vector<vector<node_path> >& all_all_paths) {
		const size_t N = G.n_nodes();

		// allocate memory
		vector<vector<size_t> > dist(N, vector<size_t>(N, utils::inf));
		all_all_paths = vector<vector<node_path> >(N, vector<node_path>(N));

		// initialise data
		for (size_t u = 0; u < N; ++u) {

			// all paths starting at a node with degree > 0 start with that node
			for (size_t v = 0; v < N; ++v) {
				if (G.degree(u) > 0 or u == v) {
					all_all_paths[u][v].push_back(u);
				}
			}

			// initialise paths for each pair of neighbouring nodes
			const neighbourhood& Nu = G.get_neighbours(u);
			for (size_t v : Nu) {
				dist[u][v] = 1;
				all_all_paths[u][v].push_back(v);
			}
		}

		// find the all-to-all paths (N^3)
		for (size_t w = 0; w < N; ++w) {
			// distance from a vertex to itself is 0
			dist[w][w] = 0;

			for (size_t u = 0; u < N; ++u) {
				for (size_t v = 0; v < N; ++v) {

					if (dist[v][w] == utils::inf or dist[w][u] == utils::inf) continue;
					if (u == v) continue;

					if (dist[u][v] > dist[u][w] + dist[w][v]) {
						dist[u][v] = dist[u][w] + dist[w][v];

						all_all_paths[u][v] = all_all_paths[u][w];
						all_all_paths[u][v].concatenate(all_all_paths[w][v]);
					}
				}
			}
		}
	}

	void paths(const graph& G, vector<vector<node_path_set> >& all_all_paths) {
		const size_t N = G.n_nodes();

		// initialise data
		vector<vector<size_t> > dist(N, vector<size_t>(N, utils::inf));
		all_all_paths = vector<vector<node_path_set> >(N, vector<node_path_set>(N));

		// initialise with edge weights (here always 1) the distance and the
		// shortest-path from u to all its neighbours with {u,v}
		for (size_t u = 0; u < N; ++u) {
			const neighbourhood& Nu = G.get_neighbours(u);
			for (size_t v : Nu) {
				dist[u][v] = 1;
				all_all_paths[u][v] = node_path_set(1);
				all_all_paths[u][v][0].push_back(u);
				all_all_paths[u][v][0].push_back(v);
			}
		}

		// find the all-to-all distance (N^3)
		for (size_t w = 0; w < N; ++w) {
			// distance from a vertex to itself is 0, the path just {w}
			dist[w][w] = 0;
			all_all_paths[w][w] = node_path_set(1, node_path(1, w));

			for (size_t u = 0; u < N; ++u) {
				for (size_t v = 0; v < N; ++v) {

					if (dist[u][w] == utils::inf or dist[w][v] == utils::inf) continue;
					if (u == v) continue;

					size_t d = dist[u][w] + dist[w][v];
					if (d < dist[u][v]) {
						// this is a shorter path than the shortest found so far
						dist[u][v] = dist[u][w] + dist[w][v];

						if (u != w and w != v) {
							// concatenate each path {u, ..., w}
							// with each path {w, ..., v} (without repeating the w)

							size_t n_uw = all_all_paths[u][w].size();
							size_t n_wv = all_all_paths[w][v].size();

							all_all_paths[u][v] = node_path_set( n_uw*n_wv );

							size_t uv = 0;
							for (size_t uw = 0; uw < n_uw; ++uw) {
								for (size_t wv = 0; wv < n_wv; ++wv) {
									all_all_paths[u][v][uv] = all_all_paths[u][w][uw];
									all_all_paths[u][v][uv].concatenate( all_all_paths[w][v][wv] );
									++uv;
								}
							}
						}
					}
					else if (d == dist[u][v]) {
						// this is a path as short as the shortest found so far
						if (u != w and w != v) {
							// if the path found is as long as the shortest,
							// just add the new ones as before

							size_t n_uw = all_all_paths[u][w].size();
							size_t n_wv = all_all_paths[w][v].size();

							for (size_t uw = 0; uw < n_uw; ++uw) {
								// add all paths from u to w into the path set of 'u to v'
								all_all_paths[u][v].insert(
									all_all_paths[u][v].end(),
									all_all_paths[u][w].begin(), all_all_paths[u][w].end()
								);

								// concatenate to the newly added paths the paths from w to v
								size_t uv = all_all_paths[u][v].size() - n_uw - 1;
								for (size_t wv = 0; wv < n_wv; ++wv) {
									all_all_paths[u][v][uv].concatenate( all_all_paths[w][v][wv] );
									++uv;
								}
							}
						}
					}
				}
			}
		}
	}

} // -- namespace traversal
} // -- namespace dsa
