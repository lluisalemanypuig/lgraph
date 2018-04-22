#pragma once

/// C++ includes
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <random>
#include <vector>
using namespace std;

/// Custom includes
#include "data_structures/random_generator.hpp"
#include "data_structures/uugraph.hpp"
#include "utils/logger.hpp"

namespace lgraph {
namespace networks {
namespace random {
namespace switching {

using namespace utils;

	/*
	Given a directed graph Gs, let E be the set of edges
	of Gs. The switching model consists on applying Q*|E|
	times the following operation:
	1. Take two edges (s,t) and (u,v), where
		s != t and u != v	- (no self-loops)
		s != u and s != v	- (both edges must be different and
		t != u and t != v	  can't share edges)
	2. Exchange endpoints: (s,v) and (u,t)
	*/

	template<
		class G = default_random_engine,
		typename dT = size_t
	>
	void switching_model(size_t Q, drandom_generator<G,dT> *rg, uugraph& Gs);

} // -- namespace switching
} // -- namespace random
} // -- namespace networks
} // -- namespace dsa

#include "switching.cpp"
