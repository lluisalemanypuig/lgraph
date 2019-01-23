#pragma once

// C includes

// C++ includes
#include <iostream>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/xxgraph.hpp>
#include <lgraph/data_structures/wxgraph.hpp>
#include <lgraph/data_structures/wugraph.hpp>
#include <lgraph/data_structures/wdgraph.hpp>
#include <lgraph/data_structures/uxgraph.hpp>
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>
using namespace lgraph;
using namespace utils;

#include <lgraph/generate_graphs/classic/classic.hpp>
using namespace networks::classic;

#include <lgraph/communities/communities.hpp>
using namespace networks::communities;

#include <lgraph/io/io.hpp>
using namespace io;

// Custom includes
#include "time.hpp"

namespace graph_driver {

	/// Driver for unweighted graphs
	void driver_unweighted(bool directed);

	/// Driver for weighted graphs
	void driver_weighted(bool directed);

} // -- namespace graph_driver
