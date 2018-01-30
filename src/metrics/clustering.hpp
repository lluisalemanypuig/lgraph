#pragma once

/// C++ incldues
#include <vector>
using namespace std;

/// Custom includes
#include "data_structures/graph.hpp"

namespace dsa {
namespace networks {
namespace metrics {
namespace clustering {
	
	// Global Clustering Coefficient of G as defined in
	// Newman, M. E. J. (2010). Networks. An introduction. Oxford
	// University Press, Oxford.
	double gcc(const graph& G);
	
	// Mean Local Clustering Coefficient of G as defined in
	// Watts, D. J. and Strogatz, S. H. (1998). Collective
	// dynamics of ’small-world’ networks. Nature, 393:440–442.
	double mlcc(const graph& G);

} // -- namespace clustering
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace dsa

