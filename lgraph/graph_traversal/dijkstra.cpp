#include <lgraph/graph_traversal/dijkstra.hpp>

// C++ includes
#include <vector>
#include <queue>

// lgraph includes
#include <lgraph/utils/logger.hpp>

namespace lgraph {
namespace traversal {
namespace dijkstra {

template<class T>
void Dijkstra
(
	const wxgraph<T> *G,
	node source,
	djka_terminate<T> terminate,
	djka_process_current<T> proc_curr,
	djka_process_neighbour<T> proc_neig
)
{
	utils::logger<utils::null_stream>& LOG = utils::logger<utils::null_stream>::get_logger();
	LOG.log() << "DIJKSTRA ALGORITHM" << std::endl;

	std::vector<bool> vis(G->n_nodes(), false);
	std::priority_queue<
		djka_node<T>,				// -> elements' type,
		std::vector<djka_node<T> >,	// -> compare elements so that smaller distances
		std::greater<djka_node<T> >	// are at the top
	> Q;

	Q.push(djka_node<T>(0, source));
	bool term = false;

	while (not Q.empty() and not term) {
		djka_node<T> u = Q.top();
		Q.pop();

		LOG.log() << "Current node: " << u.second << std::endl;

		if (not vis[u.second]) {
			vis[u.second] = true;

			LOG.log() << "    ... processing";

			proc_curr(G, u, vis);

			LOG.log() << "    ... processed." << std::endl;
			LOG.log() << "Checking termination condition" << std::endl;

			if (terminate(G, u, vis)) {

				LOG.log() << "! Termination condition true for node "
						  << u.second << std::endl;

				term = true;
			}
			else {
				const neighbourhood& Nu = G->get_neighbours(u.second);
				const weight_list<T>& wu = G->get_weights(u.second);

				LOG.log() << "Iterate through neighbours of "
						  << u.second << std::endl;
				LOG.log() << "    Node " << u.second << " has "
						  << Nu.size() << " neighbours" << std::endl;
				LOG.log() << "    Node " << u.second << " has " << wu.size()
						  << " weights" << std::endl;

				auto wu_it = wu.begin();
				for (
					auto Nu_it = Nu.begin();
					Nu_it != Nu.end();
					++Nu_it, ++wu_it
				)
				{
					LOG.log() << "    Neighbour index: " << Nu_it - Nu.begin()
							  << std::endl;

					node v = *Nu_it;
					T weight_uv = *wu_it;

					LOG.log() << "    Neighbour " << v << " was not visited before"
							  << std::endl;
					LOG.log() << "        weight edge (" << u.second << "," << v << "): "
							  << weight_uv << std::endl;

					LOG.log() << "        ... processing";
					bool add_next = proc_neig(G, u.second, v, weight_uv, vis);
					LOG.log() << "        ... processed." << std::endl;

					if (add_next) {
						Q.push( djka_node<T>(u.first + weight_uv, v) );
					}
				}
			}
		}

		LOG.log() << std::endl;
	}
}

} // -- namespace dijkstra
} // -- namespace traversal
} // -- namespace lgraph
