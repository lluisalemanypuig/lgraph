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
		vector<bool> vis(G.n_nodes(), false);
		queue<node> Q;

		vis[source] = true;
		Q.push(source);
		bool term = false;

		while (not Q.empty() and not term) {
			node v = Q.front();
			Q.pop();

			process_current(G, v, vis);
			if (terminate(G, v, vis)) {
				term = true;
			}
			else {
				const neighbourhood& Nv = G.get_neighbours(v);
				for (node w : Nv) {
					if (not vis[w]) {
						process_neighbour(G, v, w, vis);

						Q.push(w);
						vis[w] = true;
					}
				}
			}
		}
	}

} // -- namespace traversal
} // -- namespace dsa
