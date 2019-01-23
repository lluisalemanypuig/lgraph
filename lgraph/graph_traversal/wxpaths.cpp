#include <lgraph/graph_traversal/traversal_wx.hpp>

// lgraph includes
#include <lgraph/graph_traversal/dijkstra.hpp>
#include <lgraph/utils/logger.hpp>

namespace lgraph {
namespace traversal {

/* NODE-NODE */

// one path
template<class T>
void wxpath(const wxgraph<T> *G, node source, node target, node_path<T>& p) {
	assert(G->has_node(source));
	assert(G->has_node(target));

	const size_t N = G->n_nodes();

	// prev[v] = u: previous node of v in the path is u
	std::vector<node> prev(N, N + 1);
	std::vector<T> ds(N, inf_t<T>());
	ds[source] = 0;

	// terminate when target is found
	dijkstra::djka_terminate<T> terminate =
	[&target]
	(const wxgraph<T> *, const dijkstra::djka_node<T>& u, const std::vector<bool>&)
	-> bool
	{
		return u.second == target;
	};

	dijkstra::djka_process_current<T> proc_curr =
	[](const wxgraph<T> *, const dijkstra::djka_node<T>&, const std::vector<bool>&)
	-> void { };

	// function to compute the shortest distance from node u to node v
	dijkstra::djka_process_neighbour<T> proc_neig =
	[&prev, &ds]
	(const wxgraph<T> *, node u, node v, const T& w, const std::vector<bool>&)
	-> bool
	{
		bool add = false;
		if (ds[u] + w + static_cast<T>(1.0e-5) < ds[v]) {
			ds[v] = ds[u] + w;
			prev[v] = u;
			add = true;
		}
		return add;
	};

	dijkstra::Dijkstra(G, source, terminate, proc_curr, proc_neig);

	p.empty();
	node l = target;
	while (l != source and prev[l] != N + 1) {
		p.add_node(l);
		l = prev[l];
	}
	if (l == N + 1) {
		p.empty();
	}
	else {
		p.add_node(source);
		p.reverse();
	}
	p.set_length(ds[target]);
}

// Make a list of paths given a matrix of precendes
template<class T>
void make_paths
(
	node source,
	const std::vector< std::vector<node> >& prev,
	node nidx,
	node_path<T>& path,
	node_path_set<T>& ps
)
{
	path.add_node(nidx);
	if (nidx == source) {
		// path contains a list of nodes from target to source
		ps.push_back(path);
		ps.back().reverse();
		return;
	}

	for (size_t i = 0; i < prev[nidx].size(); ++i) {
		node prev_node = prev[nidx][i];
		make_paths(source, prev, prev_node, path, ps);
		path.delete_last();
	}
}

// all paths
template<class T>
void wxpaths(const wxgraph<T> *G, node source, node target, node_path_set<T>& ps) {
	assert(G->has_node(source));
	assert(G->has_node(target));

	const size_t N = G->n_nodes();

	// prev[v] = u <-> u is the previous node to v in the path
	std::vector< std::vector<node> > prev(N);
	std::vector<T> ds(N, inf_t<T>());
	ds[source] = 0;

	// terminate when target is found
	dijkstra::djka_terminate<T> terminate =
	[&target]
	(const wxgraph<T> *, const dijkstra::djka_node<T>&, const std::vector<bool>&)
	-> bool
	{
		return false;
	};

	dijkstra::djka_process_current<T> proc_curr =
	[](const wxgraph<T> *, const dijkstra::djka_node<T>&, const std::vector<bool>&)
	-> void { };

	// function to compute the shortest distance from node u to node v
	dijkstra::djka_process_neighbour<T> proc_neig =
	[&prev, &ds]
	(const wxgraph<T> *, node u, node v, const T& w, const std::vector<bool>&)
	-> bool
	{
		bool add = false;
		if (ds[u] + w + static_cast<T>(1.0e-5) < ds[v]) {
			// shorter path from u to v
			ds[v] = ds[u] + w;
			prev[v] = std::vector<node>(1, u);
			add = true;
		}
		else if (std::abs(ds[u] + w - ds[v]) <= static_cast<T>(1.0e-5)) {
			// equally long path from u to v
			prev[v].push_back(u);
		}
		return add;
	};

	dijkstra::Dijkstra(G, source, terminate, proc_curr, proc_neig);

	node_path<T> empty_path;
	empty_path.set_length(ds[target]);
	make_paths(source, prev, target, empty_path, ps);
}

/* NODE-ALL */

// one path
template<class T>
void wxpath(const wxgraph<T> *G, node source, std::vector<node_path<T> >& ps) {
	assert(G->has_node(source));

	const size_t N = G->n_nodes();

	// prev[v] = u: previous node of v in the path is u
	std::vector<node> prev(N, N + 1);
	std::vector<T> ds(N, inf_t<T>());
	ds[source] = 0;

	// terminate when target is found
	dijkstra::djka_terminate<T> terminate =
	[](const wxgraph<T> *, const dijkstra::djka_node<T>&, const std::vector<bool>&)
	-> bool { return false; };

	dijkstra::djka_process_current<T> proc_curr =
	[](const wxgraph<T> *, const dijkstra::djka_node<T>&, const std::vector<bool>&)
	-> void { };

	// function to compute the shortest distance from node u to node v
	dijkstra::djka_process_neighbour<T> proc_neig =
	[&prev, &ds]
	(const wxgraph<T> *, node u, node v, const T& w, const std::vector<bool>&)
	-> bool
	{
		bool add = false;
		if (ds[u] + w + static_cast<T>(1.0e-5) < ds[v]) {
			ds[v] = ds[u] + w;
			prev[v] = u;
			add = true;
		}
		return add;
	};

	dijkstra::Dijkstra(G, source, terminate, proc_curr, proc_neig);

	ps = std::vector<node_path<T> >(N);
	for (node u = 0; u < N; ++u) {
		node_path<T>& p = ps[u];

		p.empty();
		node l = u;
		while (l != source and l != N + 1) {
			p.add_node(l);
			l = prev[l];
		}
		if (l == N + 1) {
			p.empty();
		}
		else {
			p.add_node(source);
			p.reverse();
		}
		p.set_length(ds[u]);
	}
}

// all paths
template<class T> void wxpaths
(const wxgraph<T> *G, node source, std::vector<node_path_set<T> >& ps)
{
	ps = std::vector<node_path_set<T> >(G->n_nodes());

	for (node target = 0; target < G->n_nodes(); ++target) {
		wxpaths(G, source, target, ps[target]);
	}
}

/* ALL-ALL */

// one path
template<class T> void wxpath
(const wxgraph<T> *G, std::vector<std::vector<node_path<T> > >& all_all_paths)
{
	const size_t N = G->n_nodes();

	// allocate memory...
	std::vector<std::vector<T> > dist(N, std::vector<T>(N, inf_t<T>()));
	all_all_paths =
		std::vector<std::vector<node_path<T> > >
		(N, std::vector<node_path<T> >(N));

	// initialise data
	for (size_t u = 0; u < N; ++u) {
		// initialise paths for each pair of neighbouring nodes
		const neighbourhood& Nu = G->get_neighbours(u);
		const weight_list<T>& weights = G->get_weights(u);

		for (size_t v_it = 0; v_it < Nu.size(); ++v_it) {
			size_t v = Nu[v_it];

			dist[u][v] = weights[v_it];
			all_all_paths[u][v].add_node(u);
			all_all_paths[u][v].add_node(v);
			all_all_paths[u][v].add_length(weights[v_it]);
		}
	}

	// find the all-to-all shortest paths (N^3)
	for (size_t w = 0; w < N; ++w) {
		// distance from a vertex to itself is 0
		dist[w][w] = 0;
		all_all_paths[w][w].add_node(w);

		for (size_t u = 0; u < N; ++u) {
			for (size_t v = 0; v < N; ++v) {

				// ignore the cases where:
				// the path is not moving
				if (u == v) {
					continue;
				}
				// the distances are infinite
				if (dist[u][w] == inf_t<_new_>()) {
					continue;
				}
				if (dist[w][v] == inf_t<_new_>()) {
					continue;
				}

				T d = dist[u][w] + dist[w][v];
				if (d + static_cast<T>(1.0e-5) < dist[u][v]) {
					dist[u][v] = d;

					all_all_paths[u][v] = all_all_paths[u][w];
					all_all_paths[u][v].concatenate(all_all_paths[w][v]);
				}
			}
		}
	}
}

// all paths
template<class T> void wxpaths
(const wxgraph<T> *G, std::vector<std::vector<node_path_set<T> > >& all_all_paths)
{
	const size_t N = G->n_nodes();

	// allocate memory...
	std::vector<std::vector<T> > dist(N, std::vector<T>(N, inf_t<T>()));
	all_all_paths = std::vector<std::vector<node_path_set<T> > >(N, std::vector<node_path_set<T> >(N));

	// initialise with edge weights (here always 1) the distance and the
	// shortest-path from u to all its neighbours with {u,v}
	for (size_t u = 0; u < N; ++u) {
		const neighbourhood& Nu = G->get_neighbours(u);
		const weight_list<T>& weights = G->get_weights(u);

		for (size_t v_it = 0; v_it < Nu.size(); ++v_it) {
			size_t v = Nu[v_it];

			dist[u][v] = weights[v_it];
			all_all_paths[u][v] = node_path_set<T>(1);
			all_all_paths[u][v][0].add_node(u);
			all_all_paths[u][v][0].add_node(v);
			all_all_paths[u][v][0].add_length(weights[v_it]);
		}
	}

	// find all the all-to-all shortest paths (N^3)
	for (size_t w = 0; w < N; ++w) {
		// distance from a vertex to itself is 0, the path just {w}
		dist[w][w] = 0;
		all_all_paths[w][w] = node_path_set<T>(1, node_path<T>(w));

		for (size_t u = 0; u < N; ++u) {
			for (size_t v = 0; v < N; ++v) {

				// ignore the cases where:
				// the path is not moving
				if (u == v) {
					continue;
				}
				// the distances are infinite
				if (dist[u][w] == inf_t<_new_>()) {
					continue;
				}
				if (dist[w][v] == inf_t<_new_>()) {
					continue;
				}

				T d = dist[u][w] + dist[w][v];
				if (d + static_cast<T>(1.0e-5) < dist[u][v]) {
					// this is a shorter path than the shortest found so far
					dist[u][v] = d;

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
				else if (std::abs(d - dist[u][v]) <= static_cast<T>(1.0e-5)) {

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
