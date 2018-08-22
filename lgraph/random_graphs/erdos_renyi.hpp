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
 * @brief Erdos-Renyi model of graphs
 *
 * Also known as binomial graphs
 */
namespace Erdos_Renyi {

using namespace utils;

	/**
	 * @brief Constructs a graph following the Erdos-Renyi model
	 *
	 * @param[in]	p Probability of making an edge
	 * @param[in]  rg The RNG used to select the nodes for endpoint exchange
	 * @param[out] Gs The binomial graph constructed
	 */
	template<
		class G = default_random_engine,
		typename dT = size_t
	>
	void erdos_renyi(drandom_generator<G,dT> *rg, double p, uugraph& Gs);

} // -- namespace Erdos_Renyi
} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph

#include <lgraph/random_graphs/erdos_renyi.cpp>
