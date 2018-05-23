#pragma once

// C++ incldues
#include <vector>
using namespace std;

// Custom includes
#include "data_structures/uugraph.hpp"

namespace lgraph {
using namespace utils;

namespace networks {
namespace metrics {
namespace clustering {

	/**
	 * @brief Global Clustering Coefficient of an undirected unweighted graph.
	 * @param G The graph to be evaluated
	 * @return Returns the global clustering coefficient of G as defined in
	 * Newman, M. E. J. (2010). Networks. An introduction. Oxford
	 * University Press, Oxford.
	 */
	double gcc(const uugraph& G);

	/**
	 * @brief Mean Local Clustering Coefficient of an undirected unweighted graph.
	 * @param G The graph to be evaluated
	 * @return Returns the global clustering coefficient of G as defined in
	 * Watts, D. J. and Strogatz, S. H. (1998). Collective
	 * dynamics of ’small-world’ networks. Nature, 393:440–442.
	 */
	double mlcc(const uugraph& G);

} // -- namespace clustering
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace lgraph

