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
#include <lgraph/utils/random_generator.hpp>

namespace lgraph {
namespace networks {
namespace random {

/**
 * @brief Erdos & Renyi's model.
 *
 * Generates a G{n,p} graph.
 *
 * The implementation follows the algorithm in [1].
 *
 * [1] Vladimir Batagelj and Ulrik Brandes,
 * "Efficient generation of large random networks",
 * Phys. Rev. E, 71, 036113, 2005.
 *
 * @param[in]	N Number of nodes of the graph.
 * @param[in]	p Probability of making an edge.
 * @param[in]  rg The random number generator used. Has to be seeded by the caller.
 * @param[out] Gs The binomial graph constructed.
 */
template<
	class G = std::default_random_engine,
	typename cT = float
>
void Erdos_Renyi
(utils::crandom_generator<G,cT>& rg, size_t N, double p, uugraph& Gs);

} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph

#include <lgraph/generate_graphs/random/erdos_renyi.cpp>
