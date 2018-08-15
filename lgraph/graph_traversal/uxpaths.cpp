#include <lgraph/graph_traversal/traversal.hpp>

namespace lgraph {
namespace traversal {

	/* VERTEX-VERTEX */

	// one path
	void uxpath(const uxgraph *G, node source, node target, node_path<_new_>& p) {
		// path from source to target starts at source
		p.add_node(source);

		// distances from source to nodes
		queue<node_path<_new_> > paths;
		paths.push(p);

		// current distance from source to u
		node_path<_new_> current_path;

		// terminate when target is found
		bfs_terminate terminate =
		[&target](const uxgraph *, node u, const vector<bool>&)
		{
			return u == target;
		};

		bfs_process_current process_current =
		[&paths, &p, &current_path, &target](const uxgraph *, node u, const vector<bool>&)
		{
			current_path = paths.front();
			paths.pop();

			if (u == target) {
				p = current_path;
			}
		};

		// function to compute the shortest distance from source to node v
		bfs_process_neighbour process_neighbour =
		[&paths, &current_path](const uxgraph *, node, node v, const vector<bool>& vis)
		{
			if (not vis[v]) {
				node_path<_new_> path_to_v = current_path;
				path_to_v.add_node(v);
				path_to_v.add_length(1);
				paths.push(path_to_v);
			}
		};

		BFS(G, source, terminate, process_current, process_neighbour);
	}

	// all paths
	void uxpaths(const uxgraph *G, node source, node target, node_path_set<_new_>& ps) {
		vector<node_path_set<_new_> > node_all_paths;
		uxpaths(G, source, node_all_paths);
		ps = node_all_paths[target];
	}

	/* VERTEX-ALL */

	// one path
	void uxpath(const uxgraph *G, node source, vector<node_path<_new_> >& ps) {
		const size_t N = G->n_nodes();

		// path from source to target
		ps = vector<node_path<_new_> >(N);
		ps[source] = node_path<_new_>(source); // start path at node 'source'

		bfs_terminate terminate =
		[](const uxgraph *, node, const vector<bool>&) { return false; };

		bfs_process_current process_current =
		[](const uxgraph *, node, const vector<bool>&) { };

		// function to compute the shortest distance from source to node v
		bfs_process_neighbour process_neighbour =
		[&ps](const uxgraph *, node u, node v, const vector<bool>&)
		{
			// add one node, count the number of edges
			size_t d_u = ps[u].size() + 1 - 1;
			// number of edges
			size_t d_v = ps[v].size() - 1;
			if (d_u < d_v) {
				ps[v] = ps[u];
				ps[v].add_node(v);
				ps[v].add_length(1);
			}
		};

		BFS(G, source, terminate, process_current, process_neighbour);
	}

	// all paths
	void uxpaths(const uxgraph *G, node source, vector<node_path_set<_new_> >& ps) {
		const size_t N = G->n_nodes();

		// all paths from source to a target
		ps = vector<node_path_set<_new_> >(N);

		// only one path from source to source
		ps[source] = node_path_set<_new_>(1);
		ps[source][0].add_node(source);

		bfs_terminate terminate =
		[](const uxgraph *, node, const vector<bool>&) { return false; };

		bfs_process_current process_current =
		[](const uxgraph *, node, const vector<bool>&) { };

		// function to compute the shortest distance from source to node v
		bfs_process_neighbour process_neighbour =
		[&ps](const uxgraph *, node u, node v, const vector<bool>&)
		{
			// distance from 'source' to 'u'
			size_t d_u;
			if (ps[u].size() == 0) {
				// not a single path from 'source' to 'u'
				d_u = utils::inf_t<_new_>();
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
				d_v = utils::inf_t<_new_>();
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
				for (node_path<_new_>& np : ps[v]) {
					np.add_node(v);
					np.add_length(1);
				}
			}
			else if (d_u == d_v) {
				// if the path found is as long as the shortest, just add it
				size_t prev_size = ps[v].size();

				// add all node paths found so far
				ps[v].insert( ps[v].end(), ps[u].begin(), ps[u].end() );

				// add another vertex to the newly added paths
				for (size_t i = prev_size; i < ps[v].size(); ++i) {
					ps[v][i].add_node(v);
					ps[v][i].add_length(1);
				}
			}
		};

		BFS(G, source, terminate, process_current, process_neighbour);
	}

