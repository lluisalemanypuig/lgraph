#pragma once

// C++ includes
#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>
#include <queue>
#include <stack>

// lgraph includes
#include <lgraph/data_structures/uxgraph.hpp>
#include <lgraph/utils/logger.hpp>

namespace lgraph {
namespace traversal {

/**
* Contains a generic BFS algorithm that uses three
* different functions that guide it.
*/
namespace bfs {

/**
 * @brief Terminating function.
 *
 * Returns true if the @ref BFS algorithm should terminate.
 *
 * For more details on when this function is called see @ref BFS.
 *
 * @param G The graph being traversed.
 * @param u The node at the front of the queue of the algorithm.
 * @param vis The set of visited nodes.
 */
typedef std::function<
	bool (const uxgraph *G, node u, const std::vector<bool>& vis)
> bfs_terminate;

/**
 * @brief Node processing function.
 *
 * Processes the current node visited.
 *
 * For more details on when this function is called see @ref BFS.
 *
 * @param G The graph being traversed.
 * @param u The node at the front of the queue of the algorithm.
 * @param vis The set of visited nodes.
 */
typedef std::function<
	void (const uxgraph *G, node u, const std::vector<bool>& vis)
> bfs_process_current;

/**
 * @brief Node processing function.
 *
 * Processes the next visited node.
 *
 * For more details on when this function is called see @ref BFS.
 *
 * @param G The graph being traversed.
 * @param u The node at the front of the queue of the algorithm.
 * @param v The node neighbour of @e u visited by the algorithm.
 * @param vis The set of visited nodes.
 */
typedef std::function<
	void (const uxgraph *G, node u, node v, const std::vector<bool>& vis)
> bfs_process_neighbour;

/**
 * @brief Generic Breadth-First search algorithm.
 *
 * The usual procedure of this algorithm for traversing through a graph from
 * a source node to a target node is as follows:
 *
 * <pre>
 * BFS(graph, source, target):
 *	 1.	vis = {false}	// set of |V(graph)| bits set to false
 *	 2.	Q = empty		// empty queue
 *	 3.	while Q is not empty do
 *	 4.		v = Q.front
 *	 5.		remove Q's front
 *	 6.		proc_curr(G,v,vis)
 *	 7.		if terminate(G,v,vis) then terminate
 *	 8.		else
 *	 9.			Nv = neighbourhood of v
 *	10.			for each w in Nv do
 *	11.				proc_neigh(G,u,w,vis)
 *	12.				if w not visited before then
 *	13.					push w into Q
 *	14.					mark w as visited in vis
 *	15.				endif
 *	16.			endfor
 *	17.		endif
 *	18.	endwhile
 * </pre>
 *
 * @param G The graph being traversed.
 * @param source The node where the algorithm starts at.
 * @param term The terminating function. It is used as a termination
 * condition in line 7..
 * @param proc_curr The function to process the currently visited node.
 * It is called in line 6 used to perform some operation on the current
 * node of the traversal.
 * @param proc_neigh It is called in line 11 used to perform some
 * operation on each of the neighbours.
 */
void BFS
(
	const uxgraph *G,
	node source,
	bfs_terminate term =
		[](const uxgraph *, node, const std::vector<bool>&)
		-> bool { return false; },
	bfs_process_current proc_curr =
		[](const uxgraph *, node, const std::vector<bool>&)
		-> void {},
	bfs_process_neighbour proc_neigh =
		[](const uxgraph *, node, node, const std::vector<bool>&)
		-> void {}
);

} // -- namespace bfs
} // -- namespace traversal
} // -- namespace lgraph

