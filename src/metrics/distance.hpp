#pragma once

/// C++ incldues
#include <functional>
#include <numeric>
#include <vector>
using namespace std;

/// Custom includes
#include "data_structures/graph.hpp"
#include "utils/definitions.hpp"

namespace dsa {
using namespace utils;

namespace networks {
namespace metrics {
namespace distance {
	
	/*
	Returns the largest distance between two vertices (diameter).
	ds is the matrix that represents the all-to-all distances.
	*/
	size_t max_distance(const graph& G, const vector<vector<size_t> >& ds);
	
	/*
	Returns the mean geodesic distance between two vertices.
	ds is the matrix that represents the all-to-all distances.
	*/
	double mean_distance(const graph& G, const vector<vector<size_t> >& ds);
	
	/*
	Returns the mean closeness centrality of the network G.
	cc is the vector with each vertex's closeness centrality.
	*/
	double mcc(const graph& G, const vector<double>& cc);
	
	
} // -- namespace distance
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace dsa