	/* ALL-ALL */

	// one path
	void uxpath(const uxgraph *G, vector<vector<node_path<_new_> > >& all_all_paths) {
		const size_t N = G->n_nodes();

		// allocate memory...
		vector<vector<size_t> > dist(N, vector<size_t>(N, utils::inf_t<_new_>()));
		all_all_paths = vector<node_path_set<_new_> >(N, node_path_set<_new_>(N));

		// initialise data
		for (size_t u = 0; u < N; ++u) {

			// all paths starting at a node with degree > 0 start with that node
			for (size_t v = 0; v < N; ++v) {
				if (G->degree(u) > 0 or u == v) {
					all_all_paths[u][v].add_node(u);
				}
			}

			// initialise paths for each pair of neighbouring nodes
			const neighbourhood& Nu = G->get_neighbours(u);
			for (size_t v : Nu) {
				dist[u][v] = 1;
				all_all_paths[u][v].add_node(v);
				all_all_paths[u][v].add_length(1);
			}
		}

		// find the all-to-all shortest paths (N^3)
		for (size_t w = 0; w < N; ++w) {
			// distance from a vertex to itself is 0
			dist[w][w] = 0;

			for (size_t u = 0; u < N; ++u) {
				for (size_t v = 0; v < N; ++v) {

					// ignore the cases where:
					// the path is not moving
					if (u == v) continue;
					// the distances are infinite
					if (dist[v][w] == utils::inf_t<_new_>()) continue;
					if (dist[w][u] == utils::inf_t<_new_>()) continue;

					_new_ d = dist[u][w] + dist[w][v];
					if (d < dist[u][v]) {
						dist[u][v] = d;

						all_all_paths[u][v] = all_all_paths[u][w];
						all_all_paths[u][v].concatenate(all_all_paths[w][v]);
					}
				}
			}
		}
	}

	// all paths
	void uxpaths(const uxgraph *G, vector<vector<node_path_set<_new_> > >& all_all_paths) {
		const size_t N = G->n_nodes();

		// allocate memory...
		vector<vector<size_t> > dist(N, vector<size_t>(N, utils::inf_t<_new_>()));
		all_all_paths = vector<vector<node_path_set<_new_> > >(N, vector<node_path_set<_new_> >(N));

		// initialise with edge weights (here always 1) the distance and the
		// shortest-path from u to all its neighbours with {u,v}
		for (size_t u = 0; u < N; ++u) {
			const neighbourhood& Nu = G->get_neighbours(u);
			for (size_t v : Nu) {
				dist[u][v] = 1;
				all_all_paths[u][v] = node_path_set<_new_>(1);
				all_all_paths[u][v][0].add_node(u);
				all_all_paths[u][v][0].add_node(v);
				all_all_paths[u][v][0].add_length(1);
			}
		}

		// find all the all-to-all shortest paths (N^3)
		for (size_t w = 0; w < N; ++w) {
			// distance from a vertex to itself is 0, the path just {w}
			dist[w][w] = 0;
			all_all_paths[w][w] = node_path_set<_new_>(1, node_path<_new_>(w));

			for (size_t u = 0; u < N; ++u) {
				for (size_t v = 0; v < N; ++v) {

					if (dist[u][w] == utils::inf_t<_new_>() or dist[w][v] == utils::inf_t<_new_>()) continue;
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
							all_all_paths[u][v] = node_path_set<_new_>( n_uw*n_wv );

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
							// just add the new ones: cartesian product of
							// the current paths:
							// append to all_all_paths[u][v]
							// all_all_paths[u][w] x all_all_paths[w][v]

							size_t n_wv = all_all_paths[w][v].size();

							for (size_t wv = 0; wv < n_wv; ++wv) {
								// place iterator at the position corresponding
								// to the first added path from all_all_paths[u][w]
								size_t uv = all_all_paths[u][v].size();

								all_all_paths[u][v].insert(
									all_all_paths[u][v].end(),
									all_all_paths[u][w].begin(), all_all_paths[u][w].end()
								);

								// append each path from 'w' to 'v' to the new added paths
								for (size_t s = uv; s < all_all_paths[u][v].size(); ++s) {
									all_all_paths[u][v][s].concatenate( all_all_paths[w][v][wv] );
								}
							}
						}
					}
				}
			}
		}
	}

} // -- namespace traversal
} // -- namespace lgraph
