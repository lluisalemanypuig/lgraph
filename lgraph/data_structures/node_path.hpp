#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <vector>

// lgraph includes
#include <lgraph/data_structures/xxgraph.hpp>
#include <lgraph/utils/definitions.hpp>

namespace lgraph {

/**
 * @brief A path through a grpah seen as a list of nodes.
 *
 * It simply stores a list of nodes in which every pair of consecutive nodes
 * form an edge in a graph. If all consecutive pairs of nodes make a path in
 * a graph @e G then this object stores a path within @e G.
 *
 * It also stores the length of the path, that is, the sum of all the edges
 * in this path.
 *
 * @param T The type used for the length. It must support comparisons and the
 * C++'s output operator <<.
 */
template<class T = _new_>
class node_path {
	private:
		/// The list of nodes of this path.
		std::vector<node> nodes;

		/**
		 * @brief The total weight of this path.
		 *
		 * If 'p' is the path as a list of edges, then 'path_length' equals the
		 * sum of weights of all edges in 'p'.
		 */
		T path_length;

	public:
		/// Empty constructor.
		node_path();
		/**
		 * @brief Initialise a path starting at node @e n.
		 * @param n The first node of this path.
		 * @pre @e n >= 0
		 */
		node_path(node n); // start path at node 'n'
		~node_path();

		/**
		 * @brief Empties this path.
		 *
		 * Frees the memory occupied by the currently existing nodes.
		 * Sets @ref path_length to 0.
		 */
		void empty();

		/**
		 * @brief Outputs this path on a @e ostream object.
		 *
		 * The format is a space-separated list of indices (one for each node)
		 * followed by '->' and this path's length.
		 */
		inline friend
		std::ostream& operator<< (std::ostream& os, const node_path<T>& np) {
			if (np.size() > 0) {
				os << np.to_string() << " (" << np.path_length << ")";
			}
			return os;
		}

		/**
		 * @brief Acces the @e i-th node of this path.
		 * @param i Index of the list.
		 * @return A copy of the node at the i-th position.
		 * @pre 0 <= @e i < @e n with @e n the amount of nodes in this path.
		 */
		node operator[] (size_t i) const;

		/**
		 * @brief Acces the @e i-th node of this path.
		 * @param i Index of the list.
		 * @return A reference to the node at the i-th position.
		 * @pre 0 <= @e i < @e n with @e n the amount of nodes in this path.
		 */
		node& operator[] (size_t i);

		/// Compares two nodes using only their length.
		bool operator< (const node_path<T>& p) const;
		/// Compares two nodes using only their length.
		bool operator> (const node_path<T>& p) const;

		/// Assigns the contents of @e np to this path.
		node_path<T>& operator= (const node_path<T>& np);

		/**
		 * @brief Concatenates the two paths.
		 *
		 * Adds at the end of this path all nodes in @e p except for the first.
		 * The length of @e p will be accumulated to this path's length.
		 *
		 * @param p The path to be appended to this.
		 * @pre This path's last node and the first node of p must be the same.
		 */
		void concatenate(const node_path& p);

		/**
		 * @brief Adds a node to the path.
		 *
		 * The new node is added at the back of @ref nodes.
		 *
		 * @param u The node's index.
		 * @pre u >= 0.
		 * @post The length remains unchanged.
		*/
		void add_node(node u);

		/**
		 * @brief Accumulates to the current length of the the path the value l.
		 * @param l The value to be accumulated to @ref path_length.
		 */
		void add_length(const T& l);

		/**
		 * @brief Sets the current length of the the path the value l.
		 * @param l The value that will replace the current value of
		 *		@ref path_length.
		 */
		void set_length(const T& l);

		/// Reverses the order of the nodes of this path.
		void reverse();

		/**
		 * @brief Deletes the last node of this path.
		 * @post The length remains unchanged.
		 */
		void delete_last();

		/**
		 * @brief Returns the number of nodes in this path.
		 * @return Returns the size of @ref nodes.
		 */
		size_t size() const;

		/**
		 * @brief Returns the length of this path.
		 * @return Returns the value @ref path_length.
		 */
		T get_length() const;

		/// Return the last node of this path.
		node last_node() const;

		/// Returns a constant reference to the list of nodes.
		const std::vector<node>& get_nodes() const;

		/**
		 * @brief Formats this path into a string with a plain format.
		 *
		 * @returns Returns this path as a list of indexes, each representing
		 * a node.
		 */
		std::string to_string() const;

		/**
		 * @brief Formats this path into a string with a plain format.
		 *
		 * @param[out] s Stores this path as a list of indexes, each representing
		 * a node.
		 */
		void to_string(std::string& s) const;
};

/// Template for a list of node_path objects.
template<class T = _new_>
using node_path_set = std::vector<node_path<T> >;

} // -- namespace lgraph

#include <lgraph/data_structures/node_path.cpp>
