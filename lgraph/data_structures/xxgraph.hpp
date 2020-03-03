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
#include <map>

// lgraph includes
#include <lgraph/utils/definitions.hpp>

namespace lgraph {

/**
 * @brief Abstract class for the graph data structure.
 *
 * This interface requires the implementation of several methods
 * to complete the implementation of a data structure for graphs
 * that uses adjacency lists. It has only two attributes: @ref adjacency_list,
 * that stores the adjacency list of each node, and @ref num_edges
 * that contains the number of edges in the graph. Depending on
 * the type of graph implemented these two attributes should be
 * modified accordingly.
 */
class xxgraph {
	protected:
		/// The neighbourhood of every node.
		std::vector<neighbourhood> adjacency_list;
		/// The amount of edges in this graph.
		size_t num_edges;

		/**
		 * @brief Returns the position of node @e u's position in the neighbourhood @e n.
		 *
		 * If the position is equal to the number of elements of the list @e n then @e u is in the list.
		 * Performs a linear search to find it.
		 *
		 * @param n The neighbourhood of a node in the graph.
		 * @param u The node to look for in the neighbourhood.
		 * @return Returns a value equal to the number of elements in the list @e n if
		 * node @e u is not in it. Returns a value smaller than that if otherwise.
		 */
		size_t get_neighbour_position(const neighbourhood& n, node u) const;

		/// Initialise the list of neighbourhoods with @e n instances.
		void initialise_adjacency_list(size_t n);

		/// Clear the list of neighbourhoods.
		void clear_adjacency_list();

		/**
		 * @brief Initialises the adjacency list of this graph.
		 *
		 * The value @ref num_edges is set to 0.
		 */
		void initialise_parent_graph(size_t n);

		/**
		 * @brief Clears the adjacency list of this graph.
		 *
		 * The value @ref num_edges is set to 0.
		 */
		void clear_parent_graph();

	public:
		/// Constructor.
		xxgraph();
		/// Destructor.
		virtual ~xxgraph();

		/**
		 * @brief Initialises the attributes of a graph with @e n nodes.
		 *
		 * First, it clears all the memory allocated so far. Then, initialises all
		 * the attributes so that it can store all the necessary information.
		 *
		 * @param n Number of nodes of the graph.
		 */
		virtual void init(size_t n) = 0;

		// MODIFIERS

		/**
		 * @brief Adds one node to the graph.
		 * @return Returns the index of the new node.
		 */
		size_t add_node();

		/**
		 * @brief Adds @e n nodes to the graph.
		 *
		 * The nodes are assigned in consecutive, increasing values.
		 * @return Returns the index of the last added node.
		 */
		size_t add_n_nodes(size_t n);

		/**
		 * @brief Removes an edge from this graph.
		 *
		 * The attribute @ref num_edges is decremented by one.
		 * @param e A pair of nodes.
		 * @pre @e e must be an edge of the graph.
		 */
		void remove_edge(const edge& e);

		/**
		 * @brief Removes all edges taken from a list.
		 *
		 * The attribute @ref num_edges is decremented by one.
		 * @param edge_list A list of edges.
		 */
		void remove_edges(const std::vector<edge>& edge_list);

		/**
		 * @brief Removes an edge from this graph.
		 *
		 * The attribute @ref num_edges is decremented by one.
		 * @param u The fist node of the edge.
		 * @param v The second node of the edge.
		 * @pre @e u must be a node from the graph.
		 */
		virtual void remove_edge(node u, node v) = 0;

		/**
		 * @brief Rmoves a node from the graph.
		 *
		 * Removes its entry in the adjacency list @ref adjacency_list
		 * and removes it from the neighbourhood list of the other nodes.
		 *
		 * @param u The node to be removed.
		 * @pre @e u must be a node from the graph.
		 * @post The indexes higher than @e u's are decreased by one.
		 */
		virtual void remove_node(node u) = 0;

		// GETTERS

		/// Returns true if node @e u is in this graph.
		bool has_node(node u) const;

		/**
		 * @brief Returns true if there is an edge between nodes @e u and @e v
		 * @pre @e u and @e v must be in the graph.
		 */
		virtual bool has_edge(node u, node v) const = 0;

		/**
		 * @brief Returns the number of nodes.
		 * @return Returns the size of @ref adjacency_list.
		 */
		size_t n_nodes() const;

		/**
		 * @brief Returns the number of edges.
		 * @return Returns the value @ref num_edges.
		 */
		size_t n_edges() const;

		/// Returns all nodes (as integers).
		void nodes(std::vector<node>& all_nodes) const;

		/**
		 * @brief Returns the neighbourhood of node u.
		 * @param u The node whose neighbourhood we want.
		 * @pre @e u must be a node from the graph.
		 */
		const neighbourhood& get_neighbours(node u) const;

		/**
		 * @brief Returns the number of neighbours of u.
		 * @param u The node whose neighbourhood size we want
		 * @return Returns the size of the neighbourhood of @e u,
		 * that is, the size of the list in @ref adjacency_list[@e u].
		 * @pre @e u must be a node from the graph.
		 */
		size_t degree(node u) const;

		/**
		 * @brief Returns the genus of the graph.
		 * @return Returns the result of:
		 \verbatim
		 number of edges - number of vertices + 1
		 \endverbatim
		 */
		long long int genus() const;

		/**
		 * @brief Returns whether the graph is weighted or unweighted.
		 * @return Returns true if the graph is weighted. Returns false if otherwise.
		 */
		virtual bool is_weighted() const = 0;

		/**
		 * @brief Returns whether the graph is directed or undirected.
		 * @return Returns true if the graph is directed. Returns false if otherwise.
		 */
		virtual bool is_directed() const = 0;

		// GRAPH FEATURES

		/// Returns the adjacency matrix of this graph.
		void get_adjacency_matrix(std::vector<std::vector<bool> >& adj_mat) const;

		/**
		 * @brief Returns the degree sequence of the graph.
		 * @param[out] ds A list of pairs: for each degree the amount
		 * of nodes in this graph that have that degree. The degree
		 * of a node is detailed in @ref degree.
		 */
		void get_degree_sequence(std::map<size_t, size_t>& ds) const;

		/**
		 * @brief Returns the number of triangles in this graph.
		 * @return Returns the number of cycles of length 3.
		 */
		size_t n_triangles() const;
};

} // -- namespace lgraph
