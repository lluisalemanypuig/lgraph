#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

// Custom includes
#include <lgraph/data_structures/uxgraph.hpp>
#include <lgraph/utils/definitions.hpp>

namespace lgraph {
namespace utils {

/**
 * @brief Unweighted directed (ud) graphs.
 *
 * This class implements the unweighted directed graph data structure
 * based on adjacency lists.
 */
class udgraph : public uxgraph {
	protected:

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
		void get_unique_edges(vector<edge>& edges) const;

	public:
		/// Default constructor
		udgraph();
		/**
		 * @brief Constructor with adjacency lists
		 * @param adj The adjacency list of the graph
		 */
		udgraph(const vector<neighbourhood>& adj);
		/**
		 * @brief Constructor with adjacency lists
		 * @param adj The adjacency list of the graph
		 * @param n_edges The number of edges in the adjacency list
		 */
		udgraph(const vector<neighbourhood>& adj, size_t n_edges);
		/// Destructor
		~udgraph();

		// MODIFIERS

		using uxgraph::add_edge;
		void add_edge(node u, node v);
		using uxgraph::remove_edge;
		void remove_edge(node u, node v);
		void remove_node(node u);

		// GETTERS

		bool has_edge(node u, node v) const;
		bool is_directed() const;

};

} // -- namespace utils
} // -- namespace lgraph
