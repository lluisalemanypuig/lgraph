#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <fstream>
#include <utility>
#include <vector>
using namespace std;

// Custom includes
#include "uxgraph.hpp"
#include "utils/definitions.hpp"

namespace lgraph {
namespace utils {

/**
 * @brief Undirected weighted (uw) graphs.
 *
 * @param T In case of weighted graphs, this parameter indicates
 * the type of the edge weights
 */
template<class T>
class uwgraph : public uxgraph<T> {
	private:
		/**
		 * @brief Weight list for each node
		 *
		 * @ref weights[u] is a list of values of type @e T
		 * where @ref weights[u][v] represents the weight of
		 * edge between nodes @e u and @e v.
		 */
		vector<vector<T> > weights;

		// GETTERS

		/**
		 * @brief Computes the list of unique weighted edges of this graph
		 *
		 * Since this graph is undirected, the edge (u,v) is the same
		 * as (v,u). This method computes the list of edges so that the
		 * result is lexicographically sorted.
		 *
		 * @param[out] edges The collection of weighted edges
		 * @return Stores in @ref edges the lexicographically sorted list of
		 * weighted edges of this graph
		 */
		void get_unique_edges(set<pair<edge, T> >& edges) const;

	private:

		// MODIFIERS

		// Initialise the list of weights
		void initialise_weights(size_t n);

		// Clear the list of weights
		void clear_weights();

		// Adds the weight w to the specified node's list
		void add_weight(node u, T w);

		// Removes the weight from the position 'p'
		// of list of neighbours of node u
		void remove_weight(node u, nit p);

	public:
		uwgraph();

		/**
		 * @brief Constructor: create a grpah with @e n nodes
		 *
		 * Calls the method init with value @e n
		 * @param n Number of nodes for this graph
		 */
		uwgraph(size_t n);
		~uwgraph();

		// OPERATORS

		/**
		 * @brief Outputs to the ostream @e os this graph
		 * @param os The ostream object to output to.
		 * @param g THe graph to be output.
		 */
		inline friend
		ostream& operator<< (ostream& os, const uwgraph<T>& g) {
			for (size_t i = 0; i < g.adjacency_list.size(); ++i) {
				os << i << ":";
				ncit begin = g.adjacency_list[i].begin();
				ncit end = g.adjacency_list[i].end();
				auto weights_it = g.weights[i].begin();

				for (ncit it = begin; it != end; ++it, ++weights_it) {
					os << " " << *it;
					os << "(";
					os << *weights_it;
					os << ")";
				}

				if (i < g.adjacency_list.size() - 1) os << endl;
			}
			return os;
		}

		/**
		 * @brief Assignation operator for undirected weighted graphs
		 *
		 * The contents of this object are first cleared. Then, the contents
		 * of @e g are copied into this.
		 *
		 * @param g The graph to be copied
		 * @return Returns a reference to the copy of @e g
		 */
		uwgraph& operator= (const uwgraph& g);

		// MODIFIERS

		void add_edges(const vector<edge>& edge_list, const vector<T>& ws = vector<T>());

		// GETTERS

		// Returns the weight of the existing edge (u,v)
		T edge_weight(node u, node v) const;

		// Returns the weights to all neighbours of node u
		void get_weights(node u, vector<T>& ws) const;

		/**
		 * @brief Returns a constant reference to all the weights of node @e u
		 * @param u The node whose weight list is requested
		 * @return The weight list of node @e u
		 */
		const vector<T>& get_weights(node u) const;

		// I/O

		bool read_from_file(const string& filename);
		bool read_from_file(const char *filename);
		bool store_in_file(const string& filename);
		bool store_in_file(const char *filename);
};

} // -- namespace utils
} // -- namespace lgraph

#include "uwgraph.cpp"
