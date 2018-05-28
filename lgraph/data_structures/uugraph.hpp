#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <iostream>
#include <fstream>
#include <iomanip>
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
 * @brief Undirected unweighted (uu) graphs.
 *
 * This class is not a template since it lacks weights. Implements
 * undirecected unweighted graphs implemented with adjacency lists.
 */
class uugraph : public uxgraph<_new_> {
	private:

		// GETTERS

		/**
		 * @brief Computes the list of unique unweighted edges of this graph
		 *
		 * Since this graph is undirected, the edge (u,v) is the same
		 * as (v,u). This method computes the list of edges so that the
		 * result is lexicographically sorted. An edge is a pair of two indices.
		 * Each index is within the interval [0,@e n) where @e n is the
		 * number of nodes of this graph.
		 *
		 * @param[out] edges The collection of unweighted edges
		 * @return Stores in @ref edges the lexicographically sorted list of
		 * unweighted edges of this graph
		 */
		void get_unique_edges(set<edge>& edges) const;

	private:

		// MODIFIERS

		// Initialise the list of weights, if necessary
		void initialise_weights(size_t n);

		// Clear the list of weights, if necessary
		void clear_weights();

		// Adds the weight w to the specified node's list
		void add_weight(node u, _new_ w);

		// Removes the weight from the position 'p'
		// of list of neighbours of node u
		void remove_weight(node u, nit p);

	public:
		uugraph();

		/**
		 * @brief Constructor: create a grpah with @e n nodes
		 *
		 * Calls the method init with value @e n
		 * @param n Number of nodes for this graph
		 */
		uugraph(size_t n);

		~uugraph();

		// OPERATORS
		
		inline friend
		ostream& operator<< (ostream& os, const uugraph& g) {
			for (size_t i = 0; i < g.adjacency_list.size(); ++i) {
				os << i << ":";
				ncit begin = g.adjacency_list[i].begin();
				ncit end = g.adjacency_list[i].end();
				for (ncit it = begin; it != end; ++it) os << " " << *it;
				if (i < g.adjacency_list.size() - 1) os << endl;
			}
			return os;
		}

		/**
		 * @brief Assignation operator for undirected unweighted graphs
		 *
		 * The contents of this object are first cleared. Then, the contents
		 * of @e g are copied into this.
		 *
		 * @param g The graph to be copied
		 * @return Returns a reference to the copy of @e g
		 */
		uugraph& operator= (const uugraph& g);
		
		// MODIFIERS

		void add_edges(const vector<edge>& edge_list, const vector<_new_>& ws = vector<_new_>());

		// GETTERS

		/**
		 * @brief Returns all unique edges of this graph
		 *
		 * See method @ref get_unique_edges(set<edge>&)const for details.
		 */
		void edges(vector<edge>& all_edges) const;

		// Returns true if there is an undirected edge between nodes u and v
		bool has_edge(node u, node v) const;

		// Returns the weight of the existing edge (u,v)
		_new_ edge_weight(node u, node v) const;

		// Returns the weights to all neighbours of node u
		// Returns a list of degree-many 1's
		void get_weights(node u, vector<_new_>& ws) const;

		// I/O

		bool read_from_file(const string& filename);
		bool read_from_file(const char *filename);
		bool store_in_file(const string& filename);
		bool store_in_file(const char *filename);
};

} // -- namespace utils
} // -- namespace lgraph

