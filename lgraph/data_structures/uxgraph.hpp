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
#include <lgraph/data_structures/xxgraph.hpp>
#include <lgraph/utils/definitions.hpp>

namespace lgraph {

/**
 * @brief Abstract class for unweighted (ux) graphs.
 *
 * This class implements the unweighted graph data structure based on
 * adjacency lists.
 */
class uxgraph : public xxgraph {
	protected:

		/**
		 * @brief Computes the list of unique unweighted edges of this graph.
		 *
		 * An unweighted edge is a pair of indices each of which is within
		 * the interval [0,@e n) where @e n is the number of nodes of this
		 * graph.
		 *
		 * @param[out] edges The collection of unweighted edges.
		 * @return Stores in @ref edges the list of unweighted edges of this
		 * graph.
		 */
		virtual void get_unique_edges(std::vector<edge>& edges) const = 0;

	public:
		/// Default onstructor.
		uxgraph();
		/// Constructor with number of nodes.
		uxgraph(size_t n);
		/**
		 * @brief Constructor with adjacency list and number of edges.
		 * @param adj The adjacency list of the graph.
		 * @param n_edges The number of edges in the adjacency list.
		 */
		uxgraph(const std::vector<neighbourhood>& adj, size_t n_edges);
		/// Destructor.
		virtual ~uxgraph();

		// Initialises graph with n nodes after deallocating memory
		void init(size_t n);
		/**
		 * @brief Initialises the graph with adjacency list and number of edges.
		 * @param adj The adjacency list of the graph.
		 * @param n_edges The number of edges in the adjacency list.
		 */
		void init(const std::vector<neighbourhood>& adj, size_t n_edges);

		// OPERATORS

		/**
		 * @brief Outputs to the ostream @e os this graph.
		 * @param os The ostream object to output to.
		 * @param g THe graph to be output.
		 */
		inline friend
		std::ostream& operator<< (std::ostream& os, const uxgraph& g) {
			for (node i = 0; i < g.n_nodes(); ++i) {
				os << i << ":";
				const neighbourhood& ni = g.adjacency_list[i];

				for (node j : ni) {
					os << " " << j;
				}

				if (i < g.n_nodes() - 1) {
					os << std::endl;
				}
			}
			return os;
		}

		/**
		 * @brief Assignation operator for undirected weighted graphs.
		 *
		 * The contents of this object are first cleared. Then, the contents
		 * of @e g are copied into this.
		 *
		 * @param g The graph to be copied.
		 * @return Returns a reference to the copy of @e g.
		 */
		uxgraph& operator= (const uxgraph& g);

		// MODIFIERS

		/**
		 * @brief Adds an edge to this graph.
		 *
		 * The attribute @ref num_edges is incremented by one.
		 *
		 * @param e A pair of nodes.
		 */
		void add_edge(const edge& e);

		/**
		 * @brief Adds all edges taken from a list.
		 *
		 * The attribute @ref num_edges is incremented as many times
		 * as elements there are in @e edge_list.
		 *
		 * @param edge_list A list of pairs of nodes.
		 */
		void add_edges(const std::vector<edge>& edge_list);

		/**
		 * @brief Adds an edge between nodes @e u and @e v.
		 *
		 * The attribute @ref num_edges is incremented by one.
		 *
		 * @param u The fist node of the edge.
		 * @param v The second node of the edge.
		 */
		virtual void add_edge(node u, node v) = 0;

		/**
		 * @brief Deletes all memory used by the graph.
		 *
		 * The value @ref num_edges is set to 0.
		 */
		void clear();

		// GETTERS

		/// Returns whether this graph is weighted or not (returns false).
		bool is_weighted() const;

		/**
		 * @brief Returns all unique edges of this graph.
		 *
		 * See method @ref get_unique_edges(std::vector<edge>&)const for details.
		 */
		void edges(std::vector<edge>& all_edges) const;

};

} // -- namespace lgraph
