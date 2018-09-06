#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdint>
#include <numeric>
#include <random>
#include <vector>
#include <cmath>
using namespace std;

// Custom includes
#include <lgraph/data_structures/random_generator.hpp>
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>

namespace lgraph {
using namespace utils;

namespace networks {
namespace classic {

	/* 1-REGULAR GRAPHS */

	/**
	 * @brief Generate an undirected 1-regular graph of @e n nodes.
	 *
	 * If @e n is odd then the graph has @e n - 1 nodes.
	 *
	 * A 1-regular graph is a graph where the edges are of the form
	 * (u, u + 1) where u takes the even values in [0,n).
	 *
	 * @param n Number of nodes.
	 * @param[out] G Generated 1-regular undirected graph.
	 * @pre @e n >= 2
	 */
	void one_regular(size_t n, uugraph& G);

	/**
	 * @brief Generate an undirected 1-regular graph of @e n nodes.
	 *
	 * See @ref one_regular(size_t, uugraph&) for the description
	 * of a 1-regular graph.
	 *
	 * The orientation of the edges depends on the value of @e d.
	 *
	 * @param n Number of nodes.
	 * @param[out] G Generated 1-regular undirected graph.
	 * @param d Indicate orientation of edges.
	 *	Values:
	 *  - 1 for clockwise orientation: edges (u,v) such that u < v
	 *  - 2 for counter-clockwise orientation: edges (u,v) such that u > v
	 *  - 3 for both orientations
	 * @pre @e n >= 2
	 */
	void one_regular(size_t n, udgraph& G, uint8_t d = 1);

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
