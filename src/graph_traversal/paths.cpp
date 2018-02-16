#include "traversal.hpp"

namespace dsa {
namespace traversal {

	void path(const graph& G, node source, node target, node_path& p) {
		// terminate when target is found
		function<bool (const graph&, node, const vector<bool>&)> terminate =
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

		function<void (const graph&, node u, const vector<bool>&)> process_current =
		[&paths, &p, &current_path, &target](const graph&, node u, const vector<bool>&)
		{
			current_path = paths.front();
			paths.pop();

			if (u == target) {
				p = current_path;
			}
		};

		// function to compute the shortest distance from source to node v
		function<void (const graph&, node, node, const vector<bool>&)> process_neighbour =
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

	void path(const graph& G, node source, vector<node_path>& ps) {
		const size_t N = G.n_nodes();

		function<bool (const graph&, node, const vector<bool>&)> terminate =
		[](const graph&, node, const vector<bool>&)
		{
			return false;
		};

		// path from source to target
		ps = vector<node_path>(N);
		ps[source] = node_path(1);
		ps[source][0] = source;

		function<void (const graph& G, node u, const vector<bool>& vis)> process_current =
		[](const graph&, node, const vector<bool>&)
		{ };

		// function to compute the shortest distance from source to node v
		function<void (const graph&, node, node, const vector<bool>&)> process_neighbour =
		[&ps](const graph&, node u, node v, const vector<bool>&)
		{
			// add one node, count the number of edges
			size_t d_u = ps[u].size() + 1 - 1;
			// number of edges
			size_t d_v = ps[v].size() - 1;
			if (d_u < d_v) {
				node_path new_path = ps[u];
				new_path.push_back(v);
				ps[v] = new_path;
			}
		};

		BFS(G, source, terminate, process_current, process_neighbour);
	}

	void paths(const graph& G, vector<vector<node_path> >& all_paths) {
		const size_t N = G.n_nodes();
		logger<null_stream>& LOG = logger<null_stream>::get_logger();

		vector<vector<size_t> > dist(N, vector<size_t>(N, utils::inf));
		all_paths = vector<vector<node_path> >(N, vector<node_path>(N));

		// initialise paths
		for (size_t u = 0; u < N; ++u) {
			for (size_t v = 0; v < N; ++v) {
				if (G.degree(u) > 0 or u == v) {
					all_paths[u][v].push_back(u);
				}
			}
		}
		// initialise with edge weights (here always 1)
		for (size_t u = 0; u < N; ++u) {
			const neighbourhood& Nu = G.get_neighbours(u);
			for (size_t v : Nu) {
				dist[u][v] = 1;
				all_paths[u][v].push_back(v);
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

						LOG.log() << "-------" << endl;
						LOG.log() << "    new distance from " << u << " to " << v << " is: " << endl;
						LOG.log() << "        distance from " << u << " to " << w << ": " << dist[u][w] - 1 << endl;
						LOG.log() << "        distance from " << w << " to " << v << ": " << dist[w][v] - 1 << endl;
						LOG.log() << "        total= " << dist[u][v] - 1 << endl;

						all_paths[u][v] = all_paths[u][w];
						all_paths[u][v].insert(
							all_paths[u][v].end(),
							all_paths[w][v].begin() + 1,
							all_paths[w][v].end()
						);

						LOG.log() << "    new path from " << u << " to " << v << " is: " << endl;
						LOG.log() << "        path from " << u << " to " << w << ": " << all_paths[u][w] << endl;
						LOG.log() << "        path from " << w << " to " << v << ": " << all_paths[w][v] << endl;
						LOG.log() << "        total= " << all_paths[u][v] << endl;
					}
				}
			}
		}
	}

} // -- namespace traversal
} // -- namespace dsa
