#include "traversal.hpp"

namespace dsa {
namespace traversal {

	// private namespace
	namespace _traversal {
		void print_distance_matrix(const vector<vector<size_t> >& dist) {
			logger<null_stream>& LOG = logger<null_stream>::get_logger();
			const size_t N = dist.size();

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
		}
	}

	size_t distance(const graph& G, node source, node target) {

		// DO terminate when target node is found. BFS guarantees that when this happens
		// the shortest distance was found
		function<bool (const graph& g, node u, const vector<bool>& vis)> terminate =
		[&target](const graph&, node u, const vector<bool>&)
		{
			return u == target;
		};

		// distances from source to nodes
		queue<size_t> distances;
		distances.push(0);

		// current distance from source to u
		size_t current_dist;

		// distance from source to target. Set to infinite
		// for those targets not reachable from source.
		size_t st_dist = utils::inf;

		function<void (const graph& G, node u, const vector<bool>& vis)> process_current =
		[&distances, &st_dist, &current_dist, &target](const graph&, node u, const vector<bool>&)
		{
			current_dist = distances.front();
			distances.pop();
			if (u == target) {
				st_dist = current_dist;
			}
		};

		// function to compute the shortest distance from source to node v
		function<void (const graph&, node, node, const vector<bool>&)> process_neighbour =
		[&distances, &current_dist](const graph&, node, node v, const vector<bool>& vis)
		{
			if (not vis[v]) {
				distances.push(current_dist + 1);
			}
		};

		BFS(G, source, terminate, process_current, process_neighbour);

		return st_dist;
	}

	void distance(const graph& G, node source, vector<size_t>& ds) {
		// do NOT terminate: iterate through all nodes
		function<bool (const graph&, node, const vector<bool>&)> terminate =
		[](const graph&, node, const vector<bool>&)
		{
			return false;
		};

		// don't need to process the currently visited node
		function<void (const graph&, node, const vector<bool>&)> process_current =
		[](const graph&, node, const vector<bool>&) { };

		// distance from source to all nodes
		ds = vector<size_t>(G.n_nodes(), inf);
		ds[source] = 0;

		// function to compute the shortest distance from source to node v
		function<void (const graph&, node u, node v, const vector<bool>&)> process_neighbour =
		[&ds](const graph&, node u, node v, const vector<bool>&)
		{
			size_t d = ds[u] + 1;
			if (d < ds[v]) {
				ds[v] = d;
			}
		};

		BFS(G, source, terminate, process_current, process_neighbour);
	}

	void distances(const graph& G, vector<vector<size_t> >& dist) {
		const size_t N = G.n_nodes();
		logger<null_stream>& LOG = logger<null_stream>::get_logger();

		dist = vector<vector<size_t> >(N, vector<size_t>(N, utils::inf));

		// initialise with edge weights (here always 1)
		for (size_t u = 0; u < N; ++u) {
			const neighbourhood& Nu = G.get_neighbours(u);
			for (size_t v : Nu) {
				dist[u][v] = 1;
			}
		}

		LOG.log() << "After initialisation" << endl;
		_traversal::print_distance_matrix(dist);

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

		_traversal::print_distance_matrix(dist);
	}

} // -- namespace traversal
} // -- namespace dsa
