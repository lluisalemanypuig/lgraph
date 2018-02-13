#include "traversal.hpp"

namespace dsa {
namespace traversal {

	void path(const graph& G, node source, node target, vector<node>& path) {
		// terminate when target is found
		function<bool (const graph&, node, const vector<bool>&)> terminate =
		[&target](const graph&, node u, const vector<bool>&)
		{
			return u == target;
		};

		// path from source to target
		path = {source};

		// distances from source to nodes
		queue< vector<node> > paths;
		paths.push(path);

		// current distance from source to u
		vector<node> current_path;

		function<void (const graph&, node u, const vector<bool>&)> process_current =
		[&paths, &path, &current_path, &target](const graph&, node u, const vector<bool>&)
		{
			current_path = paths.front();
			paths.pop();

			if (u == target) {
				path = current_path;
			}
		};

		// function to compute the shortest distance from source to node v
		function<void (const graph&, node, node, const vector<bool>&)> process_neighbour =
		[&paths, &current_path](const graph&, node, node v, const vector<bool>& vis)
		{
			if (not vis[v]) {
				vector<node> path_to_v = current_path;
				path_to_v.push_back(v);
				paths.push(path_to_v);
			}
		};

		BFS(G, source, terminate, process_current, process_neighbour);

		logger<ofstream>& LOG = logger<ofstream>::get_logger();
		LOG.log() << "vertex-vertex path (" << source << " -> " << target << "):";
		if (path.size() > 0) {
			for (node u : path) LOG.log() << " " << u;
		}
		else LOG.log() << " No path!" << endl;
		LOG.log() << endl;
	}

	void path(const graph& G, node source, vector<vector<node> >& paths) {
		const size_t N = G.n_nodes();

		function<bool (const graph&, node, const vector<bool>&)> terminate =
		[](const graph&, node, const vector<bool>&)
		{
			return false;
		};

		// path from source to target
		paths = vector<vector<node> >(N);
		paths[source] = vector<node>(1);
		paths[source][0] = source;

		function<void (const graph& G, node u, const vector<bool>& vis)> process_current =
		[](const graph&, node, const vector<bool>&)
		{ };

		// function to compute the shortest distance from source to node v
		function<void (const graph&, node, node, const vector<bool>&)> process_neighbour =
		[&paths](const graph&, node u, node v, const vector<bool>&)
		{
			// add one node, count the number of edges
			size_t d_u = paths[u].size() + 1 - 1;
			// number of edges
			size_t d_v = paths[v].size() - 1;
			if (d_u < d_v) {
				vector<node> new_path = paths[u];
				new_path.push_back(v);
				paths[v] = new_path;
			}
		};

		BFS(G, source, terminate, process_current, process_neighbour);

		logger<ofstream>& LOG = logger<ofstream>::get_logger();
		for (node target = 0; target < N; ++target) {
			LOG.log() << "(vertex-all) Path from " << source << " to " << target << ":";
			if (paths[target].size() > 0) {
				for (node u : paths[target]) LOG.log() << " " << u;
			}
			else LOG.log() << " No path!" << endl;
			LOG.log() << endl;
		}
	}

} // -- namespace traversal
} // -- namespace dsa
