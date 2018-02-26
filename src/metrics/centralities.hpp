#pragma once

/// C++ incldues
#include <algorithm>
#include <limits>
#include <vector>
using namespace std;

/// Custom includes
#include "data_structures/graph.hpp"
#include "data_structures/graph_path.hpp"
#include "graph_traversal/traversal.hpp"

namespace dsa {
using namespace utils;

namespace networks {
namespace metrics {
namespace centralities {
	
	/// DEGREE CENTRALITY

	/*
	Returns the normalised degree centrality of a single node or
	of all nodes.
	*/
	double degree(const graph& G, node u);
	void degree(const graph& G, vector<double>& dc);
	
	/// CLOSENESS CENTRALITY

	/*
	Returns the normalised closeness centrality of a node or of
	all nodes. The last function admits the all-to-all distances
	of the nodes in the graph
	*/
	double closeness(const graph& G, node u);
	void closeness(const graph& G, vector<double>& cc);
	void closeness(const graph& G, const vector<vector<size_t> >& atad, vector<double>& cc);
	
	/// BETWEENNESS CENTRALITY

	/*
	This centrality measure is implemented following the recommendations given in [Newman, 2010]:
	- Any path from vertex 's' to vertex 't' is considered to include both endpoints.
	- The equation to calculate the centrality also considers paths from any vertex to itself.

	Furthermore, only the pairs of vertices (s,t) with s <= t are considered.
	Finally, this metric is also normalised.

	[Newman, 2010] Newman, M. E. J. (2010). Networks. An introduction. Oxford
	University Press, Oxford.
	*/

	/*
	Returns the betweenness centrality of a single node, and of all nodes.
	The second function of each pair admits a parameter giving all the shortest
	paths between any two vertices of the graph as boolean paths.
	*/
	double betweenness(const graph& G, node u);
	double betweenness(const graph& G, const vector<vector<boolean_path_set> >& paths, node u);
	void betweenness(const graph& G, vector<double>& bc);
	void betweenness(const graph& G, const vector<vector<boolean_path_set> >& paths, vector<double>& bc);
	
} // -- namespace centralities
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace dsa

