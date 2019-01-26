#pragma once

// C++ includes
#include <fstream>
#include <vector>

// lgraph includes
#include <lgraph/data_structures/xxgraph.hpp>
#include <lgraph/data_structures/uxgraph.hpp>
#include <lgraph/utils/definitions.hpp>

namespace lgraph {

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
		 * @brief Weight list for each node.
		 *
		 * @ref weights[u] is a list of values of type @e T
		 * where @ref weights[u][v] represents the weight of
		 * edge between nodes @e u and @e v.
		 */
		std::vector<weight_list<T> > weights;

		// MODIFIERS

		/// Initialises the list of weights.
		void initialise_weights(size_t n);

		/// Clears the list of weights.
		void clear_weights();

		/**
		 * @brief Computes the list of unique weighted edges of this graph.
		 *
		 * A weighted edge is a pair of an edge and a value representing
		 * the weight of that edge. An edge is a pair of indices, each
		 * of which is within the interval [0,@e n) where @e n is the
		 * number of nodes of this graph.
		 *
		 * @param[out] edges The collection of weighted edges.
		 * @return Stores in @ref edges the list of weighted edges of this
		 * graph.
		 */
		virtual void get_unique_edges(std::vector<std::pair<edge, T> >& edges) const = 0;

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
		/// Default constructor.
		wxgraph();
		/// Constructor with number of nodes.
		wxgraph(size_t n);
		/**
		 * @brief Constructor with adjacency list, list of weights and number of edges.
		 * @param adj The adjacency list of the graph.
		 * @param wl The weights for every edge.
		 * @param n_edges The number of edges in the adjacency list.
		 */
		wxgraph(const std::vector<neighbourhood>& adj,
				const std::vector<weight_list<T> >& wl,
				size_t n_edges);
		/// Destructor.
		virtual ~wxgraph();

		// Initialise graph with n nodes
		void init(size_t n);
		/**
		 * @brief Initialise with adjacency list, list of weights and number of edges.
		 * @param adj The adjacency list of the graph.
		 * @param wl The weights for every edge.
		 * @param n_edges The number of edges in the adjacency list.
		 */
		void init(const std::vector<neighbourhood>& adj,
				  const std::vector<weight_list<T> >& wl,
				  size_t n_edges);

		// OPERATORS

		/**
		 * @brief Outputs to the ostream @e os this graph.
		 * @param os The ostream object to output to.
		 * @param g THe graph to be output.
		 */
		inline friend
		std::ostream& operator<< (std::ostream& os, const wxgraph<T>& g) {
			for (node i = 0; i < g.n_nodes(); ++i) {
				os << i << ":";
				const neighbourhood& ni = g.adjacency_list[i];
				const weight_list<T>& wi = g.weights[i];

				auto ni_it = ni.begin();
				auto wi_it = wi.begin();
				for (; ni_it != ni.end(); ++ni_it, ++wi_it) {
					os << " " << *ni_it << "(" << *wi_it << ")";
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
		wxgraph& operator= (const wxgraph& g);

		// MODIFIERS

		/**
		 * @brief Adds an edge to this graph.
		 *
		 * The attribute @ref num_edges is incremented by one.
		 *
		 * @param e A pair of nodes.
		 * @param w The weight of the edge.
		 */
		void add_edge(const edge& e, const T& w);

		/**
		 * @brief Adds all edges taken from a list.
		 *
		 * The attribute @ref num_edges is incremented as many times
		 * as elements there are in @e edge_list.
		 *
		 * @param edge_list A list of pairs of nodes.
		 * @param ws A list of weights. The i-th edge has weight @e ws[i].
		 */
		void add_edges(const std::vector<edge>& edge_list, const std::vector<T>& ws);

		/**
		 * @brief Adds an edge between nodes @e u and @e v.
		 *
		 * The attribute @ref num_edges is incremented by one.
		 *
		 * @param u The fist node of the edge.
		 * @param v The second node of the edge.
		 * @param w The weight of the edge.
		 */
		virtual void add_edge(node u, node v, const T& w) = 0;

		/**
		 * @brief Sets the weight to an edge.
		 *
		 * Assign to the specified edge the given weight.
		 *
		 * @param e A pair of nodes.
		 * @param w The weight of the edge.
		 */
		void set_edge_weight(const edge& e, const T& w);

		/**
		 * @brief Sets the weight to an edge.
		 *
		 * Assign to the specified edge the given weight.
		 *
		 * @param u The fist node of the edge.
		 * @param v The second node of the edge.
		 * @param w The weight of the edge.
		 */
		virtual void set_edge_weight(node u, node v, const T& w) = 0;

		/**
		 * @brief Deletes all memory used by the graph.
		 *
		 * The value @ref num_edges is set to 0.
		 */
		void clear();

		// GETTERS

		/// Returns whether this graph is weighted or not (returns true).
		bool is_weighted() const;

		/**
		 * @brief Returns the weight of the edge (@e u, @e v).
		 * @pre The edge (@e u, @e v) must be in the graph.
		 */
		virtual T edge_weight(node u, node v) const = 0;

		/**
		 * @brief Returns a constant reference to all the weights of node @e u.
		 * @param u The node whose weight list is requested.
		 * @return The weight list of node @e u.
		 */
		const weight_list<T>& get_weights(node u) const;

		/**
		 * @brief Returns the weights to all neighbours of node @e u.
		 * @pre @e u must be in the graph.
		 */
		void get_weights(node u, weight_list<T>& ws) const;

		/**
		 * @brief Returns all unique edges of this graph.
		 *
		 * See method @ref get_unique_edges(std::vector<std::pair<edge,T> >& edges)const for details.
		 */
		void edges(std::vector<std::pair<edge, T> >& all_edges) const;

		/**
		 * @brief Returns all unique edges of this graph without their weights.
		 *
		 * See method @ref get_unique_edges(std::vector<edge>& edges)const for details.
		 */
		void edges(std::vector<edge>& all_edges) const;

		/**
		 * @brief Converts this graph into an unweighted graph.
		 *
		 * If the graph is directed the result is a pointer to an
		 * unweighted graph object (@ref uxgraph) instanciated with
		 * an undweighted directed graph (@ref udgraph).
		 *
		 * If the graph is undirected the result is a pointer to an
		 * unweighted graph object (@ref uxgraph) instanciated with
		 * an undweighted undirected graph (@ref uugraph).
		 *
		 * The graph returned keeps the edges and removes the weights.
		 *
		 * @return A pointer to a @ref uxgraph object.
		 */
		virtual uxgraph* to_unweighted() const = 0;
};

} // -- namespace lgraph

#include <lgraph/data_structures/wxgraph.cpp>
