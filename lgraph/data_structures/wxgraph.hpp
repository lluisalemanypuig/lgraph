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
#include <lgraph/data_structures/xxgraph.hpp>
#include <lgraph/data_structures/svector.hpp>
#include <lgraph/utils/definitions.hpp>

namespace lgraph {
namespace utils {

/**
 * @brief Abstract class for weighted (ux) graphs.
 *
 * This class implements the weighted graph data structure based on
 * adjacency lists.
 *
 * @param T Parameter that indicates the type of the edge weights
 */
template<class T>
class wxgraph : public xxgraph {
	protected:

		/**
		 * @brief Weight list for each node
		 *
		 * @ref weights[u] is a list of values of type @e T
		 * where @ref weights[u][v] represents the weight of
		 * edge between nodes @e u and @e v.
		 */
		vector<weight_list<T> > weights;

		// MODIFIERS

		/// Initialises the list of weights
		void initialise_weights(size_t n);

		/// Clears the list of weights
		void clear_weights();

		/**
		 * @brief Computes the list of unique weighted edges of this graph
		 *
		 * Since this graph is undirected, the edge (u,v) is the same
		 * as (v,u). This method computes the list of edges so that the
		 * result is lexicographically sorted. A weighted edge is a pair
		 * of two elements: an edge (a pair of two indices) and a weight.
		 * Each index is within the interval [0,@e n) where @e n is the
		 * number of nodes of this graph.
		 *
		 * @param[out] edges The collection of weighted edges
		 * @return Stores in @ref edges the lexicographically sorted list of
		 * weighted edges of this graph
		 */
		virtual void get_unique_edges(set<pair<edge, T> >& edges) const = 0;

	public:
		/// Constructor
		wxgraph();
		/// Destructor
		virtual ~wxgraph();

		// Initialise graph with n nodes
		void init(size_t n);

		// OPERATORS

		/**
		 * @brief Outputs to the ostream @e os this graph
		 * @param os The ostream object to output to.
		 * @param g THe graph to be output.
		 */
		inline friend
		ostream& operator<< (ostream& os, const wxgraph<T>& g) {
			for (node i = 0; i < g.n_nodes(); ++i) {
				os << i << ":";
				const neighbourhood& ni = g.adjacency_list[i];
				const weight_list<T>& wi = g.weights[i];

				for (node j = 0; j < ni.n_elems(); ++j) {
					os << " " << ni[j];
					os << "(" << wi[j] << ")";
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
		wxgraph& operator= (const wxgraph& g);

		// MODIFIERS

		/**
		 * @brief Adds an edge to this graph.
		 *
		 * The attribute @ref num_edges is incremented by one.
		 * @param e A pair of nodes
		 * @param w The weight of the edge
		 */
		virtual void add_edge(const edge& e, const T& w) = 0;

		/**
		 * @brief Adds all edges taken from a list
		 *
		 * The attribute @ref num_edges is incremented as many times
		 * as elements there are in @e edge_list.
		 * @param edge_list A list of pairs of nodes
		 * @param ws A list of weights. The i-th edge has weight @e ws[i].
		 */
		void add_edges(const vector<edge>& edge_list, const vector<T>& ws);

		/**
		 * @brief Adds an edge between nodes @e u and @e v
		 *
		 * The attribute @ref num_edges is incremented by one.
		 *
		 * @param u The fist node of the edge
		 * @param v The second node of the edge
		 * @param w The weight of the edge
		 */
		virtual void add_edge(node u, node v, const T& w) = 0;

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

		/// Returns whether this graph is weighted or not (returns true).
		bool is_weighted() const;

		/**
		 * @brief Returns the weight of the edge (@e u, @e v)
		 * @pre The edge (@e u, @e v) must be in the graph
		 */
		virtual T edge_weight(node u, node v) const = 0;

		/**
		 * @brief Returns a constant reference to all the weights of node @e u
		 * @param u The node whose weight list is requested
		 * @return The weight list of node @e u
		 */
		const weight_list<T>& get_weights(node u) const;

		/**
		 * @brief Returns the weights to all neighbours of node @e u
		 * @pre @e u must be in the graph
		 */
		void get_weights(node u, weight_list<T>& ws) const;

		/**
		 * @brief Returns all unique edges of this graph
		 *
		 * See method @ref get_unique_edges(set<pair<edge,T> >& edges)const for details.
		 */
		void edges(vector<pair<edge, T> >& all_edges) const;

		// I/O

		bool read_from_file(const string& filename);
		bool read_from_file(const char *filename);
		bool store_in_file(const string& filename);
		bool store_in_file(const char *filename);
};

} // -- namespace utils
} // -- namespace lgraph

#include <lgraph/data_structures/wxgraph.cpp>
