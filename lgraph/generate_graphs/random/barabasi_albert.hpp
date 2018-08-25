#pragma once

// C++ includes
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <random>
#include <vector>
using namespace std;

// Custom includes
#include <lgraph/data_structures/random_generator.hpp>
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/utils/logger.hpp>

namespace lgraph {
using namespace utils;

namespace networks {
namespace random {

	/**
	 * @brief Barabasi-Albert model: Preferential attachment variant
	 *
	 * Builds a graph with @e n0 + @e T vertices. The first step is to build an
	 * empty graph with @e n0 vertices.
	 *
	 * Then add @e T new vertices, each of which is connected to @e m0 already
	 * existing vertices of the graph each with a probability proportional to their degree.
	 *
	 * @param[in] n0 The initial number of vertices
	 * @param[in] m0 The number of edges to connect each vertex to
	 * @param[in] T The number of steps of the algorithm
	 * @param[in] rg The random number generator used
	 * @param[out] Gs The resulting graph following this Barabasi-Albert model variant
	 *
	 * @pre Seeding the RNG is done before valling the function.
	 */
	template<
		class G = default_random_engine,
		typename dT = size_t
	>
	void BA_preferential_attachment(
		drandom_generator<G,dT> *rg,
		size_t n0, size_t m0, size_t T,
		uugraph& Gs
	);
	
	/**
	 * @brief Barabasi-Albert model: Random attachment variant
	 *
	 * Similar to the @ref BA_preferential_attachment model.
	 *
	 *
	 * However, at each step, the m0 connections are made with
	 * probabilities uniformly at random.
	 *
	 * @param[in] n0 The initial number of vertices
	 * @param[in] m0 The number of edges to connect each vertex to
	 * @param[in] T The number of steps of the algorithm
	 * @param[in] rg The random number generator used
	 * @param[out] Gs The resulting graph following this Barabasi-Albert model variant
	 *
	 * @pre Seeding the RNG is done before valling the function.
	 */
	template<
		class G = default_random_engine,
		typename dT = size_t
	>
	void BA_random_attachment(
		drandom_generator<G,dT> *rg,
		size_t n0, size_t m0, size_t T,
		uugraph& Gs
	);
	
	/**
	 * @brief Barabasi-Albert model: No vertex growth variant
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
	 * @param[in] n0 The total number of vertices
	 * @param[in] m0 The number of edges to connect each vertex to
	 * @param[in] T The number of steps of the algorithm
	 * @param[in] rg The random number generator used
	 * @param[out] Gs The resulting graph following this Barabasi-Albert model variant
	 *
	 * @pre Seeding the RNG is done before valling the function.
	 */
	template<
		class G = default_random_engine,
		typename dT = size_t
	>
	void BA_no_vertex_growth(
		drandom_generator<G,dT> *rg,
		size_t n0, size_t m0, size_t T,
		uugraph& Gs
	);

} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph

#include <lgraph/generate_graphs/social/ba_preferential_attachment.cpp>
#include <lgraph/generate_graphs/social/ba_random_attachment.cpp>
#include <lgraph/generate_graphs/social/ba_no_vertex_growth.cpp>
