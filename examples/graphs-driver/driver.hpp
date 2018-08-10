#pragma once

// C includes

// C++ includes
#include <iostream>
using namespace std;

// Custom includes
#include <lgraph/data_structures/xxgraph.hpp>

#include <lgraph/data_structures/wxgraph.hpp>
#include <lgraph/data_structures/wugraph.hpp>

#include <lgraph/data_structures/uxgraph.hpp>
#include <lgraph/data_structures/uugraph.hpp>
using namespace lgraph::utils;

namespace graph_driver {

	/// Driver for unweighted graphs
	void driver_unweighted(bool directed);

	/// Driver for weighted graphs
	void driver_weighted(bool directed);

}
