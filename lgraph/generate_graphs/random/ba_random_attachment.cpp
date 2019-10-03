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

#include <lgraph/generate_graphs/random/barabasi_albert.hpp>

namespace lgraph {
namespace networks {
namespace random {
	
template<class G, typename dT>
void BA_random_attachment
(
	utils::drandom_generator<G,dT>& rg,
	size_t n0, size_t m0, size_t T,
	uugraph& Gs
)
{
	// initialize sequences of graphs
	Gs.init(n0);

	// initialize vertices to choose from
	std::vector<size_t> idxs(n0);
	for (size_t i = 0; i < idxs.size(); ++i) {
		idxs[i] = i;
	}

	// at each time step t (1 <= t <= T) add one vertex to G
	// connected to m0 vertices chosen u.a.r. making sure that
	// no vertex is chosen twice in the same time step.
	for (size_t t = 1; t <= T; ++t) {

		// define the upper bound of the interval within which
		// the random numbers will be generated
		size_t max_idx = idxs.size() - 1;

		// add a new vertex to the graph
		size_t u = Gs.add_node();

		// connect the new vertex to m0 vertices in the graph
		for (size_t m = 0; m < m0; ++m) {
			// reset the uniform random generator
			rg.init_uniform(0, max_idx);
			size_t r = rg.get_uniform();

			Gs.add_edge(u, idxs[r]);

			// the chosen node goes at the end, where it will not
			// be chosen again.
			std::swap(idxs[r], idxs[max_idx]);
			--max_idx;
		}

		// add another index to the list so that we can consider
		// the new vertex in the next time step.
		idxs.push_back(u);
	}
}

} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph
