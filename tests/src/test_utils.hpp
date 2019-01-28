#pragma once

// C++ includes
#include <sstream>
#include <string>
#include <limits>

// lgraph includes
#include <lgraph/data_structures/node_path.hpp>

// custom includes
#include "definitions.hpp"

namespace test_utils {

bool comp_ux_paths
(const lgraph::node_path<lgraph::_new_>& p, const lgraph::node_path<lgraph::_new_>& q);

bool comp_wx_paths
(const lgraph::node_path<float>& p, const lgraph::node_path<float>& q);

template<typename T>
std::string floatpointout_dist(T d) {
	if (d == std::numeric_limits<T>::max()) {
		return "inf";
	}
	std::stringstream out;
	out.setf(std::ios::fixed);
	out.precision(3);
	out << d;
	return out.str();
}

template<typename T>
std::string floatpointout_metric(T d) {
	if (d == std::numeric_limits<T>::max()) {
		return "inf";
	}
	std::ostringstream out;
	out.setf(std::ios::fixed);
	out.precision(8);
	out << d;
	return out.str();
}

} // -- namespace test_utils
