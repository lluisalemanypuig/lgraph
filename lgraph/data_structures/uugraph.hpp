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
#include <lgraph/data_structures/uxgraph.hpp>
#include <lgraph/utils/definitions.hpp>

namespace lgraph {

/**
 * @brief Unweighted undirected (uu) graphs.
 *
 * This class implements the unweighted undirected graph data structure
 * based on adjacency lists.
 */
class uugraph : public uxgraph {
	public:
		/// Default constructor
		uugraph();
		/**
		 * @brief Constructor with adjacency list
		 * @param adj The adjacency list of the graph.
		 */
		uugraph(const std::vector<neighbourhood>& adj);
		/**
		 * @brief Constructor with adjacency list and number of edges
		 * @param adj The adjacency list of the graph.
		 * @param n_edges The number of edges in the adjacency list.
		 */
		uugraph(const std::vector<neighbourhood>& adj, size_t n_edges);
		/// Destructor
		~uugraph();

		using uxgraph::init;
		/**
		 * @brief Initialises the graph with adjacency list
		 * @param adj The adjacency list of the graph.
		 */
		void init(const std::vector<neighbourhood>& adj);

		// MODIFIERS

		using uxgraph::add_edge;
		void add_edge(node u, node v);
		using uxgraph::remove_edge;
		void remove_edge(node u, node v);
		void remove_node(node u);

		// GETTERS

		bool has_edge(node u, node v) const;
		bool is_directed() const;

	protected:

		/**
		 * @brief Computes the list of unique edges of this graph
		 *
		 * Since this graph is undirected, the edge (u,v) is the same
		 * as (v,u). This method computes the list of edges so that the
		 * result is lexicographically sorted. An unweighted edge is a
		 * pair of indices each of which is within the interval [0,@e n)
		 * where @e n is the number of nodes of this graph.
		 *
		 * @param[out] edges The collection of edges.
		 * @return Stores in @ref edges the lexicographically sorted list of
		 * unweighted edges of this graph.
		 */
		void get_unique_edges(std::vector<edge>& edges) const;
};

} // -- namespace lgraph
