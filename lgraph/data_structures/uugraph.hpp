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
#include <lgraph/utils/definitions.hpp>
#include <lgraph/data_structures/uxgraph.hpp>

namespace lgraph {
namespace utils {

/**
 * @brief Unweighted undirected (ux) graphs.
 *
 * This class implements the unweighted undirected graph data structure
 * based on adjacency lists.
 */
class uugraph : public uxgraph {
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
		 * @param[out] edges The collection of edges
		 * @return Stores in @ref edges the lexicographically sorted list of
		 * unweighted edges of this graph
		 */
		void get_unique_edges(vector<edge>& edges) const;

	public:
		/// Constructor
		uugraph();
		/// Destructor
		~uugraph();

		// MODIFIERS

		void add_edge(const edge& e);
		void add_edge(node u, node v);

		void remove_edge(const edge& e);
		void remove_edge(node u, node v);

		// GETTERS

		bool has_edge(node u, node v) const;
		bool is_directed() const;

};

} // -- namespace utils
} // -- namespace lgraph
