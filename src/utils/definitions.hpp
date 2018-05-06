#pragma once

// C++ includes
#include <cstdint>
#include <limits>
using namespace std;

namespace lgraph {
namespace utils {

	typedef int32_t node;
	typedef vector<node> neighbourhood;
	typedef neighbourhood::const_iterator ncit;
	typedef neighbourhood::iterator nit;
	typedef pair<node, node> edge;

	template<class T> void UNUSED(const T& t) { (void)t; }

	// maximum values for 'size_t' and 'doubles'
	// used as infinites
	const static size_t z_inf = numeric_limits<size_t>::max();
	const static double r_inf = numeric_limits<double>::max();

	// shorthand for any maximum value
	template<typename T> T inf_t() { return numeric_limits<T>::max(); }

	// default type for 'null' edge weight
	typedef size_t _new_;

} // -- namespace utils
} // -- namespace lgraph
