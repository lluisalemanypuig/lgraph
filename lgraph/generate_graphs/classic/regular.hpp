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

// lgraph includes
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>

namespace lgraph {
namespace networks {
namespace classic {

/* 1-REGULAR GRAPHS */

/**
 * @brief Generate an undirected 1-regular graph of @e n nodes.
 *
 * If @e n is odd then the graph has @e n - 1 nodes.
 *
 * A 1-regular graph is a graph where the edges are of the form
 * (u, u + 1) where u takes the even values in [0,n).
 *
 * @param n Number of nodes.
 * @param[out] G Generated 1-regular undirected graph.
 * @pre @e n >= 2
 */
void one_regular(size_t n, uugraph& G);

/**
 * @brief Generate an undirected 1-regular graph of @e n nodes.
 *
 * See @ref one_regular(size_t, uugraph&) for the description
 * of a 1-regular graph.
 *
 * The orientation of the edges depends on the value of @e d.
 *
 * @param n Number of nodes.
 * @param[out] G Generated 1-regular undirected graph.
 * @param d Indicate orientation of edges.
 *	Values:
 *  - 1 for clockwise orientation: edges (u,v) such that u < v
 *  - 2 for counter-clockwise orientation: edges (u,v) such that u > v
 *  - 3 for both orientations
 * @pre @e n >= 2
 */
void one_regular(size_t n, udgraph& G, uint8_t d = 1);

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
