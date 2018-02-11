#include "traversal.hpp"

namespace dsa {
namespace traversal {

	void BFS
	(
		const graph& G,
		node source,
		function<bool (const graph&, node, const vector<bool>&)> terminate,
		function<void (const graph&, node, const vector<bool>&)> process_current,
		function<void (const graph&, node, node, const vector<bool>&)> process_neighbour
	)
	{
		logger<null_stream>& LOG = logger<null_stream>::get_logger();

		vector<bool> vis(G.n_nodes(), false);
		queue<node> Q;

		vis[source] = true;
		Q.push(source);
		bool term = false;

		while (not Q.empty() and not term) {
			node v = Q.front();
			Q.pop();

			LOG.log() << "Current node: " << v << endl;
			LOG.log() << "... processing ...";

			process_current(G, v, vis);

			LOG.log() << " processed." << endl;

			if (terminate(G, v, vis)) {

				LOG.log() << "! Termination condition true for node " << v << endl;

				term = true;
			}
			else {
				const neighbourhood& Nv = G.get_neighbours(v);

				LOG.log() << "Iterate through neighbours of " << v << endl;

				for (node w : Nv) {
					LOG.log() << "    Neighbour " << w << endl;
					LOG.log() << "    ... processing ...";

					process_neighbour(G, v, w, vis);

					LOG.log() << " processed." << endl;

					if (not vis[w]) {

						LOG.log() << "    Neighbour " << w << " was not visited before" << endl;

						Q.push(w);
						vis[w] = true;
					}
					else {
						LOG.log() << "    Neighbour " << w << " already visited" << endl;
					}
				}
			}
		}
	}

} // -- namespace traversal
} // -- namespace dsa
