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
