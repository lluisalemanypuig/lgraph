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

#include <lgraph/generate_graphs/random/erdos_renyi.hpp>

namespace lgraph {
namespace networks {
namespace random {

template<class G, typename cT>
void Erdos_Renyi(utils::crandom_generator<G,cT>& rg, size_t N, double p, uugraph& Gs) {
	if (p == 0.0) {
		// empty graph
		Gs.init(0);
		return;
	}
	if (p == 1.0) {
		// complete graph
		classic::complete_graph(N, Gs);
		return;
	}

	Gs.init(N);
	rg.init_uniform(0, 1);

	size_t v = 1;
	int w = -1;

	while (v < N) {

		cT r = rg.get_uniform();
		w = w + 1 + (log(1 - r)/log(1 - p));
		while (w >= int(v) and v < N) {
			w = w - int(v);
			++v;
		}

		if (v < N) {
			Gs.add_edge(node(v),node(w));
		}
	}
}

} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph
