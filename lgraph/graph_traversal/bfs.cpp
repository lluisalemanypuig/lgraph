/*********************************************************************
 * lgraph
 * Copyright (C) 2018-2019 Lluís Alemany Puig
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Contact: Lluís Alemany Puig (lluis.alemany.puig@gmail.com)
 * 
 ********************************************************************/

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
