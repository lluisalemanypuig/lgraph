#include <lgraph/graph_traversal/dfs.hpp>

namespace lgraph {
namespace traversal {
namespace dfs {

	void DFS
	(
		const uxgraph *G,
		node source,
		dfs_terminate terminate,
		dfs_process_current proc_curr,
		dfs_process_neighbour proc_neig
	)
	{
		logger<null_stream>& LOG = logger<null_stream>::get_logger();
		LOG.log() << "DEPTH-FIRST SEARCH ALGORITHM" << endl;

		vector<bool> vis(G->n_nodes(), false);
		stack<node> S;

		vis[source] = true;
		S.push(source);
		bool term = false;

		while (not S.empty() and not term) {
			node u = S.top();
			S.pop();

			LOG.log() << "Current node: " << u << endl;
			LOG.log() << "... processing ...";

			proc_curr(G, u, vis);

			LOG.log() << " processed." << endl;

			if (terminate(G, u, vis)) {

				LOG.log() << "! Termination condition true for node " << u << endl;

				term = true;
			}
			else {
				const neighbourhood& Nu = G->get_neighbours(u);

				LOG.log() << "Iterate through neighbours of " << u << endl;

				for (auto Nu_it = Nu.begin(); Nu_it != Nu.end(); ++Nu_it) {
					node v = *Nu_it;

					LOG.log() << "    Neighbour " << v << endl;
					LOG.log() << "    ... processing ...";

					proc_neig(G, u, v, vis);

					LOG.log() << " processed." << endl;

					if (not vis[v]) {

						LOG.log() << "    Neighbour " << v << " was not visited before" << endl;

						S.push(v);
						vis[v] = true;
					}
					else {
						LOG.log() << "    Neighbour " << v << " already visited" << endl;
					}
				}
			}
		}
	}

} // -- namespace dfs
} // -- namespace traversal
} // -- namespace lgraph
