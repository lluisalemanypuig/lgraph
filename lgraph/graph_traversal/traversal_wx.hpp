#pragma once

// C++ includes
#include <vector>

// lgraph includes
#include <lgraph/data_structures/boolean_path.hpp>
#include <lgraph/data_structures/node_path.hpp>
#include <lgraph/data_structures/wxgraph.hpp>

namespace lgraph {
namespace traversal {

// ------------------------------------------------------------
// WEIGHTED FUNCTIONS (for directed/undirected weighted graphs)
// ------------------------------------------------------------

/* DISTANCE COMPUTATION */

// NODE-NODE

/**
 * @brief Directed/Undirected distance between two nodes.
 *
 * Applies Dijkstra's algorithm for shortest-path finding.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[in] source The source node.
 * @param[in] target The target node.
 * @return The shortest distance between @e source and @e target.
 */
template<class T>
T wxdistance(const wxgraph<T> *G, node source, node target);
/**
 * @brief Directed/Undirected distance between two nodes.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[in] source The source node.
 * @param[in] target The target node.
 * @param[out] n_paths The number of shortest paths between @e source and
 * @e target.
 * @return The shortest distance between @e source and @e target.
 */
template<class T>
T wxdistance(const wxgraph<T> *G, node source, node target, size_t& n_paths);

// NODE-ALL

/**
 * @brief Directed/Undirected distance between a node to the rest of the
 * graph's nodes.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[in] source The source node.
 * @param[out] wxdistances The i-th position contains the directed/undirected
 * distance between the source node and the i-th node of the graph.
 */
template<class T>
void wxdistance(const wxgraph<T> *G, node source, std::vector<T>& wxdistances);
/**
 * @brief Directed/Undirected distance between a node to the rest of the graph's nodes.
 *
 * Applies a Breadth-First Search algorithm.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[in] source The source node.
 * @param[out] wxdistances The i-th position contains the directed/undirected
 * distance between the source node and the i-th node of the graph.
 * @param[out] n_paths The i-th position contains the number of shortest paths
 * between the source node and the i-th node.
 */
template<class T>
void wxdistance(
	const wxgraph<T> *G, node source,
	std::vector<T>& wxdistances, std::vector<size_t>& n_paths
);

// ALL-ALL

/**
 * @brief Directed/Undirected distance between all pairs of nodes.
 *
 * Applies the Floyd-Warshall algorithm.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[out] ds The shortest directed/undirected distance between all pairs
 * of nodes.
 */
template<class T>
void wxdistances(const wxgraph<T> *G, std::vector<std::vector<T> >& ds);
/**
 * @brief Directed/Undirected distance between all pairs of nodes.
 *
 * Applies the Floyd-Warshall algorithm.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[out] ds The shortest directed/undirected distance between all pairs
 * of nodes.
 * @param[out] n_paths The number of shortest paths between each pair of nodes.
 */
template<class T>
void wxdistances(
	const wxgraph<T> *G,
	std::vector<std::vector<T> >& ds, std::vector<std::vector<size_t> >& n_paths
);

// NODE-NODE

/**
 * @brief A directed/undirected path between two nodes.
 *
 * Applies Dijkstra's algorithm for shortest-path finding.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[in] source The source node.
 * @param[in] target The target node.
 * @param[out] p A path between the nodes.
 */
template<class T>
void wxpath(const wxgraph<T> *G, node source, node target, node_path<T>& p);
/**
 * @brief A directed/undirected path between two nodes.
 *
 * Applies Dijkstra's algorithm for shortest-path finding.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[in] source The source node.
 * @param[in] target The target node.
 * @param[out] p A path between the nodes.
 */
template<class T>
void wxpath(const wxgraph<T> *G, node source, node target, boolean_path<T>& p);

/**
 * @brief All directed/undirected path between two nodes.
 *
 * Applies Dijkstra's algorithm for shortest-path finding.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[in] source The source node.
 * @param[in] target The target node.
 * @param[out] ps The paths between the nodes.
 */
template<class T>
void wxpaths(const wxgraph<T> *G, node source, node target, node_path_set<T>& ps);
/**
 * @brief All directed/undirected path between two nodes.
 *
 * Applies Dijkstra's algorithm for shortest-path finding.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[in] source The source node.
 * @param[in] target The target node.
 * @param[out] ps The paths between the nodes.
 */
template<class T>
void wxpaths(const wxgraph<T> *G, node source, node target, boolean_path_set<T>& ps);

// NODE-ALL

/**
 * @brief A directed/undirected path between a source node and any other node
 * in the graph.
 *
 * Applies Dijkstra's algorithm for shortest-path finding.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[in] source The source node.
 * @param[out] ps A path between the nodes.
 */
template<class T>
void wxpath(const wxgraph<T> *G, node source, std::vector<node_path<T> >& ps);
/**
 * @brief A directed/undirected path between a source node and any other node
 * in the graph.
 *
 * Applies Dijkstra's algorithm for shortest-path finding.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[in] source The source node.
 * @param[out] ps A path between the nodes.
 */
template<class T>
void wxpath(const wxgraph<T> *G, node source, std::vector<boolean_path<T> >& ps);

/**
 * @brief All directed/undirected paths between a source node and any other
 * node in the graph.
 *
 * Applies Dijkstra's algorithm for shortest-path finding.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[in] source The source node.
 * @param[out] ps All paths between the source node and all other nodes in
 * the graph.
 */
template<class T>
void wxpaths(const wxgraph<T> *G, node source, std::vector<node_path_set<T> >& ps);
/**
 * @brief All directed/undirected paths between a source node and any other
 * node in the graph.
 *
 * Applies Dijkstra's algorithm for shortest-path finding.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[in] source The source node.
 * @param[out] ps All paths between the source node and all other nodes in
 * the graph.
 */
template<class T>
void wxpaths(
	const wxgraph<T> *G, node source, std::vector<boolean_path_set<T> >& ps
);

// ALL-ALL

/**
 * @brief A directed/undirected path between all pairs of nodes in the graph.
 *
 * Applies Floyd-Warshall's algorithm.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[out] ps A path between the nodes.
 */
template<class T>
void wxpath(const wxgraph<T> *G, std::vector<std::vector<node_path<T> > >& ps);
/**
 * @brief A directed/undirected path between all pairs of nodes in the graph.
 *
 * Applies Floyd-Warshall's algorithm.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[out] ps A path between the nodes.
 */
template<class T>
void wxpath(const wxgraph<T> *G, std::vector<std::vector<boolean_path<T> > >& ps);

/**
 * @brief All directed/undirected paths between all pairs of nodes in the graph.
 *
 * Applies Floyd-Warshall's algorithm.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[out] ps A path between the nodes.
 */
template<class T>
void wxpaths(const wxgraph<T> *G, std::vector<std::vector<node_path_set<T> > >& ps);
/**
 * @brief All directed/undirected paths between all pairs of nodes in the graph.
 *
 * Applies Floyd-Warshall's algorithm.
 *
 * @param[in] G A directed/undirected weighted graph.
 * @param[out] ps A path between the nodes.
 */
template<class T>
void wxpaths(const wxgraph<T> *G, std::vector<std::vector<boolean_path_set<T> > >& ps);

} // -- namespace traversal
} // -- namespace lgraph

#include <lgraph/graph_traversal/paths_wx.cpp>
#include <lgraph/graph_traversal/distances_wx.cpp>
#include <lgraph/graph_traversal/paths_boolean_wx.cpp>
