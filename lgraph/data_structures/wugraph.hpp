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
#include <utility>
#include <vector>

// lgraph includes
#include <lgraph/data_structures/wxgraph.hpp>
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/utils/definitions.hpp>

namespace lgraph {

/**
 * @brief Weighted undirected graphs.
 *
 * This class implements the weighted, undirected graph data structure
 * based on adjacency lists.
 *
 * @param T In case of weighted graphs, this parameter indicates
 * the type of the edge weights.
 */
template<class T>
class wugraph : public wxgraph<T> {
	protected:

		/**
		 * @brief Computes the list of unique weighted edges of this graph.
		 *
		 * Since this graph is undirected, the edge (u,v) is the same
		 * as (v,u). This method computes the list of edges so that the
		 * result is lexicographically sorted. A weighted edge is a pair
		 * of an edge and a value representing the weight of that edge.
		 * An edge is a pair of indices, each of which is within the
		 * interval [0,@e n) where @e n is the number of nodes of this graph.
		 *
		 * @param[out] edges The collection of weighted edges.
		 * @return Stores in @ref edges the lexicographically sorted list of
		 * weighted edges of this graph.
		 */
		void get_unique_edges(std::vector<std::pair<edge, T> >& edges) const;

		/**
		 * @brief Computes the list of unique edges of this graph.
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

	public:
		/// Default constructor.
		wugraph();
		/**
		 * @brief Constructor with adjacency list and list of weights.
		 * @param adj The adjacency list of the graph.
		 * @param wl The weights for every edge.
		 */
		wugraph(const std::vector<neighbourhood>& adj, const std::vector<weight_list<T> >& wl);
		/**
		 * @brief Constructor with adjacency list, list of weights and number of edges.
		 * @param adj The adjacency list of the graph.
		 * @param wl The weights for every edge.
		 * @param n_edges The number of edges in the adjacency list.
		 */
		wugraph(const std::vector<neighbourhood>& adj, const std::vector<weight_list<T> >& wl, size_t n_edges);
		/// Destructor.
		~wugraph();

		using wxgraph<T>::init;
		/**
		 * @brief Initialises the graph with adjacency list and list of weights.
		 * @param adj The adjacency list of the graph.
		 * @param wl The weights for every edge.
		 */
		void init(const std::vector<neighbourhood>& adj, const std::vector<weight_list<T> >& wl);

		// MODIFIERS

		using wxgraph<T>::add_edge;
		void add_edge(node u, node v, const T& w);
		using wxgraph<T>::set_edge_weight;
		void set_edge_weight(node u, node v, const T& w);
		using wxgraph<T>::remove_edge;
		void remove_edge(node u, node v);
		void remove_node(node u);

		// GETTERS

		bool has_edge(node u, node v) const;
		T edge_weight(node u, node v) const;
		bool is_directed() const;
		uxgraph* to_unweighted() const;

};

} // -- namespace lgraph

#include <lgraph/data_structures/wugraph.cpp>
