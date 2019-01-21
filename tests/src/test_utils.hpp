#pragma once

// C++ includes
#include <string>
#include <limits>

// lgraph includes
#include <lgraph/data_structures/node_path.hpp>

namespace test_utils {

bool comp_ux_paths
(const lgraph::node_path<lgraph::_new_>& p, const lgraph::node_path<lgraph::_new_>& q);

template<typename T>
std::string distout(T d) {
	if (d == std::numeric_limits<T>::max()) {
		return "inf";
	}
	return std::to_string(d);
}

} // -- namespace test_utils
