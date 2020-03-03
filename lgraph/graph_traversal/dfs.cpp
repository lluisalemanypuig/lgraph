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

#include <lgraph/graph_traversal/dfs.hpp>

// C++ includes
#include <vector>
#include <stack>

// lgraph includes
#include <lgraph/utils/logger.hpp>

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
	utils::logger<utils::null_stream>& LOG = utils::logger<utils::null_stream>::get_logger();
	LOG.log() << "DEPTH-FIRST SEARCH ALGORITHM" << std::endl;

	std::vector<bool> vis(G->n_nodes(), false);
	std::stack<node> S;

	vis[source] = true;
	S.push(source);
	bool term = false;

	while (not S.empty() and not term) {
		node u = S.top();
		S.pop();

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

					S.push(v);
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

} // -- namespace dfs
} // -- namespace traversal
} // -- namespace lgraph
