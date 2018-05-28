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
#include <lgraph/data_structures/boolean_path.hpp>
#include <lgraph/data_structures/node_path.hpp>
#include <lgraph/data_structures/xxgraph.hpp>
#include <lgraph/graph_traversal/dijkstra.hpp>
#include <lgraph/graph_traversal/bfs.hpp>
#include <lgraph/graph_traversal/dfs.hpp>
#include <lgraph/utils/logger.hpp>

namespace lgraph {
using namespace utils;

namespace traversal {
using namespace bfs;
using namespace dijkstra;

	// ----------------------------------------------------------------
	// UNWEIGHTED FUNCTIONS (for directed/undirected unweighted graphs)
	// ----------------------------------------------------------------

	/* DISTANCE COMPUTATION */

	// NODE-NODE

	/**
	 * @brief Directed/Undirected distance between two nodes
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @return The shortest distance between @e source and @e target
	 */
	_new_ xudistance(const xxgraph<_new_> *G, node source, node target);
	/**
	 * @brief Directed/Undirected distance between two nodes
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @param[out] n_paths The number of shortest paths between @e source and @e target
	 * @return The shortest distance between @e source and @e target
	 */
	_new_ xudistance(const xxgraph<_new_> *G, node source, node target, size_t& n_paths);

	// NODE-ALL

	/**
	 * @brief Directed/Undirected distance between a node to the rest of the graph's nodes
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @param[out] xudistances The i-th position contains the directed/undirected distance
	 * between the source node and the i-th node of the graph.
	 */
	void xudistance(const xxgraph<_new_> *G, node source, vector<_new_>& xudistances);
	/**
	 * @brief Directed/Undirected distance between a node to the rest of the graph's nodes
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @param[out] xudistances The i-th position contains the directed/undirected distance
	 * between the source node and the i-th node of the graph.
	 * @param[out] n_paths The i-th position contains the number of shortest paths between
	 * the source node and the i-th node.
	 */
	void xudistance(const xxgraph<_new_> *G, node source, vector<_new_>& xudistances, vector<size_t>& n_paths);

	// ALL-ALL

	/**
	 * @brief Directed/Undirected distance between all pairs of nodes
	 *
	 * Applies the Floyd-Warshall algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[out] ds The shortest directed/undirected distance between all pairs of nodes.
	 */
	void xudistances(const xxgraph<_new_> *G, vector<vector<_new_> >& ds);
	/**
	 * @brief Directed/Undirected distance between all pairs of nodes
	 *
	 * Applies the Floyd-Warshall algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[out] ds The shortest directed/undirected distance between all pairs of nodes.
	 * @param[out] n_paths The number of shortest paths between each pair of nodes.
	 */
	void xudistances(const xxgraph<_new_> *G, vector<vector<_new_> >& ds, vector<vector<size_t> >& n_paths);

	/* PATH FINDING IN UNWEIGHTED GRAPHS */

	// NODE-NODE

	/**
	 * @brief A directed/undirected path between two nodes
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @param[out] p A path between the nodes
	 */
	void xupath(const xxgraph<_new_> *G, node source, node target, node_path<_new_>& p);
	/**
	 * @brief A directed/undirected path between two nodes
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @param[out] p A path between the nodes
	 */
	void xupath(const xxgraph<_new_> *G, node source, node target, boolean_path<_new_>& p);

	/**
	 * @brief All directed/undirected path between two nodes
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @param[out] ps The paths between the nodes
	 */
	void xupaths(const xxgraph<_new_> *G, node source, node target, node_path_set<_new_>& ps);
	/**
	 * @brief All directed/undirected path between two nodes
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @param[out] ps The paths between the nodes
	 */
	void xupaths(const xxgraph<_new_> *G, node source, node target, boolean_path_set<_new_>& ps);

	// NODE-ALL

	/**
	 * @brief A directed/undirected path between a source node and any other node in the graph
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[out] ps A path between the nodes
	 */
	void xupath(const xxgraph<_new_> *G, node source, vector<node_path<_new_> >& ps);
	/**
	 * @brief A directed/undirected path between a source node and any other node in the graph
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[out] ps A path between the nodes
	 */
	void xupath(const xxgraph<_new_> *G, node source, vector<boolean_path<_new_> >& ps);

