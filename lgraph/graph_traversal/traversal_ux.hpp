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

// C++ includes
#include <vector>

// lgraph includes
#include <lgraph/data_structures/boolean_path.hpp>
#include <lgraph/data_structures/node_path.hpp>
#include <lgraph/data_structures/uxgraph.hpp>

namespace lgraph {
namespace traversal {

// ----------------------------------------------------------------
// UNWEIGHTED FUNCTIONS (for directed/undirected unweighted graphs)
// ----------------------------------------------------------------

/* DISTANCE COMPUTATION */

// NODE-NODE

/**
 * @brief Directed/Undirected distance between two nodes.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[in] source The source node.
 * @param[in] target The target node.
 * @return The shortest distance between @e source and @e target.
 */
_new_ uxdistance(const uxgraph *G, node source, node target);
/**
 * @brief Directed/Undirected distance between two nodes.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[in] source The source node.
 * @param[in] target The target node.
 * @param[out] n_paths The number of shortest paths between @e source and
 * @e target.
 * @return The shortest distance between @e source and @e target.
 */
_new_ uxdistance(const uxgraph *G, node source, node target, size_t& n_paths);

// NODE-ALL

/**
 * @brief Directed/Undirected distance between a node to the rest of the
 * graph's nodes.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[in] source The source node.
 * @param[out] uxdistances The i-th position contains the directed/undirected
 * distance between the source node and the i-th node of the graph.
 */
void uxdistance(const uxgraph *G, node source, std::vector<_new_>& uxdistances);
/**
 * @brief Directed/Undirected distance between a node to the rest of the
 * graph's nodes.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[in] source The source node.
 * @param[out] uxdistances The i-th position contains the directed/undirected
 * distance between the source node and the i-th node of the graph.
 * @param[out] n_paths The i-th position contains the number of shortest paths
 * between the source node and the i-th node.
 */
void uxdistance(
	const uxgraph *G, node source,
	std::vector<_new_>& uxdistances, std::vector<size_t>& n_paths
);

// ALL-ALL

/**
 * @brief Directed/Undirected distance between all pairs of nodes.
 *
 * Applies the Floyd-Warshall algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[out] ds The shortest directed/undirected distance between all pairs
 * of nodes.
 */
void uxdistances(const uxgraph *G, std::vector<std::vector<_new_> >& ds);
/**
 * @brief Directed/Undirected distance between all pairs of nodes.
 *
 * Applies the Floyd-Warshall algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[out] ds The shortest directed/undirected distance between all pairs
 * of nodes.
 * @param[out] n_paths The number of shortest paths between each pair of nodes.
 */
void uxdistances(
	const uxgraph *G,
	std::vector<std::vector<_new_> >& ds,
	std::vector<std::vector<size_t> >& n_paths
);

/* PATH FINDING IN UNWEIGHTED GRAPHS */

// NODE-NODE

/**
 * @brief A directed/undirected path between two nodes.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[in] source The source node.
 * @param[in] target The target node.
 * @param[out] p A path between the nodes.
 */
void uxpath(const uxgraph *G, node source, node target, node_path<_new_>& p);
/**
 * @brief A directed/undirected path between two nodes.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[in] source The source node.
 * @param[in] target The target node.
 * @param[out] p A path between the nodes.
 */
void uxpath(const uxgraph *G, node source, node target, boolean_path<_new_>& p);

/**
 * @brief All directed/undirected path between two nodes.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[in] source The source node.
 * @param[in] target The target node.
 * @param[out] ps The paths between the nodes.
 */
void uxpaths(const uxgraph *G, node source, node target, node_path_set<_new_>& ps);
/**
 * @brief All directed/undirected path between two nodes.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[in] source The source node.
 * @param[in] target The target node.
 * @param[out] ps The paths between the nodes.
 */
void uxpaths(const uxgraph *G, node source, node target, boolean_path_set<_new_>& ps);

// NODE-ALL

/**
 * @brief A directed/undirected path between a source node and any other node
 * in the graph.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[in] source The source node.
 * @param[out] ps A path between the nodes.
 */
void uxpath(const uxgraph *G, node source, std::vector<node_path<_new_> >& ps);
/**
 * @brief A directed/undirected path between a source node and any other node
 * in the graph.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[in] source The source node.
 * @param[out] ps A path between the nodes.
 */
void uxpath(const uxgraph *G, node source, std::vector<boolean_path<_new_> >& ps);

/**
 * @brief All directed/undirected paths between a source node and any other
 * node in the graph.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[in] source The source node.
 * @param[out] ps All paths between the source node and all other nodes in
 * the graph.
 */
void uxpaths(const uxgraph *G, node source, std::vector<node_path_set<_new_> >& ps);
/**
 * @brief All directed/undirected paths between a source node and any other
 * node in the graph.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[in] source The source node.
 * @param[out] ps All paths between the source node and all other nodes in
 * the graph.
 */
void uxpaths(const uxgraph *G, node source, std::vector<boolean_path_set<_new_> >& ps);

// ALL-ALL

/**
 * @brief A directed/undirected path between all pairs of nodes in the graph.
 *
 * Applies Floyd-Warshall's algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[out] ps A path between the nodes.
 */
void uxpath(const uxgraph *G, std::vector<std::vector<node_path<_new_> > >& ps);
/**
 * @brief A directed/undirected path between all pairs of nodes in the graph.
 *
 * Applies Floyd-Warshall's algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[out] ps A path between the nodes.
 */
void uxpath(const uxgraph *G, std::vector<std::vector<boolean_path<_new_> > >& ps);

/**
 * @brief All directed/undirected paths between all pairs of nodes in the graph.
 *
 * Applies Floyd-Warshall's algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[out] ps A path between the nodes.
 */
void uxpaths(const uxgraph *G, std::vector<std::vector<node_path_set<_new_> > >& ps);
/**
 * @brief All directed/undirected paths between all pairs of nodes in the
 * graph.
 *
 * Applies Floyd-Warshall's algorithm.
 *
 * @param[in] G A directed/undirected unweighted graph.
 * @param[out] ps A path between the nodes.
 */
void uxpaths(const uxgraph *G, std::vector<std::vector<boolean_path_set<_new_> > >& ps);

} // -- namespace traversal
} // -- namespace lgraph
