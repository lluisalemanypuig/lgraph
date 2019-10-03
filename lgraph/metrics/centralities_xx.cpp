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

#include <lgraph/metrics/centralities_xx.hpp>

// C++ includes
using namespace std;

namespace lgraph {
namespace networks {
namespace metrics {
namespace centralities {

/* DEGREE */

double degree(const xxgraph *G, node u) {
	// number of nodes minus 1
	const double nm1 = G->n_nodes() - 1;
	return G->degree(u)/nm1;
}

void degree(const xxgraph *G, std::vector<double>& dc) {
	vector<node> nds;
	G->nodes(nds);

	// number of nodes minus 1
	const double nm1 = G->n_nodes() - 1;
	dc.clear();

	transform(
		// iterate through all nodes
		nds.begin(), nds.end(),

		// append value at the back of dc
		back_inserter(dc),

		// calculate degree centrality
		[&](node u) {
			return G->degree(u)/nm1;
		}
	);
}

} // -- namespace centralities
} // -- namespace metrics
} // -- namespace networks
} // -- namespace lgraph
