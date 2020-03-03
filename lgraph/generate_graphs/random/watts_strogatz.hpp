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
	 * @brief Watts & Strogatz's model.
	 *
	 * Create a cycle graph of @e N nodes, then connect each node with
	 * its @e k nearest nodes in the ring (or @e k - 1 if @e k is odd).
	 *
	 * The rewiring is done by iterating over all edges created in the
	 * previous two steps (@e u,@e v) and replacing it with an edge
	 * (@e u,@e w) with probability @e p.
	 *
	 * @e w is chosen uniformly at random from the set of non-neighbours
	 * of @e u at the moment of rewiring.
	 *
	 * @param crg Continuous random number generator. Has to be seeded by the caller.
	 * @param drg Discrete random number generator. Has to be seeded by the caller.
	 * @param   N Number of nodes of the graph.
	 * @param   k Number of the @e k nearest neighbours in a ring topology.
	 * Must satisfy: 2 <= @e k <= @e N - 1.
	 * @param   p Probability of rewiring an edge.
	 * @param  Gs The graph generated, following the Watts & Strogatz's model.
	 */
	template<
		class G = std::default_random_engine,
		typename cT = float,
		typename dT = size_t
	>
	void Watts_Strogatz(
		utils::crandom_generator<G,cT>& crg,
		utils::drandom_generator<G,dT>& drg,
		size_t N, size_t k, double p,
		uugraph& Gs
	);

} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph

#include <lgraph/generate_graphs/random/watts_strogatz.cpp>
