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
#include "data_structures/boolean_path.hpp"
#include "data_structures/node_path.hpp"
#include "utils/logger.hpp"
#include "bfs.hpp"
#include "dfs.hpp"
#include "dijkstra.hpp"

namespace lgraph {
using namespace utils;

namespace traversal {

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

	/* Functions that compute the distances:
	 * - node-to-node	(Dijkstra)
	 * - node-to-all	(Dijkstra)
	 * - all-to-all		(Floyd-Warshall)
	 *
	 * The distance from one vertex to another is defined as the number
	 * of edges in the shortest path between the two.
	 */

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
} // -- namespace lgraph

// assume weighted graphs
#include "xwpaths.cpp"
#include "xwdistances.cpp"
#include "xwpaths_boolean.cpp"
