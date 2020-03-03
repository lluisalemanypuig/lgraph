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
namespace modify {

/**
 * @brief Applies the switching model to an undirected unweighted graph.
 *
 * Given an undirected unweighted graph Gs, let E be the set of edges
 * of Gs. The switching model consists on applying @e Q*|E|
 * times the following operation:
 *	1. Take two edges (s,t) and (u,v), where
 *		s != t and u != v	- (no self-loops)
 *		s != u and s != v	- (both edges must be different and
 *		t != u and t != v	  can't share edges)
 *	2. Exchange endpoints: (s,v) and (u,t)
 *
 * @param[in]	Q Factor used to compute the number of rounds T = Q*|E|
 * where |E| is the number of edges in the graph.
 * @param[in]  rg The RNG used to select the nodes for endpoint exchange.
 * Has to be seeded by the caller.
 * @param[out] Gs The graph on which the switching model is applied.
 * @pre The graph on which to apply the model must have at least two edges.
 * Also, seeding the RNG is done before valling the function.
 */
template<
	class G = std::default_random_engine,
	typename dT = size_t
>
void switching_model(utils::drandom_generator<G,dT>& rg, size_t Q, uugraph& Gs);

} // -- namespace modify
} // -- namespace networks
} // -- namespace lgraph

#include <lgraph/generate_graphs/switching.cpp>
