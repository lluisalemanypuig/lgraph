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
namespace networks {
namespace random {

/**
 * @brief Implementation of a number of variants of the Barabasi-Albert model.
 *
 * These variants are:
 *	* Preferential Attachment
 *	* Random Attachment
 *	* No growth variant
 */
namespace Barabasi_Albert {

using namespace utils;

	/**
	 * @brief Barabasi-Albert model: Preferentail attachment variant
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
	void preferential_attachment(
		drandom_generator<G,dT> *rg,
		size_t n0, size_t m0, size_t T,
		uugraph& Gs
	);
	
	/**
	 * @brief Barabasi-Albert model: Random attachment variant
	 *
	 * Similar to the @ref preferential_attachment model.
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
	void random_attachment(
		drandom_generator<G,dT> *rg,
		size_t n0, size_t m0, size_t T,
		uugraph& Gs
	);
	
	/**
	 * @brief Barabasi-Albert model: No vertex growth variant
	 *
	 * Similar to the @ref preferential_attachment model. This time, it
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
	void no_vertex_growth(
		drandom_generator<G,dT> *rg,
		size_t n0, size_t m0, size_t T,
		uugraph& Gs
	);

} // -- namespace Barabasi_Albert
} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph

#include <lgraph/generate_graphs/social/random/ba_preferential_attachment.cpp>
#include <lgraph/generate_graphs/social/random/ba_random_attachment.cpp>
#include <lgraph/generate_graphs/social/random/ba_no_vertex_growth.cpp>
