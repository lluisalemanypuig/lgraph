#pragma once

// C++ includes
#include <cstdint>
#include <limits>
#include <vector>
using namespace std;

// Custom includes
#include <lgraph/data_structures/svector.hpp>

namespace lgraph {
namespace utils {

	/// Typedef for a graph node's index
	typedef int32_t node;
	/// Typedef for a list of nodes
	typedef svector<node> neighbourhood;
	/// Typedef for a list of weights
	template<class T>
	using weight_list = svector<T>;
	/// Typedef for a constant iterator through a @ref neighbourhood
	typedef neighbourhood::const_iterator ncit;
	/// Typedef for a non-constant iterator through a @ref neighbourhood
	typedef neighbourhood::iterator nit;
	/// Typedef for an edge of a graph
	typedef pair<node, node> edge;

	/// Function to avoid 'Unused parameter' warnings
	template<class T> inline void UNUSED(const T& t) { (void)t; }

	/// Constant for maximum value for unsigned integer type
	const static size_t z_inf = numeric_limits<size_t>::max();
	/// Constant for maximum value for double-precision floating point type
	const static double r_inf = numeric_limits<double>::max();

	/// Shorthand for the maximum value of any type
	template<typename T> inline T inf_t() { return numeric_limits<T>::max(); }

	/// Typedef for the type of weight in unweighted graphs
	typedef uint32_t _new_;

} // -- namespace utils
} // -- namespace lgraph
