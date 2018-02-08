#pragma once

/// C++ incldues
#include <algorithm>
#include <vector>
using namespace std;

/// Custom includes
#include "data_structures/graph.hpp"

namespace dsa {
using namespace utils;

namespace networks {
namespace metrics {
namespace centralities {
	
	/*
	Returns the normalised degree centrality of each node.
	*/
	void degree(const graph& G, vector<double>& dc);
	
	/*
	Returns the closeness centrality of each node.
	*/
	void closeness(const graph& G, vector<double>& cc);
	
	/*
	Returns the betweenness centrality of each node.
	*/
	void betweenness(const graph& G, vector<double>& bc);
	
} // -- namespace centralities
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace dsa

