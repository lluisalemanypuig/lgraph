/*********************************************************************
 * lgraph
 * Copyright (C) 2018-2019 Lluís Alemany Puig
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Contact: Lluís Alemany Puig (lluis.alemany.puig@gmail.com)
 * 
 ********************************************************************/

#pragma once

// lgraph includes
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>

namespace lgraph {
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
