#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

// Custom includes
#include "xxgraph.hpp"
#include "utils/definitions.hpp"
#include "utils/static_bitset.hpp"
#include "utils/logger.hpp"
#include "node_path.hpp"

namespace lgraph {
namespace utils {

/**
 * @brief A path through a graph seen as a list of Boolean values.
 *
 * The i-th position of this path is 1 if, and only if, the i-th node of the
 * graph is in the path. This is intended to be used ONLY for shortest paths.
 * Therefore, any boolean_path can be converted into a node_path under the
 * following condition:
 *	if p(u) is the position of node 'u' in the node path then:
 *		+ if u has only one neighbour 'v' then either p(v) < p(u) or p(u) < p(v)
 *		+ if u has two neighbours 'v', 'w' then either p(v) < p(u) < p(w) or
 *			p(w) < p(u) < p(v)
 * Any other boolean path not following the previous two conventions is not
 * guaranteed to be able to be converted into an object of type 'node_path'.
 * The template parameter type is the type used to store this path's length
 * (see @ref path_length).
 *
 * The type used for the length must support comparisons and the C++'s output
 * operator <<.
 */
template<class T = _new_>
class boolean_path {
	private:
		/**
		 * @brief The list of nodes as Boolean values.
		 *
		 * @ref nodes_in_path[i] = true if, and only if, i-th node
		 * of the graph is in the path
		 */
		static_bitset nodes_in_path;

		/// Number of nodes in the path, i.e., the amount of values set to true.
		size_t n_nodes;

		/**
		 * @brief The total weight of this path.
		 *
		 * If 'p' is the path as a list of edges, then 'path_length' equals the
		 * sum of weights of all edges in 'p'.
		 */
		T path_length;

	public:
		boolean_path();
		~boolean_path();

		/**
		 * @brief Initialises the path to an empty path within a graph of
		 * @e n nodes.
		 *
		 * There is no need for this path to be 'uninitialised'.
		 */
		void init(size_t n);

		/**
		 * @brief Initialises the path to a path within a graph of @e n nodes
		 * with the nodes in @e vp.
		 *
		 * @param n The number of nodes of the graph this path goes through.
		 * @param vp The list of nodes that makes the path within the graph. All
		 * indices of this path must be lower than @e n.
		 */
		void init(size_t n, const node_path<T>& vp);

		/**
		 * @brief Clears the path.
		 *
		 * One of the two methods @ref init(size_t) or @ref init(size_t,const node_path<T>&)
		 * will have to be called again to be able to use it again. However, the
		 * destructor of this class frees the memory automatically.
		 */
		void clear();

		/**
		 * @brief Adds a node to the path.
		 *
		 * The corresponding position of @ref nodes_in_path is set to true.
		 * @param u The node's index, between 0 and @ref n_nodes - 1
		*/
		void add_node(node u);

		/**
		 * @brief Accumulates to the current length of the the path the value l.
		 * @param l The value to be accumulated to @ref path_length
		 */
		void add_length(const T& l);

		/**
		 * @brief Sets the current length of the the path the value l.
		 * @param l The value that will replace the current value of
		 *		@ref path_length
		 */
		void set_length(const T& l);

		/**
		 * @brief Adds to this paths all nodes from bp
		 * @param bp The boolean path that will be concatenated to this.
		 */
		void concatenate(const boolean_path<T>& bp);

		/**
		 * @brief Outputs this path on a \ref ostream object.
		 *
		 * The format is this path as a string (see \ref to_string())
		 * followed by '->' and this path's length.
		 */
		inline friend
		ostream& operator<< (ostream& os, const boolean_path<T>& bp) {
			os << bp.to_string() << " -> " << bp.path_length;
			return os;
		}

		/**
		 * @brief Check if the i-th node is in the path
		 *
		 * @param i The node's index.
		 * @return Returns true if, and only if, @ref nodes_in_path[@e i] is set
		 * to true.
		 *
		 * @pre The node index @e i must satisfy @e i < @ref n_nodes
		 */
		bool operator[] (node i) const;

		/**
		 * @brief Overrides this boolean path's information with @e bp.
		 *
		 * This boolean path's memory is first freed and reallocated to hold
		 * the contents in @e bp.
		 *
		 * @param bp The new boolean path.
		 */
		boolean_path& operator= (const boolean_path<T>& bp);

		/**
		 * @brief Returns the number of nodes in the path.
		 *
		 * Returns the value @ref n_nodes
		 */
		size_t size() const;

		/**
		 * @brief Returns this path's length.
		 *
		 * Returns the sum of the distances between the nodes in the path,
		 * that is, the value @ref path_length
		 */
		T get_length() const;

