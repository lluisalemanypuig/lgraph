#pragma once

/// C++ incldues
#include <functional>
#include <numeric>
#include <vector>
using namespace std;

/// Custom includes
#include "data_structures/uugraph.hpp"
#include "metrics/centralities.hpp"
#include "utils/definitions.hpp"
#include "graph_traversal/traversal.hpp"

namespace lgraph {
using namespace utils;

namespace networks {
namespace metrics {
namespace distance {
	
	/*
	Returns the largest distance between two vertices (diameter).
	ds is the matrix that represents the all-to-all distances.
	*/
	_new_ max_distance(const uugraph& G);
	_new_ max_distance(const uugraph& G, const vector<vector<_new_> >& ds);
	
	/*
	Returns the mean geodesic distance between two vertices.
	ds is the matrix that represents the all-to-all distances.
	*/
	double mean_distance(const uugraph& G);
	double mean_distance(const uugraph& G, const vector<vector<_new_> >& ds);
	
	/*
	Returns the mean closeness centrality of the network G.
	cc is the vector with each vertex's closeness centrality.
	*/
	double mcc(const uugraph& G);
	double mcc(const uugraph& G, const vector<double>& cc);
	
	
} // -- namespace distance
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace lgraph

