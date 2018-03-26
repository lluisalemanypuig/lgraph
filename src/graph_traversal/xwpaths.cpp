#include "traversal.hpp"

namespace dsa {
namespace traversal {

	/// VERTEX-VERTEX

	template<class T>
	void xwpath(const xxgraph<T> *G, node source, node target, node_path<T>& p) {
		assert(G->has_node(source));
		assert(G->has_node(target));

		const size_t N = G->n_nodes();

		// prev[v] = u: previous node of v in the path is u
		vector<node> prev(N, N + 1);
		vector<T> ds(N, utils::inf_t<T>());
		ds[source] = 0;

		// terminate when target is found
		djka_terminate<T> terminate =
		[&target](const xxgraph<T> *, const djka_dist_node<T>& u, const vector<bool>&) -> bool
		{
			return u.second == target;
		};

		djka_process_current<T> proc_curr =
		[] (const xxgraph<T> *, const djka_dist_node<T>&, const vector<bool>&) -> void { };

		// function to compute the shortest distance from node u to node v
		djka_process_neighbour<T> proc_neig =
		[&prev, &ds]
		(const xxgraph<T> *, node u, node v, const T& w, const vector<bool>&) -> bool
		{
			bool add = false;
			if (ds[u] + w < ds[v]) {
				ds[v] = ds[u] + w;
				prev[v] = u;
				add = true;
			}
			return add;
		};

		Dijkstra(G, source, terminate, proc_curr, proc_neig);

		p.empty();
		node l = target;
		while (l != source) {
			p.add_node(l);
			l = prev[l];
		}
		p.add_node(source);
		p.reverse();
		p.set_length(ds[target]);
	}

	template<class T>
	void xwpath(const xxgraph<T> *G, node source, node target, node_path_set<T>& ps) {
		// all paths from source to the other nodes
		vector<node_path_set<T> > node_all_paths;
		xwpath(G, source, node_all_paths);
		ps = node_all_paths[target];
	}

	/// VERTEX-ALL

	template<class T>
	void xwpath(const xxgraph<T> *G, node source, vector<node_path<T> >& ps) {
		assert(G->has_node(source));

		const size_t N = G->n_nodes();

		// prev[v] = u: previous node of v in the path is u
		vector<node> prev(N, N + 1);
		vector<T> ds(N, utils::inf_t<T>());
		ds[source] = 0;

		// terminate when target is found
		djka_terminate<T> terminate =
		[](const xxgraph<T> *, const djka_dist_node<T>&, const vector<bool>&) -> bool
		{ return false; };

		djka_process_current<T> proc_curr =
		[] (const xxgraph<T> *, const djka_dist_node<T>&, const vector<bool>&) -> void { };

		// function to compute the shortest distance from node u to node v
		djka_process_neighbour<T> proc_neig =
		[&prev, &ds]
		(const xxgraph<T> *, node u, node v, const T& w, const vector<bool>&) -> bool
		{
			bool add = false;
			if (ds[u] + w < ds[v]) {
				ds[v] = ds[u] + w;
				prev[v] = u;
				add = true;
			}
			return add;
		};

		Dijkstra(G, source, terminate, proc_curr, proc_neig);

		ps = vector<node_path<T> >(N);
		for (node u = 0; u < N; ++u) {
			node_path<T>& p = ps[u];

			p.empty();
			node l = u;
			while (l != source) {
				p.add_node(l);
				l = prev[l];
			}
			p.add_node(source);
			p.reverse();
			p.set_length(ds[u]);
		}
	}

