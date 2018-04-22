#pragma once

/// C++ includes
#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

/// Custom includes
#include "data_structures/xxgraph.hpp"
#include "utils/logger.hpp"

namespace lgraph {
using namespace utils;

namespace traversal {

	/*
	Generic Breadth-First search algorithm:

	The usual scheme of this algorithm for traversing through a graph from
	a source node to a target node is as follows:

	BFS(graph, source, target):
	1.	vis = {false}	// set of |V(graph)| bits set to false
	2.	Q = empty		// empty queue
	3.	while Q is not empty do
	4.		v = Q.front
	5.		remove Q's front
	6.		if v == target then terminate
	7.		else do
	8.			Nv = neighbourhood of v
	9.			for each w in Nv do
	10.				if w not visited before then
	11.					push w into Q
	12.					mark w as visited in vis
	13.				endif
	14.			endfor
	15.		endif
	16.	endwhile

	This algorithm is implemented in a way generic enough so that function:
	- proces_current() is called before the 'if' in line 6 (and after removing
		the current node from the queue in line 5) used to perform some operation
		on the current node of the traversal.
		This function admits 3 parameters:
			* the graph being traversed
			* the node at the front of the queue ('v' in the pseudocode, line 4)
			* the set of visited nodes, as a vector<bool>
	- terminate() is used as a termination condition in line 6.
		This function admits 3 parameters:
			* the graph being traversed
			* the node at the front of the queue ('v' in the pseudocode, line 4)
			* the set of visited nodes, as a vector<bool>
	- process_neighbour() is called between the 'for' loop in line 9 and the
		'if' in line 10, used to perform some operation on each of the neighbours.
		This function admits 4 parameters:
			* the graph being traversed
			* the node at the front of the queue ('v' in the pseudocode, line 4)
			* the neighbour of 'v' being processed ('w' in the pseudocode, line 9)
			* the set of visited nodes, as a vector<bool>
	*/

	/* parameters:
	 *	- input graph,
	 *	- node at the front of the queue,
	 *	- set of visited nodes
	 */
	template<class T = size_t>
	using bfs_terminate = function<bool (const xxgraph<T> *, node, const vector<bool>&)>;

	/* parameters:
	 *	- input graph,
	 *	- node at the front of the queue,
	 *	- set of visited nodes
	 */
	template<class T = size_t>
	using bfs_process_current = function<void (const xxgraph<T> *, node, const vector<bool>&)>;

	/* parameters:
	 *	- input graph,
	 *	- node at the front of the queue,
	 *	- neighbour of node at the top of the queue,
	 *	- set of visited nodes
	 */
	template<class T = size_t>
	using bfs_process_neighbour = function<void (const xxgraph<T> *, node, node, const vector<bool>&)>;

	template<class T>
	void BFS
	(
		const xxgraph<T> *G,
		node source,
		bfs_terminate<T> term =					[](const xxgraph<T> *, node, const vector<bool>&) -> bool { return false; },
		bfs_process_current<T> proc_curr =		[](const xxgraph<T> *, node, const vector<bool>&) -> void {},
		bfs_process_neighbour<T> proc_neig =	[](const xxgraph<T> *, node, node, const vector<bool>&) -> void {}
	);

} // -- namespace traversal
} // -- namespace lgraph

#include "bfs.cpp"
