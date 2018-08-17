#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <fstream>
#include <utility>
#include <vector>
using namespace std;

// Custom includes
#include <lgraph/data_structures/wxgraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>
#include <lgraph/utils/definitions.hpp>

namespace lgraph {
namespace utils {

/**
 * @brief Weighted directed graphs.
 *
 * This class implements the weighted, directed graph data structure
 * based on adjacency lists.
 *
 * @param T In case of weighted graphs, this parameter indicates
 * the type of the edge weights
 */
template<class T>
class wdgraph : public wxgraph<T> {
	protected:

		/**
		 * @brief Computes the list of unique weighted edges of this graph
		 *
		 * A weighted edge is a pair of an edge and a value representing the
		 * weight of that edge. An edge is a pair of indices, each of which is
		 * within the interval [0,@e n) where @e n is the number of nodes of
		 * this graph.
		 *
		 * @param[out] edges The collection of weighted edges
		 * @return Stores in @ref edges the lexicographically sorted list of
		 * weighted edges of this graph
		 */
		void get_unique_edges(set<pair<edge, T> >& edges) const;

		/**
		 * @brief Computes the list of unique edges of this graph
		 *
		 * An unweighted edge is a pair of indices each of which is within the
		 * interval [0,@e n) where @e n is the number of nodes of this graph.
		 *
		 * @param[out] edges The collection of edges
		 * @return Stores in @ref edges the lexicographically sorted list of
		 * unweighted edges of this graph
		 */
		void get_unique_edges(set<edge>& edges) const;

	public:
		/// Constructor
		wdgraph();
		/// Destructor
		~wdgraph();

		// MODIFIERS

		void add_edge(const edge& e, const T& w);
		void add_edge(node u, node v, const T& w);

		void remove_edge(const edge& e);
		void remove_edge(node u, node v);

		// GETTERS

		bool has_edge(node u, node v) const;
		T edge_weight(node u, node v) const;
		bool is_directed() const;
		uxgraph* to_unweighted() const;

};

} // -- namespace utils
} // -- namespace lgraph

#include <lgraph/data_structures/wdgraph.cpp>
