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
 * @brief Switching model algorithm
 *
 * So far implemented only on undirected unweighted graphs.
 */
namespace switching {

using namespace utils;

	/**
	 * @brief Applies the switching model to an undirected unweighted graph
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
	 * where |E| is the number of edges in the graph
	 * @param[in]  rg The RNG used to select the nodes for endpoint exchange
	 * @param[out] Gs The graph on which the switching model is applied.
	 * @pre The graph on which to apply the model must have at least two edges.
	 */
	template<
		class G = default_random_engine,
		typename dT = size_t
	>
	void switching_model(size_t Q, drandom_generator<G,dT> *rg, uugraph& Gs);

} // -- namespace switching
} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph

#include "switching.cpp"
