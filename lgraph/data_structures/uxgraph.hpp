#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

// Custom includes
#include <lgraph/utils/definitions.hpp>
#include <lgraph/data_structures/xxgraph.hpp>

namespace lgraph {
namespace utils {

/**
 * @brief Abstract class for unweighted (ux) graphs.
 *
 * This class implements the unweighted graph data structure based on
 * adjacency lists.
 */
class uxgraph : public xxgraph {
	protected:

		/**
		 * @brief Computes the list of unique weighted edges of this graph
		 *
		 * Since this graph is undirected, the edge (u,v) is the same
		 * as (v,u). This method computes the list of edges so that the
		 * result is lexicographically sorted.
		 * Each index is within the interval [0,@e n) where @e n is the
		 * number of nodes of this graph.
		 *
		 * @param[out] edges The collection of weighted edges
		 * @return Stores in @ref edges the lexicographically sorted list of
		 * edges of this graph
		 */
		virtual void get_unique_edges(set<edge>& edges) const = 0;

	public:
		/// Constructor
		uxgraph();
		/// Destructor
		virtual ~uxgraph();

		/**
		 * @brief Initialises the attributes of a graph with @e n nodes
		 *
		 * First, it clears all the memory allocated so far. Then, initialises all
		 * the attributes so that it can store all the necessary information.
		 * @param n Number of nodes of the graph
		 */
		void init(size_t n);

		// OPERATORS

		/**
		 * @brief Outputs to the ostream @e os this graph
		 * @param os The ostream object to output to.
		 * @param g THe graph to be output.
		 */
		inline friend
		ostream& operator<< (ostream& os, const uxgraph& g) {
			for (node i = 0; i < g.n_nodes(); ++i) {
				os << i << ":";
				const neighbourhood& ni = g.adjacency_list[i];

				for (node j = 0; j < ni.n_elems(); ++j) {
					os << " " << ni[j];
				}

				if (i < g.n_nodes() - 1) {
					os << endl;
				}
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
		uxgraph& operator= (const uxgraph& g);

		// MODIFIERS

		/**
		 * @brief Adds an edge to this graph.
		 *
		 * The attribute @ref num_edges is incremented by one.
		 * @param e A pair of nodes
		 */
		virtual void add_edge(const edge& e) = 0;

		/**
		 * @brief Adds all edges taken from a list
		 *
		 * The attribute @ref num_edges is incremented as many times
		 * as elements there are in @e edge_list.
		 * @param edge_list A list of pairs of nodes
		 */
		void add_edges(const vector<edge>& edge_list);

		/**
		 * @brief Adds an edge between nodes @e u and @e v
		 *
		 * The attribute @ref num_edges is incremented by one.
		 *
		 * @param u The fist node of the edge
		 * @param v The second node of the edge
		 */
		virtual void add_edge(node u, node v) = 0;

		/**
		 * @brief Removes an edge from this graph.
		 *
		 * The attribute @ref num_edges is decremented by one.
		 * @param e A pair of nodes
		 */
		virtual void remove_edge(const edge& e) = 0;

		/**
		 * @brief Removes all edges taken from a list
		 *
		 * The attribute @ref num_edges is decremented by one.
		 * @param edge_list A list of edges
		 */
		void remove_edges(const vector<edge>& edge_list);

		/**
		 * @brief Removes an edge from this graph.
		 *
		 * The attribute @ref num_edges is decremented by one.
		 * @param u The fist node of the edge
		 * @param v The second node of the edge
		 */
		virtual void remove_edge(node u, node v) = 0;

		/**
		 * @brief Deletes all memory used by the graph
		 *
		 * The value @ref num_edges is set to 0.
		 */
		void clear();

		// GETTERS

		/// Returns whether this graph is weighted or not (returns false).
		bool is_weighted() const;

		/**
		 * @brief Returns all unique edges of this graph
		 *
		 * See method @ref get_unique_edges(set<edge>&)const for details.
		 */
		virtual void edges(vector<edge>& all_edges) const = 0;

		// I/O

		bool read_from_file(const string& filename);
		bool read_from_file(const char *filename);
		bool store_in_file(const string& filename);
		bool store_in_file(const char *filename);

};

} // -- namespace utils
} // -- namespace lgraph
