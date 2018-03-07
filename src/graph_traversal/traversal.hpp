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
#include "data_structures/graph.hpp"
#include "data_structures/graph_path.hpp"
#include "utils/logger.hpp"

namespace dsa {
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

	Find examples on how to use this function in the implementation of methods:
	- size_t distance(const graph& G, node source, node target);
	- void distance(const graph& G, node source, vector<size_t>& distances);
	*/

	typedef function<bool (const graph&, node,       const vector<bool>&)> terminate;
	typedef function<void (const graph&, node,       const vector<bool>&)> process_current;
	typedef function<void (const graph&, node, node, const vector<bool>&)> process_neighbour;

	void BFS
	(
		const graph& G,
		node source,
		terminate terminate					= [](const graph&, node, const vector<bool>&) -> bool { return false; },
		process_current process_current		= [](const graph&, node, const vector<bool>&) -> void {},
		process_neighbour process_neighbour	= [](const graph&, node, node, const vector<bool>&) -> void {}
	);

	void DFS
	(
		const graph& G,
		node source,
		terminate terminate					= [](const graph&, node, const vector<bool>&) -> bool { return false; },
		process_current process_current		= [](const graph&, node, const vector<bool>&) -> void {},
		process_neighbour process_neighbour	= [](const graph&, node, node, const vector<bool>&) -> void {}
	);

	/* Functions that compute the distances:
	 * - vertex-to-vertex	(BFS)
	 * - vertex-to-all		(BFS)
	 * - all-to-all			(Floyd-Warshall)
	 *
	 * The distance from one vertex to another is defined as the number
	 * of edges in the shortest path between the two.
	 */

	/// VERTEX-VERTEX

	size_t distance(const graph& G, node source, node target);
	size_t distance(const graph& G, node source, node target, size_t& n_paths);

	/// VERTEX-ALL

	void distance(const graph& G, node source, vector<size_t>& distances);
	void distance(const graph& G, node source, vector<size_t>& distances, vector<size_t>& n_paths);

	/// ALL-ALL

	void distances(const graph& G, vector<vector<size_t> >& ds);
	void distances(const graph& G, vector<vector<size_t> >& ds, vector<vector<size_t> >& n_paths);

	/* Functions that compute the paths:
	 * - vertex-to-vertex	(BFS)
	 * - vertex-to-all		(BFS)
	 * - all-to-all			(Floyd-Warshall modified)
	 *
	 * A path from vertex 'u' to vertex 'v' is defined as the shortest list of vertices
	 * (u, ..., v) where '...' is a list of vertices v1, v2, ... , vn  such that v1 is a
	 * neighbour of u, v2 is a neighbour of v1, ..., vn is a neighbout of vn-1 and v is
	 * a neighbour of vn. n may be 0.
	 *
	 * Its length is the number of edges in the path. Also, the number of vertices in it minus 1.
	 */

	/// VERTEX-VERTEX

	void path(const graph& G, node source, node target, node_path& p);
	void path(const graph& G, node source, node target, node_path_set& ps);
	void path(const graph& G, node source, node target, boolean_path& p);
	void path(const graph& G, node source, node target, boolean_path_set& ps);

	/// VERTEX-ALL

	void path(const graph& G, node source, vector<node_path>& ps);
	void path(const graph& G, node source, vector<node_path_set>& ps);
	void path(const graph& G, node source, vector<boolean_path>& ps);
	void path(const graph& G, node source, vector<boolean_path_set>& ps);

	/// ALL-ALL

	void paths(const graph& G, vector<vector<node_path> >& ps);
	void paths(const graph& G, vector<vector<node_path_set> >& ps);
	void paths(const graph& G, vector<vector<boolean_path> >& ps);
	void paths(const graph& G, vector<vector<boolean_path_set> >& ps);

} // -- namespace traversal
} // -- namespace dsa
