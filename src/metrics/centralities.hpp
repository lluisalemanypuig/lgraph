#pragma once

/// C++ incldues
#include <algorithm>
#include <vector>
using namespace std;

/// Custom includes
#include "src/graph.hpp"

namespace dsa {
namespace networks {
namespace metrics {
namespace centralities {
	
	/*
	Returns the degree centrality of each node.
	dc[i] denotes the degree centrality of the i-th vertex.
	*/
	void degree(const graph& G, vector<double>& dc);
	
} // -- namespace centralities
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace dsa

