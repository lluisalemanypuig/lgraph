#pragma once

// C includes

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
#include <lgraph/data_structures/udgraph.hpp>
#include <lgraph/utils/logger.hpp>

namespace lgraph {
namespace networks {
namespace classic {
using namespace utils;

	/**
	 * @brief Generate a complete graph of @e N nodes
	 * @param N Number of nodes
	 * @param[out] Gs Generated complete undirected graph
	 */
	void complete_graph(size_t N, uugraph& Gs);

	/**
	 * @brief Generate a complete graph of @e N nodes
	 * @param N Number of nodes
	 * @param[out] Gs Generated complete directed graph
	 */
	void complete_graph(size_t N, udgraph& Gs);

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
