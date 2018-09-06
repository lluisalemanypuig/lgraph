#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdint>
#include <numeric>
#include <random>
#include <vector>
#include <cmath>
using namespace std;

// Custom includes
#include <lgraph/data_structures/random_generator.hpp>
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>

namespace lgraph {
using namespace utils;

namespace networks {
namespace classic {

	/* COMPLETE GRAPHS */

	/**
	 * @brief Generate an undirected complete graph of @e N nodes.
	 * @param N Number of nodes.
	 * @param[out] G Generated complete undirected graph.
	 */
	void complete_graph(size_t N, uugraph& G);

	/**
	 * @brief Generate a directed complete graph of @e N nodes.
	 * @param N Number of nodes.
	 * @param[out] G Generated complete directed graph. For each pair of
	 * nodes u,v there are two pairs of directed edges (u,v) and (v,u).
	 */
	void complete_graph(size_t N, udgraph& G);

	/* LINEAR TREES */

	/**
	 * @brief Generate a liner tree of @e N nodes.
	 *
	 * For N = 1, the graph is a single node with no neighbours.
	 *
	 * For N = 2, the graph consists of two nodes joined by an edge.
	 *
	 * For N >= 3, the graph has N nodes,
	 * - the 0-th node has as neighbours the nodes 1,
	 * - the 1-st node has as neighbours the nodes 0 and 2,
	 * - the 2-nd node has as neighbouts the nodes 1 and 3,
	 * - ...
	 * - the (N-2)-th node has as neighbours the nodes N-3 and N-1
	 * - the (N-1)-th node has as neighbours the nodes N-2
	 *
	 * @param N Number of nodes.
	 * @param[out] G Generated cycle graph.
	 */
	void linear_tree(size_t N, uugraph& G);

	/**
	 * @brief Generate a liner tree of @e N nodes with edge orientation.
	 *
	 * See @ref linear_tree(size_t, uugraph&) for the description of a linear
	 * tree.
	 *
	 * The orientation of the edges depends on the value of @e d.
	 *
	 * @param N Number of nodes.
	 * @param[out] G Generated cycle graph.
	 * @param d Indicate orientation of edges.
	 *	Values:
	 *  - 1 for clockwise orientation: edges (u,v) such that u < v
	 *  - 2 for counter-clockwise orientation: edges (u,v) such that u > v
	 *  - 3 for both orientations
	 */
	void linear_tree(size_t N, udgraph& G, uint8_t d = 1);

	/* CYCLE GRAPHS */

	/**
	 * @brief Generate a cycle graph of @e N nodes.
	 *
	 * A cycle graph is a graph with 3 or more nodes. It is, basically,
	 * a linear tree in which the nodes 0 and N-1 are connected by an edge.
	 *
	 * See @ref linear_tree(size_t, uugraph&) for the description of a linear
	 * tree.
	 *
	 * @param N Number of nodes.
	 * @param[out] G Generated cycle graph.
	 */
	void cycle_graph(size_t N, uugraph& G);

	/**
	 * @brief Generate a cycle graph of @e N nodes wih edge orientation.
	 *
	 * See @ref cycle_graph(size_t, uugraph&) for the description of a cycle
	 * graph.
	 *
	 * The orientation of the edges depends on the value of @e clockwise.
	 *
	 * @param N Number of nodes.
	 * @param[out] G Generated cycle graph.
	 * @param d Indicate orientation of edges.
	 *	Values:
	 *  - 1 for clockwise orientation: edges (u,v) such that u < v
	 *  - 2 for counter-clockwise orientation: edges (u,v) such that u > v
	 *  - 3 for both orientations
	 */
	void cycle_graph(size_t N, udgraph& G, uint8_t d = 1);

	/* STAR GRAPHS */

	/**
	 * @brief Generate a star graph of @e N nodes.
	 *
	 * A star graph is a graph in which the nodes from 1 to N-1 are connected
	 * to node 0.
	 *
	 * @param N Number of nodes.
	 * @param[out] G Generated cycle graph.
	 */
	void star_graph(size_t N, uugraph& G);

	/**
	 * @brief Generate a star graph of @e N nodes wih edge orientation
	 *
	 * A star graph is a graph in which the nodes from 1 to N-1 are connected
	 * to node 0.
	 *
	 * The orientation of the edges depends on the value of @e clockwise.
	 *
	 * @param N Number of nodes.
	 * @param[out] G Generated cycle graph.
	 * @param d Indicate orientation of edges.
	 *	Values:
	 *  - 1 for outwards orientation: edges (u,v) such that u < v
	 *  - 2 for inwards orientation: edges (u,v) such that u > v
	 *  - 3 for both orientations
	 */
	void star_graph(size_t N, udgraph& G, uint8_t d = 1);

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
