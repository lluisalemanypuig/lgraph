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
	 * @brief Barabasi-Albert model: Preferential attachment variant.
	 *
	 * Builds a graph with @e n0 + @e T vertices. The first step is to build an
	 * empty graph with @e n0 vertices.
	 *
	 * Then add @e T new vertices, each of which is connected to @e m0 already
	 * existing vertices of the graph each with a probability proportional to their degree.
	 *
	 * @param[in] n0 The initial number of vertices.
	 * @param[in] m0 The number of edges to connect each vertex to.
	 * @param[in] T The number of steps of the algorithm.
	 * @param[in] rg The random number generator used. Has to be seeded by the caller.
	 * @param[out] Gs The resulting graph following this Barabasi-Albert model variant.
	 */
	template<
		class G = std::default_random_engine,
		typename dT = size_t
	>
	void BA_preferential_attachment(
		utils::drandom_generator<G,dT>& rg,
		size_t n0, size_t m0, size_t T,
		uugraph& Gs
	);
	
	/**
	 * @brief Barabasi-Albert model: Random attachment variant.
	 *
	 * Similar to the @ref BA_preferential_attachment model.
	 *
	 *
	 * However, at each step, the m0 connections are made with
	 * probabilities uniformly at random.
	 *
	 * @param[in] n0 The initial number of vertices.
	 * @param[in] m0 The number of edges to connect each vertex to.
	 * @param[in] T The number of steps of the algorithm.
	 * @param[in] rg The random number generator used. Has to be seeded by the caller.
	 * @param[out] Gs The resulting graph following this Barabasi-Albert model variant.
	 */
	template<
		class G = std::default_random_engine,
		typename dT = size_t
	>
	void BA_random_attachment(
		utils::drandom_generator<G,dT>& rg,
		size_t n0, size_t m0, size_t T,
		uugraph& Gs
	);
	
	/**
	 * @brief Barabasi-Albert model: No vertex growth variant.
	 *
	 * Similar to the @ref BA_preferential_attachment model. This time, it
	 * differs from it in that the initial graph has the same number of
	 * vertices as the final graph: @e n0.
	 *
	 * The @e T steps are used to make @e m0 connections at each step.
	 * More precisely:
	 *	- Create an empty graph with @e n0 vertices
	 *	- For step ti = 1 to @e T
	 *		- Choose a vertex with probability proportional to its
	 *		degree. Let u be that vertex.
	 *		- Make @e m0 connections with some of the other vertices
	 *		in the graph. Each edge (u, v) is added with probability
	 *		proportional to the degree of v.
	 *
	 * @param[in] n0 The total number of vertices.
	 * @param[in] m0 The number of edges to connect each vertex to.
	 * @param[in] T The number of steps of the algorithm.
	 * @param[in] rg The random number generator used. Has to be seeded by the caller.
	 * @param[out] Gs The resulting graph following this Barabasi-Albert model variant.
	 */
	template<
		class G = std::default_random_engine,
		typename dT = size_t
	>
	void BA_no_vertex_growth(
		utils::drandom_generator<G,dT>& rg,
		size_t n0, size_t m0, size_t T,
		uugraph& Gs
	);

} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph

#include <lgraph/generate_graphs/random/ba_preferential_attachment.cpp>
#include <lgraph/generate_graphs/random/ba_random_attachment.cpp>
#include <lgraph/generate_graphs/random/ba_no_vertex_growth.cpp>
