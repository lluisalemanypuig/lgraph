#pragma once

/// C++ incldues
#include <algorithm>
#include <limits>
#include <vector>
using namespace std;

/// Custom includes
#include "data_structures/graph.hpp"
#include "graph_traversal/traversal.hpp"

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
	The second function admits the all-to-all distances
	of the nodes in the graph
	*/
	void closeness(const graph& G, vector<double>& cc);
	void closeness(const graph& G, const vector<vector<size_t> >& atad, vector<double>& cc);
	
	/*
	Returns the betweenness centrality of each node.
	*/
	void betweenness(const graph& G, vector<double>& bc);
	
} // -- namespace centralities
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace dsa