	/**
	 * @brief All directed/undirected paths between a source node and any other node in the graph
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[out] ps All paths between the source node and all other nodes in the graph
	 */
	void xupaths(const xxgraph<_new_> *G, node source, vector<node_path_set<_new_> >& ps);
	/**
	 * @brief All directed/undirected paths between a source node and any other node in the graph
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[out] ps All paths between the source node and all other nodes in the graph
	 */
	void xupaths(const xxgraph<_new_> *G, node source, vector<boolean_path_set<_new_> >& ps);

	// ALL-ALL

	/**
	 * @brief A directed/undirected path between all pairs of nodes in the graph
	 *
	 * Applies Floyd-Warshall's algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[out] ps A path between the nodes
	 */
	void xupath(const xxgraph<_new_> *G, vector<vector<node_path<_new_> > >& ps);
	/**
	 * @brief A directed/undirected path between all pairs of nodes in the graph
	 *
	 * Applies Floyd-Warshall's algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[out] ps A path between the nodes
	 */
	void xupath(const xxgraph<_new_> *G, vector<vector<boolean_path<_new_> > >& ps);

	/**
	 * @brief All directed/undirected paths between all pairs of nodes in the graph
	 *
	 * Applies Floyd-Warshall's algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[out] ps A path between the nodes
	 */
	void xupaths(const xxgraph<_new_> *G, vector<vector<node_path_set<_new_> > >& ps);
	/**
	 * @brief All directed/undirected paths between all pairs of nodes in the graph
	 *
	 * Applies Floyd-Warshall's algorithm.
	 * @param[in] G A directed/undirected unweighted graph
	 * @param[in] source The source node
	 * @param[out] ps A path between the nodes
	 */
	void xupaths(const xxgraph<_new_> *G, vector<vector<boolean_path_set<_new_> > >& ps);

	// ------------------------------------------------------------
	// WEIGHTED FUNCTIONS (for directed/undirected weighted graphs)
	// ------------------------------------------------------------

	/* DISTANCE COMPUTATION */

	// NODE-NODE

	/**
	 * @brief Directed/Undirected distance between two nodes
	 *
	 * Applies Dijkstra's algorithm for shortest-path finding.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @return The shortest distance between @e source and @e target
	 */
	template<class T>
	T xwdistance(const xxgraph<T> *G, node source, node target);
	/**
	 * @brief Directed/Undirected distance between two nodes
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @param[out] n_paths The number of shortest paths between @e source and @e target
	 * @return The shortest distance between @e source and @e target
	 */
	template<class T>
	T xwdistance(const xxgraph<T> *G, node source, node target, size_t& n_paths);

	// NODE-ALL

	/**
	 * @brief Directed/Undirected distance between a node to the rest of the graph's nodes
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @param[out] xwdistances The i-th position contains the directed/undirected distance
	 * between the source node and the i-th node of the graph.
	 */
	template<class T>
	void xwdistance(const xxgraph<T> *G, node source, vector<T>& xwdistances);
	/**
	 * @brief Directed/Undirected distance between a node to the rest of the graph's nodes
	 *
	 * Applies a Breadth-First Search algorithm.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @param[out] xwdistances The i-th position contains the directed/undirected distance
	 * between the source node and the i-th node of the graph.
	 * @param[out] n_paths The i-th position contains the number of shortest paths between
	 * the source node and the i-th node.
	 */
	template<class T>
	void xwdistance(const xxgraph<T> *G, node source, vector<T>& xwdistances, vector<size_t>& n_paths);

	// ALL-ALL

	/**
	 * @brief Directed/Undirected distance between all pairs of nodes
	 *
	 * Applies the Floyd-Warshall algorithm.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[out] ds The shortest directed/undirected distance between all pairs of nodes.
	 */
	template<class T>
	void xwdistances(const xxgraph<T> *G, vector<vector<T> >& ds);
	/**
	 * @brief Directed/Undirected distance between all pairs of nodes
	 *
	 * Applies the Floyd-Warshall algorithm.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[out] ds The shortest directed/undirected distance between all pairs of nodes.
	 * @param[out] n_paths The number of shortest paths between each pair of nodes.
	 */
	template<class T>
	void xwdistances(const xxgraph<T> *G, vector<vector<T> >& ds, vector<vector<size_t> >& n_paths);

