#pragma once

// C++ includes
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <random>
#include <vector>
#include <cmath>
using namespace std;

// Custom includes
#include <lgraph/data_structures/random_generator.hpp>
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/utils/logger.hpp>

namespace lgraph {
namespace networks {
namespace random {

/**
 * @brief Erdos-Renyi model of graphs
 *
 * Also known as binomial graphs
 */
namespace Erdos_Renyi {

using namespace utils;

	/**
	 * @brief Constructs the random graph G{n,p}
	 *
	 * The implementation follows the algorithm in [1].
	 *
	 * [1] Vladimir Batagelj and Ulrik Brandes,
	 * "Efficient generation of large random networks",
	 * Phys. Rev. E, 71, 036113, 2005.
	 *
	 * @param[in]	N Number of nodes of the graph
	 * @param[in]	p Probability of making an edge
	 * @param[in]  rg The RNG used to generate floating point numbers
	 * @param[out] Gs The binomial graph constructed
	 */
	template<
		class G = default_random_engine,
		typename cT = float
	>
	void erdos_renyi(crandom_generator<G,cT> *rg, size_t N, double p, uugraph& Gs);

} // -- namespace Erdos_Renyi
} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph

#include <lgraph/random_graphs/erdos_renyi.cpp>
