#include <lgraph/graph_traversal/bfs.hpp>

namespace lgraph {
namespace traversal {
namespace bfs {

void BFS
(
	const uxgraph *G,
	node source,
	bfs_terminate terminate,
	bfs_process_current proc_curr,
	bfs_process_neighbour proc_neig
)
{
	utils::logger<utils::null_stream>& LOG = utils::logger<utils::null_stream>::get_logger();
	LOG.log() << "BREADTH-FIRST SEARCH ALGORITHM" << std::endl;

	std::vector<bool> vis(G->n_nodes(), false);
	std::queue<node> Q;

	vis[source] = true;
	Q.push(source);
	bool term = false;

	while (not Q.empty() and not term) {
		node u = Q.front();
		Q.pop();

		LOG.log() << "Current node: " << u << std::endl;
		LOG.log() << "... processing ...";

		proc_curr(G, u, vis);

		LOG.log() << " processed." << std::endl;

		if (terminate(G, u, vis)) {

			LOG.log() << "! Termination condition true for node "
					  << u << std::endl;

			term = true;
		}
		else {
			const neighbourhood& Nu = G->get_neighbours(u);

			LOG.log() << "Iterate through neighbours of "
					  << u << std::endl;

			for (auto Nu_it = Nu.begin(); Nu_it != Nu.end(); ++Nu_it) {
				node v = *Nu_it;

				LOG.log() << "    Neighbour " << v << std::endl;
				LOG.log() << "    ... processing ...";

				proc_neig(G, u, v, vis);

				LOG.log() << " processed." << std::endl;

				if (not vis[v]) {

					LOG.log() << "    Neighbour " << v
							  << " was not visited before" << std::endl;

					Q.push(v);
					vis[v] = true;
				}
				else {
					LOG.log() << "    Neighbour " << v
							  << " already visited" << std::endl;
				}
			}
		}
	}
}

} // -- namespace bfs
} // -- namespace traversal
} // -- namespace lgraph
