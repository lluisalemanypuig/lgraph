#include <lgraph/graph_traversal/bfs.hpp>

// C++ includes
#include <queue>
using namespace std;

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

			LOG.log() << "! Termination condition true for node "
					  << u << endl;

			term = true;
		}
		else {
			const neighbourhood& Nu = G->get_neighbours(u);

			LOG.log() << "Iterate through neighbours of "
					  << u << endl;

			for (auto Nu_it = Nu.begin(); Nu_it != Nu.end(); ++Nu_it) {
				node v = *Nu_it;

				LOG.log() << "    Neighbour " << v << endl;
				LOG.log() << "    ... processing ...";

				proc_neig(G, u, v, vis);

				LOG.log() << " processed." << endl;

				if (not vis[v]) {

					LOG.log() << "    Neighbour " << v
							  << " was not visited before" << endl;

					Q.push(v);
					vis[v] = true;
				}
				else {
					LOG.log() << "    Neighbour " << v
							  << " already visited" << endl;
				}
			}
		}
	}
}

} // -- namespace bfs
} // -- namespace traversal
} // -- namespace lgraph
