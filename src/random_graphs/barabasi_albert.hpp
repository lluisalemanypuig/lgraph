#pragma once

/// C++ includes
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <random>
#include <vector>
using namespace std;

#include "src/random_generator.hpp"
#include "src/graph.hpp"

namespace dsa {
namespace networks {
namespace random {
namespace Barabasi_Albert {

using namespace utils;

	/*
	Implementation of the three main variants of the Barabasi-Albert model:
	
		- Preferential Attachment: builds a graph with n0 + T vertices.
			The first step is to build an empty graph with n0 vertices.
			Then add T new vertices, each of which is connected to m0
			already existing vertices of the graph each with a probability
			proportional to their degree.
			
		- Random Attachment: similar to the preferential attachment model.
			However, at each step, the m0 connections are made with
			probabilities uniformly at random.
			
		- No growth variant: similar to the preferential attachment model.
			This time, it differs from it in that the initial graph has
			the same number of vertices as the final graph: n0. The T steps
			are used to make m0 connections at each step. More precisely:
			1. Create an empty graph with n0 vertices
			2. For step ti = 1 to T
				2.1. Choose a vertex with probability proportional to its
					 degree. Let u be that vertex.
				2.2. Make m0 connections with some of the other vertices
					 in the graph. Each edge (u, v) is added with probability
					 proportional to the degree of v.
	
	Parameters:
	- n0: number of initial vertices
	- m0: edges to add at each step
	- T: number of steps
	- Gs: resulting graph
	*/
	
	template<
		class G = default_random_engine,
		typename dT = size_t
	>
	void preferential_attachment(
		size_t n0, size_t m0, size_t T,
		drandom_generator<G,dT> *rg,
		graph& Gs
	);
	
	template<
		class G = default_random_engine,
		typename dT = size_t
	>
	void random_attachment(
		size_t n0, size_t m0, size_t T,
		drandom_generator<G,dT> *rg,
		graph& Gs
	);
	
	template<
		class G = default_random_engine,
		typename dT = size_t
	>
	void no_vertex_growth(
		size_t n0, size_t m0, size_t T,
		drandom_generator<G,dT> *rg,
		graph& Gs
	);

} // -- namespace Barabasi_Albert
} // -- namespace random
} // -- namespace networks
} // -- namespace dsa

#include "ba_preferential_attachment.cpp"
#include "ba_random_attachment.cpp"
#include "ba_no_vertex_growth.cpp"