	// NODE-NODE

	/**
	 * @brief A directed/undirected path between two nodes
	 *
	 * Applies Dijkstra's algorithm for shortest-path finding.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @param[out] p A path between the nodes
	 */
	template<class T>
	void xwpath(const xxgraph<T> *G, node source, node target, node_path<T>& p);
	/**
	 * @brief A directed/undirected path between two nodes
	 *
	 * Applies Dijkstra's algorithm for shortest-path finding.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @param[out] p A path between the nodes
	 */
	template<class T>
	void xwpath(const xxgraph<T> *G, node source, node target, boolean_path<T>& p);

	/**
	 * @brief All directed/undirected path between two nodes
	 *
	 * Applies Dijkstra's algorithm for shortest-path finding.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @param[out] ps The paths between the nodes
	 */
	template<class T>
	void xwpaths(const xxgraph<T> *G, node source, node target, node_path_set<T>& ps);
	/**
	 * @brief All directed/undirected path between two nodes
	 *
	 * Applies Dijkstra's algorithm for shortest-path finding.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[in] target The target node
	 * @param[out] ps The paths between the nodes
	 */
	template<class T>
	void xwpaths(const xxgraph<T> *G, node source, node target, boolean_path_set<T>& ps);

	// NODE-ALL

	/**
	 * @brief A directed/undirected path between a source node and any other node in the graph
	 *
	 * Applies Dijkstra's algorithm for shortest-path finding.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[out] ps A path between the nodes
	 */
	template<class T>
	void xwpath(const xxgraph<T> *G, node source, vector<node_path<T> >& ps);
	/**
	 * @brief A directed/undirected path between a source node and any other node in the graph
	 *
	 * Applies Dijkstra's algorithm for shortest-path finding.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[out] ps A path between the nodes
	 */
	template<class T>
	void xwpath(const xxgraph<T> *G, node source, vector<boolean_path<T> >& ps);

	/**
	 * @brief All directed/undirected paths between a source node and any other node in the graph
	 *
	 * Applies Dijkstra's algorithm for shortest-path finding.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[out] ps All paths between the source node and all other nodes in the graph
	 */
	template<class T>
	void xwpaths(const xxgraph<T> *G, node source, vector<node_path_set<T> >& ps);
	/**
	 * @brief All directed/undirected paths between a source node and any other node in the graph
	 *
	 * Applies Dijkstra's algorithm for shortest-path finding.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[out] ps All paths between the source node and all other nodes in the graph
	 */
	template<class T>
	void xwpaths(const xxgraph<T> *G, node source, vector<boolean_path_set<T> >& ps);

	// ALL-ALL

	/**
	 * @brief A directed/undirected path between all pairs of nodes in the graph
	 *
	 * Applies Floyd-Warshall's algorithm.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[out] ps A path between the nodes
	 */
	template<class T>
	void xwpath(const xxgraph<T> *G, vector<vector<node_path<T> > >& ps);
	/**
	 * @brief A directed/undirected path between all pairs of nodes in the graph
	 *
	 * Applies Floyd-Warshall's algorithm.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[out] ps A path between the nodes
	 */
	template<class T>
	void xwpath(const xxgraph<T> *G, vector<vector<boolean_path<T> > >& ps);

	/**
	 * @brief All directed/undirected paths between all pairs of nodes in the graph
	 *
	 * Applies Floyd-Warshall's algorithm.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[out] ps A path between the nodes
	 */
	template<class T>
	void xwpaths(const xxgraph<T> *G, vector<vector<node_path_set<T> > >& ps);
	/**
	 * @brief All directed/undirected paths between all pairs of nodes in the graph
	 *
	 * Applies Floyd-Warshall's algorithm.
	 * @param[in] G A directed/undirected weighted graph
	 * @param[in] source The source node
	 * @param[out] ps A path between the nodes
	 */
	template<class T>
	void xwpaths(const xxgraph<T> *G, vector<vector<boolean_path_set<T> > >& ps);

} // -- namespace traversal
} // -- namespace lgraph

// assume weighted graphs
#include "xwpaths.cpp"
#include "xwdistances.cpp"
#include "xwpaths_boolean.cpp"
