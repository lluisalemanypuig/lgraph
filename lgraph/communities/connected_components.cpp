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

#include <lgraph/communities/communities.hpp>

// C++ includes
using namespace std;

// lgraph includes
#include <lgraph/graph_traversal/bfs.hpp>

namespace lgraph {
using namespace traversal::bfs;

namespace networks {
namespace communities {

size_t connected_components
(
	const uugraph& g, std::vector<size_t>& comps,
	std::vector<size_t> *bins
)
{
	const size_t N = g.n_nodes();

	// initialise with a value equal to the number
	// of nodes to indicate unprocessed node
	comps = vector<size_t>(N, N);
	// the label of each connected component
	size_t label = 0;
	// how many vertices have label 'label'
	size_t count = 0;

	bfs_terminate term = [](const uxgraph *, node, const vector<bool>&) -> bool {
		// the BFS algorithm will terminate by its own accord
		// when it can't find more neighbours to expand the
		// search to.
		return false;
	};
	bfs_process_current proc_cur =
	[&](const uxgraph *, node u, const vector<bool>&) -> void
	{
		// assign to vertex u the current label
		comps[u] = label;
		// increment the number of vertices in this component
		++count;
	};
	bfs_process_neighbour proc_neigh =
	[](const uxgraph *, node, node, const vector<bool>&) -> void {
		// no need to do anything
	};

	for (node u = 0; u < g.n_nodes(); ++u) {
		// if a node has already been processed, skip
		if (comps[u] < N) {
			continue;
		}

		// launch the BSF traversal starting at node u.
		BFS(&g, u, term, proc_cur, proc_neigh);

		// the traversal has found a whole new component
		// -> increment label
		++label;
		// append information to bins, reset count
		if (bins != nullptr) {
			bins->push_back(count);
		}
		count = 0;
	}

	return label;
}

size_t connected_components
(
	const udgraph& g, std::vector<size_t>& comps,
	std::vector<size_t> *bins
)
{
	comps = vector<size_t>(g.n_nodes(), g.n_nodes());
	UNUSED(bins);

	return 0;
}

} // -- namespace communities
} // -- namespace networks
} // -- namespace lgraph
