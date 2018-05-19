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
#include "data_structures/xxgraph.hpp"
#include "utils/logger.hpp"

namespace lgraph {
using namespace utils;

namespace traversal {

/**
* @brief Grouping of the DFS-related functions
*
* Contains a generic DFS algorithm and several
* functions used to guide it.
*/
namespace dfs {

	/**
	 * @brief Terminating function
	 *
	 * Returns true if the @ref DFS algorithm should terminate. For more details on
	 * when it is called see @ref DFS.
	 *
	 * @param G The graph being traversed
	 * @param u The node at the top of the stack of the algorithm
	 * @param vis The set of visited nodes
	 */
	template<class T = size_t>
	using dfs_terminate = function<bool (const xxgraph<T> *G, node u, const vector<bool>& vis)>;

	/**
	 * @brief Node processing function
	 *
	 * Processes the current node visited. For more details on
	 * when it is called see @ref DFS.
	 *
	 * @param G The graph being traversed
	 * @param u The node at the top of the stack of the algorithm
	 * @param vis The set of visited nodes
	 */
	template<class T = size_t>
	using dfs_process_current = function<void (const xxgraph<T> *G, node u, const vector<bool>& vis)>;

	/**
	 * @brief Node processing function
	 *
	 * Processes the next visited node. For more details on
	 * when it is called see @ref DFS.
	 *
	 * @param G The graph being traversed
	 * @param u The node at the top of the stack of the algorithm
	 * @param v The node neighbour of @e u visited by the algorithm
	 * @param vis The set of visited nodes
	 */
	template<class T = size_t>
	using dfs_process_neighbour = function<void (const xxgraph<T> *G, node u, node v, const vector<bool>& vis)>;

	/**
	 * @brief Generic Depth-First search algorithm
	 *
	 * The usual procedure of this algorithm for traversing through a graph from
	 * a source node to a target node is as follows:
	 *
	 * <pre>
	 * DFS(graph, source, target):
	 *	 1.	vis = {false}	// set of |V(graph)| bits set to false
	 *	 2.	S = empty		// empty stack
	 *	 3.	while S is not empty do
	 *	 4.		v = S.top
	 *	 5.		remove S's top
	 *	 6.		proc_curr(G,v,vis)
	 *	 7.		if terminate(G,v,vis) then terminate
	 *	 8.		else
	 *	 9.			Nv = neighbourhood of v
	 *	10.			for each w in Nv do
	 *	11.				proc_neigh(G,u,w,vis)
	 *	12.				if w not visited before then
	 *	13.					push w onto S
	 *	14.					mark w as visited in vis
	 *	15.				endif
	 *	16.			endfor
	 *	17.		endif
	 *	18.	endwhile
	 * </pre>
	 *
	 * @param G The graph being traversed
	 * @param source The node where the algorithm starts at
	 * @param term The terminating function. It is used as a termination condition in line 7.
	 * @param proc_curr The function to process the currently visited node.
	 *	It is called in line 6 used to perform some operation on the current node of the traversal.
	 * @param proc_neigh It is called in line 11 used to perform some operation on each of the
	 *	neighbours.
	 */
	template<class T>
	void DFS
	(
		const xxgraph<T> *G,
		node source,
		dfs_terminate<T> term =					[](const xxgraph<T> *, node, const vector<bool>&) -> bool { return false; },
		dfs_process_current<T> proc_curr =		[](const xxgraph<T> *, node, const vector<bool>&) -> void {},
		dfs_process_neighbour<T> proc_neig =	[](const xxgraph<T> *, node, node, const vector<bool>&) -> void {}
	);

} // -- namespace dfs
} // -- namespace traversal
} // -- namespace lgraph

#include "dfs.cpp"
