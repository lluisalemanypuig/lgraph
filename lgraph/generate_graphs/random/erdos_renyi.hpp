#pragma once

// C++ includes
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <random>
#include <vector>
#include <cmath>

// lgraph includes
#include <lgraph/generate_graphs/classic/classic.hpp>
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
