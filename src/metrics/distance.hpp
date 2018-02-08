#pragma once

/// C++ incldues
#include <vector>
using namespace std;

/// Custom includes
#include "data_structures/graph.hpp"

namespace dsa {
using namespace utils;

namespace networks {
namespace metrics {
namespace distance {
	
	/*
	Returns the largest distance between two vertices (diameter).
	*/
	size_t geodesic_dist(const graph& G);
	size_t geodesic_dist(const graph& G, const vector<size_t>& ds);
	
	/*
	Returns the mean geodesic distance between two vertices.
	*/
	double mgc(const graph& G);
	double mgc(const graph& G, const vector<size_t>& ds);
	
	/*
	Returns the mean closeness centrality of the network G.
	*/
	double mcc(const graph& G);
	double mcc(const graph& G, const vector<double>& cc);
	
	
} // -- namespace distance
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace dsa

