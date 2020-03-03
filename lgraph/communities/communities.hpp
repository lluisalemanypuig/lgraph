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
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>

namespace lgraph {
namespace networks {
namespace communities {

// CONNECTED COMPONENTS

/**
 * @brief Computes the connected components of this graph.
 * @param[in] g The input graph.
 * @param[out] comps @e comps[i] = @e j if, and only if, the @e i-th vertex
 * belongs to the @e j-th connected component, where @e i is a node index. \n
 * The labels start at 0. Any label's value greater or equal than
 * the number of vertices of @e g is not valid.
 * @param[out] bins If this parameter is not null then @e bins[i] contains
 * how many vertices are in the @e i-th connected component.
 * @returns Returns the amount of connected components in @e g.
 */
size_t connected_components
(
	const uugraph& g,
	std::vector<size_t>& comps,
	std::vector<size_t> *bins = nullptr
);

/**
 * @brief Computes the strongly connected components of this graph.
 * @param[in] g The input graph.
 * @param[out] comps @e comps[i] = @e j if, and only if, the @e i-th vertex
 * belongs to the @e j-th connected component, where @e i is a node index. \n
 * The labels start at 0. Any label's value greater or equal than
 * the number of vertices of @e g is not valid.
 * @param[out] bins If this parameter is not null then @e bins[i] contains
 * how many vertices are in the @e i-th connected component.
 * @returns Returns the amount of connected components in @e g.
 */
size_t connected_components
(
	const udgraph& g,
	std::vector<size_t>& comps,
	std::vector<size_t> *bins = nullptr
);

} // -- namespace communities
} // -- namespace networks
} // -- namespace lgraph
