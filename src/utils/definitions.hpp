#pragma once

/// C++ includes
#include <limits>
using namespace std;

namespace dsa {
namespace utils {

	template<class T>
	void UNUSED(const T& t) { (void)t; }

	const static size_t inf = numeric_limits<size_t>::max();

} // -- namespace utils
} // -- namespace dsa
