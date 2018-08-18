#include <lgraph/graph_traversal/dijkstra.hpp>

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
		logger<null_stream>& LOG = logger<null_stream>::get_logger();
		LOG.log() << "DIJKSTRA ALGORITHM" << endl;

		vector<bool> vis(G->n_nodes(), false);
		priority_queue<
			djka_node<T>,			// -> elements' type,
			vector<djka_node<T> >,	// -> compare elements so that smaller distances
			greater<djka_node<T> >	// are at the top
		> Q;

		Q.push(djka_node<T>(0, source));
		bool term = false;

		while (not Q.empty() and not term) {
			djka_node<T> u = Q.top();
			Q.pop();

			LOG.log() << "Current node: " << u.second << endl;

			if (not vis[u.second]) {
				vis[u.second] = true;

				LOG.log() << "    ... processing";

				proc_curr(G, u, vis);

				LOG.log() << "    ... processed." << endl;
				LOG.log() << "Checking termination condition" << endl;

				if (terminate(G, u, vis)) {

					LOG.log() << "! Termination condition true for node " << u.second << endl;

					term = true;
				}
				else {
					const neighbourhood& Nu = G->get_neighbours(u.second);
					const weight_list<T>& wu = G->get_weights(u.second);

					LOG.log() << "Iterate through neighbours of " << u.second << endl;
					LOG.log() << "    Node " << u.second << " has " << Nu.size() << " neighbours" << endl;
					LOG.log() << "    Node " << u.second << " has " << wu.size() << " weights" << endl;

					auto wu_it = wu.begin();
					for (
						auto Nu_it = Nu.begin();
						Nu_it != Nu.end();
						++Nu_it, ++wu_it
					)
					{
						LOG.log() << "    Neighbour index: " << Nu_it - Nu.begin() << endl;

						node v = *Nu_it;
						T weight_uv = *wu_it;

						LOG.log() << "    Neighbour " << v << " was not visited before" << endl;
						LOG.log() << "        weight edge (" << u.second << "," << v << "): " << weight_uv << endl;

						LOG.log() << "        ... processing";
						bool add_next = proc_neig(G, u.second, v, weight_uv, vis);
						LOG.log() << "        ... processed." << endl;

						if (add_next) {
							Q.push( djka_node<T>(u.first + weight_uv, v) );
						}
					}
				}
			}

			LOG.log() << endl;
		}
	}

} // -- namespace dijkstra
} // -- namespace traversal
} // -- namespace lgraph