	template<class T>
	void xwpath(const xxgraph<T> *G, node source, vector<node_path_set<T> >& ps) {
		/*
		const size_t N = G->n_nodes();

		// all paths from source to a target
		ps = vector<node_path_set<T> >(N);

		// only one path from source to source
		ps[source] = node_path_set<T>(1);
		ps[source][0] = node_path(1, source);

		function<bool (const abstract_graph<T> *, node, const vector<bool>&)> terminate =
		[](const abstract_graph<T> *, node, const vector<bool>&) { return false; };

		function<void (const abstract_graph<T> *, node, const vector<bool>&)> proc_curr =
		[](const abstract_graph<T> *, node, const vector<bool>&) { };

		// function to compute the shortest distance from source to node v
		function<void (const abstract_graph<T> *, node, node, const vector<bool>&)> proc_neig =
		[&ps](const abstract_graph<T> *, node u, node v, const vector<bool>&)
		{
			// distance from 'source' to 'u'
			T d_u;
			if (ps[u].size() == 0) {
				// not a single path from 'source' to 'u'
				d_u = utils::inf_t<T>();
			}
			else {
				// at least one path from 'source' to 'u'

				// add one node, count the number of edges,
				// path from 'source' to 'u' to 'v'
				d_u = ps[u][0].size() + 1 - 1;
			}

			// distance from 'source' to 'v'
			T d_v;
			if (ps[v].size() == 0) {
				// not a single path from 'source' to 'u'
				d_v = utils::z_inf;
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
				for (node_path<T>& np : ps[v]) {
					np.push_back(v);
				}
			}
			else if (d_u == d_v) {
				// if the path found is as long as the shortest, just add it
				T prev_size = ps[v].size();

				// add all node paths found so far
				ps[v].insert( ps[v].end(), ps[u].begin(), ps[u].end() );

				// add another vertex to the newly added paths
				for (size_t i = prev_size; i < ps[v].size(); ++i) {
					ps[v][i].push_back(v);
				}
			}
		};

		BFS(G, source, terminate, proc_curr, proc_neig);
		*/
	}

	/// ALL-ALL

	template<class T>
	void xwpaths(const xxgraph<T> * G, vector<node_path_set<T> >& all_all_paths) {
		/*
		const size_t N = G.n_nodes();

		// allocate memory...
		vector<vector<size_t> > dist(N, vector<size_t>(N, utils::z_inf));
		all_all_paths = vector<node_path_set<T> >(N, node_path_set<T>(N));

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

		// find the all-to-all shortest paths (N^3)
		for (size_t w = 0; w < N; ++w) {
			// distance from a vertex to itself is 0
			dist[w][w] = 0;

			for (size_t u = 0; u < N; ++u) {
				for (size_t v = 0; v < N; ++v) {

					if (dist[v][w] == utils::z_inf or dist[w][u] == utils::z_inf) continue;
					if (u == v) continue;

					if (dist[u][v] > dist[u][w] + dist[w][v]) {
						dist[u][v] = dist[u][w] + dist[w][v];

						all_all_paths[u][v] = all_all_paths[u][w];
						all_all_paths[u][v].concatenate(all_all_paths[w][v]);
					}
				}
			}
		}
		*/
	}

	template<class T>
	void xwpaths(const xxgraph<T> *G, vector<vector<node_path_set<T> > >& all_all_paths) {
		/*
		const size_t N = G.n_nodes();

		// allocate memory...
		vector<vector<size_t> > dist(N, vector<size_t>(N, utils::z_inf));
		all_all_paths = vector<vector<node_path_set<T> > >(N, vector<node_path_set<T> >(N));

		// initialise with edge weights (here always 1) the distance and the
		// shortest-path from u to all its neighbours with {u,v}
		for (size_t u = 0; u < N; ++u) {
			const neighbourhood& Nu = G.get_neighbours(u);
			for (size_t v : Nu) {
				dist[u][v] = 1;
				all_all_paths[u][v] = node_path_set<T>(1);
				all_all_paths[u][v][0].push_back(u);
				all_all_paths[u][v][0].push_back(v);
			}
		}

		// find all the all-to-all shortest paths (N^3)
		for (size_t w = 0; w < N; ++w) {
			// distance from a vertex to itself is 0, the path just {w}
			dist[w][w] = 0;
			all_all_paths[w][w] = node_path_set<T>(1, node_path(1, w));

			for (size_t u = 0; u < N; ++u) {
				for (size_t v = 0; v < N; ++v) {

					if (dist[u][w] == utils::z_inf or dist[w][v] == utils::z_inf) continue;
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
							all_all_paths[u][v] = node_path_set<T>( n_uw*n_wv );

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
		*/
	}

} // -- namespace traversal
} // -- namespace dsa