		/**
		 * @brief Returns the maximum number of nodes that could be in the path.
		 *
		 * Basically, returns the size used to initialise it.
		 */
		size_t potential_length() const;

		/**
		 * @brief Looks for the next node in this path taking as a reference the
		 * @e previous and @e current nodes.
		 *
		 * Since a node could have more than one of its neighbour in the path,
		 * the node that it retrieves is the closest to the @e current node, that
		 * is different from the @e previous node.
		 *
		 * @param[in]  G		The graph this path goes through.
		 * @param[in]  previous	The previous node in the path. To retrieve the
		 * second node in the path, set this parameter to -1.
		 * @param[in]  current	The current node in the path.
		 * @param[out] next		The value of the next node in the path, if it exists.
		 * @return Returns true if there actually exists a "next" node in the path.
		 */
		bool closest_next(const xxgraph<T> *G, node previous, node current, node& next) const;

		/**
		 * @brief Looks for the next node in this path taking as a reference the
		 * nodes previously visited and the @e current node.
		 *
		 * Since a node could have more than one of its neighbour in the path,
		 * the node that it retrieves is the closest to the @e current node, that
		 * is different from the previously visited nodes (marked in @e previous).
		 * This function is meant to be used when converting a boolean_path to a
		 * node_path.
		 *
		 * @param[in]  G		The graph this path goes through.
		 * @param[in]  previous	The nodes previously visited. To retrieve the
		 * second node in the path, all the values must be set to false. Its size
		 * must be equal to this path's potential length (see @ref potential_length()).
		 * @param[in]  current	The current node in the path.
		 * @param[out] next		The value of the next node in the path, if it exists.
		 * @return Returns true if there actually exists a "next" node in the path.
		 */
		bool closest_next
		(const xxgraph<T> *G, const vector<bool>& previous, node current, node& next) const;

		/**
		 * @brief Converts this boolean_path to an object of type node_path.
		 *
		 * The conversion is done assuming that the boolean_path starts at node
		 * @e s. The result is an object that stores the path as a list of nodes.
		 *
		 * @param G The graph this path goes through.
		 * @param s The node where this path starts at.
		 * @return Returns a node_path object equivalent to this boolean path.
		 */
		node_path<T> to_node_path(const xxgraph<T> *G, node s) const;

		/**
		 * @brief Converts this boolean_path to an object of type node_path.
		 *
		 * The conversion is done assuming that the boolean_path starts at node
		 * @e s. The result is an object that stores the path as a list of nodes.
		 *
		 * @param[in]	G	The graph this path goes through.
		 * @param[in]	s	The node where this path starts at.
		 * @param[out]	np	The path seen as a list of nodes.
		 */
		void to_node_path(const xxgraph<T> *G, node s, node_path<T>& np) const;

		/**
		 * @brief Formats this path into a string with a 'pretty' format.
		 *
		 * @returns Returns this path formatted into a string that has two
		 * parts separated with an 'endl' character. The first is the header
		 * indicating the index of the node. The second is either a 0 or a 1
		 * telling whether the corresponding index is in the path or not.
		 */
		string pretty_string() const;

		/**
		 * @brief Formats this path into a string with a 'pretty' format.
		 *
		 * @param[out] s Stores this path formatted into a string that has two
		 * parts separated with an 'endl' character. The first is the header
		 * indicating the index of the node. The second is either a 0 or a 1
		 * telling whether the corresponding index is in the path or not.
		 */
		void pretty_string(string& s) const;

		/**
		 * @brief Formats this path into a string with a plain format.
		 *
		 * @returns Returns this path as a list of 0's and 1's. The i-th
		 * digit is a 1 if, and only if, the i-th vertex is in the path.
		 */
		string to_string() const;

		/**
		 * @brief Formats this path into a string with a plain format.
		 *
		 * @param[out] s Stores this path as a list of 0's and 1's. The i-th
		 * digit is a 1 if, and only if, the i-th vertex is in the path.
		 */
		void to_string(string& s) const;
};

//! Template for a list of boolean_path objects.
template<class T = size_t>
using boolean_path_set = vector<boolean_path<T> >;

/**
 * @brief Shortcut to convert all node_path objects in a list to a list
 * of boolean_path objects.
 *
 * @param[in]	nps	The list of node_path objects to convert.
 * @param[in]	N	The amount of nodes that the graph each node_path object traverses has.
 * @param[out]	bps	A list with as many boolean_paths as node_paths are in @e bps.
 *					The boolean path in @e bps[i]
 */
template<class T>
void from_nps_to_bps(const node_path_set<T>& nps, size_t N, boolean_path_set<T>& bps);

} // -- namespace utils
} // -- namespace lgraph

#include "boolean_path.cpp"
