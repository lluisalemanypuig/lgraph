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
#include "data_structures/uugraph.hpp"
#include "data_structures/boolean_path.hpp"
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

	/* parameters:
	 *	- input graph,
	 *	- node at the front of the stack,
	 *	- set of visited nodes
	 */
	template<class T = size_t>
	using dfs_terminate = function<bool (const xxgraph<T> *, node, const vector<bool>&)>;

	/* parameters:
	 *	- input graph,
	 *	- node at the front of the queue,
	 *	- set of visited nodes
	 */
	template<class T = size_t>
	using dfs_process_current = function<void (const xxgraph<T> *, node, const vector<bool>&)>;

	/* parameters:
	 *	- input graph,
	 *	- node at the front of the queue,
	 *	- neighbour of node at the top of the stack,
	 *	- set of visited nodes
	 */
	template<class T = size_t>
	using dfs_process_neighbour = function<void (const xxgraph<T> *, node, node, const vector<bool>&)>;

	template<class T>
	void DFS
	(
		const xxgraph<T> *G,
		node source,
		dfs_terminate<T> term =					[](const xxgraph<T> *, node, const vector<bool>&) -> bool { return false; },
		dfs_process_current<T> proc_curr =		[](const xxgraph<T> *, node, const vector<bool>&) -> void {},
		dfs_process_neighbour<T> proc_neig =	[](const xxgraph<T> *, node, node, const vector<bool>&) -> void {}
	);

	template<class T>
	using djka_dist_node = pair<T, node>;

	/* parameters:
	 *	- input graph,
	 *	- first: shortest distance to that node,
	 *	  second: node at the front of the priority queue
	 *	- set of visited nodes
	 */
	template<class T = size_t>
	using djka_terminate = function<bool (const xxgraph<T> *, const djka_dist_node<T>&, const vector<bool>&)>;

	/* parameters:
	 *	- input graph,
	 *	- first: shortest distance to that node,
	 *	  second: node at the front of the priority queue
	 *	- set of visited nodes
	 */
	template<class T = size_t>
	using djka_process_current = function<void (const xxgraph<T> *, const djka_dist_node<T>&, const vector<bool>&)>;

	/* parameters:
	 *	- input graph,
	 *	- node at the front of the priority queue (u),
	 *	- neighbour of node at the top of the priority queue (v),
	 *	- weight of edge (u,v)
	 *	- set of visited nodes
	 *
	 * Returns true or false n whether the next pair should be added or not
	 */
	template<class T = size_t>
	using djka_process_neighbour = function<bool (const xxgraph<T> *, node, node, const T&, const vector<bool>&)>;

	template<class T>
	void Dijkstra
	(
		const xxgraph<T> *G,
		node source,
		djka_terminate<T> term =				[](const xxgraph<T> *, const djka_dist_node<T>&, const vector<bool>&) -> bool { return false; },
		djka_process_current<T> proc_curr =		[](const xxgraph<T> *, const djka_dist_node<T>&, const vector<bool>&) -> void {},
		djka_process_neighbour<T> proc_neig =	[](const xxgraph<T> *, node, node, const T&, const vector<bool>&) -> bool { return true; }
	);

	/* Functions that compute the distances:
	 * - node-to-node	(Dijkstra)
	 * - node-to-all	(Dijkstra)
	 * - all-to-all		(Floyd-Warshall)
	 *
	 * The distance from one vertex to another is defined as the number
	 * of edges in the shortest path between the two.
	 */

	/// ----------------------------------------------------------------
	/// UNWEIGHTED FUNCTIONS (for directed/undirected unweighted graphs)
	/// ----------------------------------------------------------------

	/* Functions that compute the distances:
	 * - vertex-to-vertex	(BFS)
	 * - vertex-to-all		(BFS)
	 * - all-to-all			(Floyd-Warshall)
	 *
	 * The distance from one vertex to another is defined as the number
	 * of edges in the shortest path between the two.
	 */

	/// NODE-NODE

	_new_ xudistance(const xxgraph<_new_> *G, node source, node target);
	_new_ xudistance(const xxgraph<_new_> *G, node source, node target, size_t& n_paths);

	/// NODE-ALL

	void xudistance(const xxgraph<_new_> *G, node source, vector<_new_>& xudistances);
	void xudistance(const xxgraph<_new_> *G, node source, vector<_new_>& xudistances, vector<size_t>& n_paths);

	/// ALL-ALL

	void xudistances(const xxgraph<_new_> *G, vector<vector<_new_> >& ds);
	void xudistances(const xxgraph<_new_> *G, vector<vector<_new_> >& ds, vector<vector<size_t> >& n_paths);

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

	/// NODE-NODE

	// a shortest path from a node to another node
	void xupath(const xxgraph<_new_> *G, node source, node target, node_path<_new_>& p);
	void xupath(const xxgraph<_new_> *G, node source, node target, boolean_path<_new_>& p);

	// all shortest paths from a node to another node
	void xupaths(const xxgraph<_new_> *G, node source, node target, node_path_set<_new_>& ps);
	void xupaths(const xxgraph<_new_> *G, node source, node target, boolean_path_set<_new_>& ps);

	/// NODE-ALL

	// a shortest path from all nodes to a single node
	void xupath(const xxgraph<_new_> *G, node source, vector<node_path<_new_> >& ps);
	void xupath(const xxgraph<_new_> *G, node source, vector<boolean_path<_new_> >& ps);

	// all shortest paths from all nodes to a single node
	void xupaths(const xxgraph<_new_> *G, node source, vector<node_path_set<_new_> >& ps);
	void xupaths(const xxgraph<_new_> *G, node source, vector<boolean_path_set<_new_> >& ps);

	/// ALL-ALL

	// a shortest path from all nodes to all other nodes
	void xupath(const xxgraph<_new_> *G, vector<vector<node_path<_new_> > >& ps);
	void xupath(const xxgraph<_new_> *G, vector<vector<boolean_path<_new_> > >& ps);

	// all shortest paths from all nodes to all other nodes
	void xupaths(const xxgraph<_new_> *G, vector<vector<node_path_set<_new_> > >& ps);
	void xupaths(const xxgraph<_new_> *G, vector<vector<boolean_path_set<_new_> > >& ps);

	/// ------------------------------------------------------------
	/// WEIGHTED FUNCTIONS (for directed/undirected weighted graphs)
	/// ------------------------------------------------------------

	/// NODE-NODE

	/* (1): distance from source to target.
	 * (2): idem, and the number of shortest paths.
	*/

	template<class T>
	T xwdistance(const xxgraph<T> *G, node source, node target);
	template<class T>
	T xwdistance(const xxgraph<T> *G, node source, node target, size_t& n_paths);

	/// NODE-ALL

	/* (1): distance from source to all other nodes in the graph.
	 * (2): idem, and the number of shortest paths between them.
	*/

	template<class T>
	void xwdistance(const xxgraph<T> *G, node source, vector<T>& xwdistances);
	template<class T>
	void xwdistance(const xxgraph<T> *G, node source, vector<T>& xwdistances, vector<size_t>& n_paths);

	/// ALL-ALL

	/* (1): distance from all nodes in the graph to all other nodes in the graph.
	 * (2): idem, and the number of shortest paths between them.
	*/

	template<class T>
	void xwdistances(const xxgraph<T> *G, vector<vector<T> >& ds);
	template<class T>
	void xwdistances(const xxgraph<T> *G, vector<vector<T> >& ds, vector<vector<size_t> >& n_paths);

	/* Functions that compute the paths:
	 * - node-to-node	(Dijkstra)
	 * - node-to-all	(Dijkstra)
	 * - all-to-all		(Floyd-Warshall modified)
	 *
	 * A path from vertex 'u' to vertex 'v' is defined as the shortest list of vertices
	 * (u, ..., v) where '...' is a list of vertices v1, v2, ... , vn  such that v1 is a
	 * neighbour of u, v2 is a neighbour of v1, ..., vn is a neighbout of vn-1 and v is
	 * a neighbour of vn. n may be 0.
	 *
	 * Its length is the number of edges in the path. Also, the number of vertices in it minus 1.
	 */

	/// NODE-NODE

	// a shortest path from a node to another node
	template<class T>
	void xwpath(const xxgraph<T> *G, node source, node target, node_path<T>& p);
	template<class T>
	void xwpath(const xxgraph<T> *G, node source, node target, boolean_path<T>& p);

	// all shortest paths from a node to another node
	template<class T>
	void xwpaths(const xxgraph<T> *G, node source, node target, node_path_set<T>& ps);
	template<class T>
	void xwpaths(const xxgraph<T> *G, node source, node target, boolean_path_set<T>& ps);

	/// NODE-ALL

	// a shortest path from all nodes to a single node
	template<class T>
	void xwpath(const xxgraph<T> *G, node source, vector<node_path<T> >& ps);
	template<class T>
	void xwpath(const xxgraph<T> *G, node source, vector<boolean_path<T> >& ps);

	// all shortest paths from all nodes to a single node
	template<class T>
	void xwpaths(const xxgraph<T> *G, node source, vector<node_path_set<T> >& ps);
	template<class T>
	void xwpaths(const xxgraph<T> *G, node source, vector<boolean_path_set<T> >& ps);

	/// ALL-ALL

	// a shortest path from all nodes to all other nodes
	template<class T>
	void xwpath(const xxgraph<T> *G, vector<vector<node_path<T> > >& ps);
	template<class T>
	void xwpath(const xxgraph<T> *G, vector<vector<boolean_path<T> > >& ps);

	// all shortest paths from all nodes to all other nodes
	template<class T>
	void xwpaths(const xxgraph<T> *G, vector<vector<node_path_set<T> > >& ps);
	template<class T>
	void xwpaths(const xxgraph<T> *G, vector<vector<boolean_path_set<T> > >& ps);

} // -- namespace traversal
} // -- namespace dsa

#include "dfs.cpp"
#include "bfs.cpp"
#include "dijkstra.cpp"

// assume weighted graphs
#include "xwpaths.cpp"
#include "xwdistances.cpp"
#include "xwpaths_boolean.cpp"
