#include "traversal.hpp"

namespace lgraph {
namespace traversal {

	template<class T>
	void BFS
	(
		const xxgraph<T> *G,
		node source,
		bfs_terminate<T> terminate,
		bfs_process_current<T> proc_curr,
		bfs_process_neighbour<T> proc_neig
	)
	{
		logger<null_stream>& LOG = logger<null_stream>::get_logger();
		LOG.log() << "BREADTH-FIRST SEARCH ALGORITHM" << endl;

		vector<bool> vis(G->n_nodes(), false);
		queue<node> Q;

		vis[source] = true;
		Q.push(source);
		bool term = false;

		while (not Q.empty() and not term) {
			node u = Q.front();
			Q.pop();

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

				for (node v : Nu) {
					LOG.log() << "    Neighbour " << v << endl;
					LOG.log() << "    ... processing ...";

					proc_neig(G, u, v, vis);

					LOG.log() << " processed." << endl;

					if (not vis[v]) {

						LOG.log() << "    Neighbour " << v << " was not visited before" << endl;

						Q.push(v);
						vis[v] = true;
					}
					else {
						LOG.log() << "    Neighbour " << v << " already visited" << endl;
					}
				}
			}
		}
	}

} // -- namespace traversal
} // -- namespace dsa
