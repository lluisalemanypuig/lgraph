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

#include <lgraph/generate_graphs/classic/classic.hpp>

namespace lgraph {
namespace networks {
namespace classic {

	void cycle_graph(size_t N, uugraph& G) {
		assert(N >= 3);

		linear_tree(N, G);

		// last edge
		if (N > 2) {
			G.add_edge(0, N - 1);
		}
	}

	void cycle_graph(size_t N, udgraph& G, uint8_t d) {
		assert(N >= 3);
		assert(1 <= d and d <= 3);

		linear_tree(N, G, d);

		if (N > 2) {
			if ( (d & 0x01) == 0x01 ) {
				// clockwise
				G.add_edge(N - 1, 0);
			}
			if ( (d & 0x02) == 0x02 ) {
				// counter-clockwise
				G.add_edge(0, N - 1);
			}
		}
	}

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
