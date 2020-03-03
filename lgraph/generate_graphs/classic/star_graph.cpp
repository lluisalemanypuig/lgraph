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

	void star_graph(size_t N, uugraph& G) {
		G.init(N);

		for (node u = 1; u < N; ++u) {
			G.add_edge(0,u);
		}
	}

	void star_graph(size_t N, udgraph& G, uint8_t d) {
		G.init(N);

		for (node u = 1; u < N; ++u) {
			if ( (d & 0x01) == 0x01 ) {
				// clockwise
				G.add_edge(0,u);
			}
			if ( (d & 0x02) == 0x02 ) {
				// counter-clockwise
				G.add_edge(u,0);
			}
		}
	}

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
