#pragma once

// C++ includes
#include <vector>
using namespace std;

// Custom includes
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>
#include <lgraph/graph_traversal/bfs.hpp>

namespace lgraph {
using namespace utils;
using namespace traversal::bfs;

namespace networks {
namespace communities {

	// CONNECTED COMPONENTS

	/**
	 * @brief Computes the connected components of this graph.
	 * @param[in] g The input graph.
	 * @param[out] comps @e comps[i] = @e j if, and only if, the @e i-th vertex
	 * belongs to the @e j-th connected component, where @e i is a node index. \n
	 * The labels start at 0. Any label's value greater or equal than
	 * the number of vertices of @e g is not valid.
	 * @param[out] bins If this parameter is not null then @e bins[i] contains
	 * how many vertices are in the @e i-th connected component.
	 * @returns Returns the amount of connected components in @e g.
	 */
	size_t connected_components
	(
		const uugraph& g,
		vector<size_t>& comps,
		vector<size_t> *bins = nullptr
	);

	/**
	 * @brief Computes the strongly connected components of this graph.
	 * @param[in] g The input graph.
	 * @param[out] comps @e comps[i] = @e j if, and only if, the @e i-th vertex
	 * belongs to the @e j-th connected component, where @e i is a node index. \n
	 * The labels start at 0. Any label's value greater or equal than
	 * the number of vertices of @e g is not valid.
	 * @param[out] bins If this parameter is not null then @e bins[i] contains
	 * how many vertices are in the @e i-th connected component.
	 * @returns Returns the amount of connected components in @e g.
	 */
	size_t connected_components
	(
		const udgraph& g,
		vector<size_t>& comps,
		vector<size_t> *bins = nullptr
	);

} // -- namespace communities
} // -- namespace networks
} // -- namespace lgraph
