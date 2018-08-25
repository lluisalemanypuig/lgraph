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

namespace lgraph {
using namespace utils;

namespace networks {
namespace random {

	/**
	 * @brief Generate a graph that follows the Watts & Strogatz's model
	 *
	 * @param N Number of nodes of the graph
	 * @param k Number of the @e k nearest neighbours in a ring topology.
	 * @param p Probability of rewiring an edge
	 */
	template<
		class G = default_random_engine,
		typename cT = size_t
	>
	void watts_strogatz(
		crandom_generator<G,cT> *rg,
		size_t N, size_t k, cT p,
		uugraph& Gs
	);

} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph

#include <lgraph/generate_graphs/random/watts_strogatz.cpp>
