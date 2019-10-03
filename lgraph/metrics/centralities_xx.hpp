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

#pragma once

// C++ includes
#include <vector>

// lgraph includes
#include <lgraph/data_structures/xxgraph.hpp>

namespace lgraph {
namespace networks {
namespace metrics {
namespace centralities {

/* DEGREE CENTRALITY */

/**
 * @brief Normalised degree centrality of a single node.
 * @param G The unweighted graph to be evaluated.
 * @param u The node to be evaluated.
 * @return Returns the degree of node @e u divided by the
 * number of nodes (minus 1).
 */
double degree(const xxgraph *G, node u);

/**
 * @brief Normalised degree centrality of all nodes in a graph.
 * @param[in] G The unweighted graph to be evaluated.
 * @param[out] dc The i-th position contains the normalised degree
 * centrality of the i-th node.
 */
void degree(const xxgraph *G, std::vector<double>& dc);

} // -- namespace centralities
} // -- namespace metrics
} // -- namespace networks
} // -- namespace lgraph
