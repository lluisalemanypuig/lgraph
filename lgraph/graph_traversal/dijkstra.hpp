#pragma once

// C++ includes
#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// Custom includes
#include <lgraph/data_structures/wxgraph.hpp>
#include <lgraph/utils/logger.hpp>

namespace lgraph {
using namespace utils;

namespace traversal {

/**
* @brief Grouping of the Dijkstra's algorithm for path finding generic functions
*
* Contains a generic Dijkstra algorithm for shortest-path and several
* functions used to guide it.
*/
namespace dijkstra {

	/// A pair encoding the distance to a node, and that node
	template<class T>
	using djka_node = pair<T, node>;

	/**
	 * @brief Terminating function
	 *
	 * Returns true if the @ref Dijkstra algorithm should terminate.
	 * For more details on when it is called see @ref Dijkstra.
	 *
	 * @param G The graph being traversed
	 * @param u The node at the front of the queue of the algorithm and the distance
	 *	to it.
	 * @param vis The set of visited nodes
	 */
	template<class T = size_t>
	using djka_terminate = function<bool (const wxgraph<T> *G, const djka_node<T>& u, const vector<bool>& vis)>;

	/**
	 * @brief Node processing function
	 *
	 * Processes the current node visited. For more details on
	 * when it is called see @ref Dijkstra.
	 *
	 * @param G The graph being traversed
	 * @param u The node at the front of the queue of the algorithm and the distance
	 *	to it.
	 * @param vis The set of visited nodes
	 */
	template<class T = size_t>
	using djka_process_current = function<void (const wxgraph<T> *G, const djka_node<T>& u, const vector<bool>& vis)>;

	/**
	 * @brief Node processing function
	 *
	 * Processes the next visited node. For more details on
	 * when it is called see @ref Dijkstra.
	 *
	 * @param G The graph being traversed
	 * @param u The node at the front of the queue of the algorithm
	 * @param v The node neighbour of @e u visited by the algorithm
	 * @param w weight of edge (u,v)
	 * @param vis The set of visited nodes
	 *
	 * @return Returns true or false whether the next pair of (distance,node)
	 *	should be added or not
	 */
	template<class T = size_t>
	using djka_process_neighbour = function<bool (const wxgraph<T> *G, node u, node v, const T& w, const vector<bool>& vis)>;

	/**
	 * @brief Generic Dijkstra algorithm
	 *
	 * The procedure applied for this algorithm here
	 * for traversing through a graph from a source node to
	 * a target node is as follows:
	 *
	 * <pre>
	 * Dijkstra(graph, source, target):
	 *	 1.	vis = {false}	// set of |V(graph)| bits set to false
	 *	 2.	Q = empty		// empty priority queue of (distance,node)
	 *	 3.	while Q is not empty do
	 *	 4.		(wu,u) = Q.front
	 *	 5.		remove Q's front
	 *   6.		if u is not visited then
	 *	 7.			proc_curr(G,u,vis)
	 *	 8			if terminate(G,u,vis) then terminate
	 *	 9.			else
	 *	10.				Nu = neighbourhood of u
	 *	11.				for each v in Nu do
	 *	12.					wv := weight edge (u,v)
	 *	13.					add_next := proc_neigh(G, u,v, wv, vis)
	 *	14.					if add_next then
	 *	15.						push w into Q
	 *	16.					endif
	 *	17.				endfor
	 *	18.			endif
	 *	19.		endif
	 *	20.	endwhile
	 * </pre>
	 *
	 * @param G The graph being traversed
	 * @param source The node where the algorithm starts at
	 * @param term The terminating function. It is used as a termination condition in line 8.
	 * @param proc_curr The function to process the currently visited node.
	 *	It is called in line 7 used to perform some operation on the current node of the traversal.
	 * @param proc_neigh It is called between the 'for' loop in line 13 and the
	 *	used to perform some operation on each of the neighbours.
	 */
	template<class T>
	void Dijkstra
	(
		const wxgraph<T> *G,
		node source,
		djka_terminate<T> term =				[](const wxgraph<T> *, const djka_node<T>&, const vector<bool>&) -> bool { return false; },
		djka_process_current<T> proc_curr =		[](const wxgraph<T> *, const djka_node<T>&, const vector<bool>&) -> void {},
		djka_process_neighbour<T> proc_neigh =	[](const wxgraph<T> *, node, node, const T&, const vector<bool>&) -> bool { return true; }
	);

} // -- namespace dijkstra
} // -- namespace traversal
} // -- namespace lgraph

#include <lgraph/graph_traversal/dijkstra.cpp>
