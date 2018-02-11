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
	Returns the normalised degree centrality of a single node or of all nodes.
	*/
	double degree(const graph& G, node u);
	void degree(const graph& G, vector<double>& dc);
	
	/*
	Returns the closeness centrality of a node or of all nodes.
	The last function admits the all-to-all distances
	of the nodes in the graph
	*/
	double closeness(const graph& G, node u);
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

