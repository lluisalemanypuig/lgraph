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

// C includes
#include <assert.h>

namespace lgraph {
namespace networks {
namespace classic {

void one_regular(size_t n, uugraph& G) {
	assert(n >= 2);

	if ( (n & 0x1) == 1) {
		// if n is odd, decrease it by one
		// to make it even
		--n;
	}

	G.init(n);
	for (node u = 0; u < n; u += 2) {
		G.add_edge(u, u + 1);
	}
}

void one_regular(size_t n, udgraph& G, uint8_t d) {
	assert(n >= 2);

	if ( (n & 0x1) == 1) {
		// if n is odd, decrease it by one
		// to make it even
		--n;
	}

	G.init(n);
	for (node u = 0; u < n; u += 2) {

		if ( (d & 0x01) == 0x01 ) {
			// clockwise
			G.add_edge(u, u + 1);
		}
		if ( (d & 0x02) == 0x02 ) {
			// counter-clockwise
			G.add_edge(u + 1, u);
		}

	}
}

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
