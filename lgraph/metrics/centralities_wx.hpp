#pragma once

// C++ includes
#include <vector>

// lgraph includes
#include <lgraph/data_structures/boolean_path.hpp>
#include <lgraph/data_structures/wxgraph.hpp>

namespace lgraph {
namespace networks {
namespace metrics {
namespace centralities {

/* -------------------------------- */
/* CENTRALITIES FOR WEIGHTED GRAPHS */

/* DEGREE CENTRALITY */

/**
 * @brief Normalised degree centrality of a single node.
 * @param G The weighted graph to be evaluated.
 * @param u The node to be evaluated.
 * @return Returns the degree of node @e u divided by the
 * number of nodes (minus 1).
 */
template<class T>
double degree(const wxgraph<T> *G, node u);

/**
 * @brief Normalised degree centrality of all nodes in a graph.
 * @param[in] G The weighted graph to be evaluated.
 * @param[out] dc The i-th position contains the normalised degree
 * centrality of the i-th node.
 */
template<class T>
void degree(const wxgraph<T> *G, std::vector<double>& dc);

/*  CLOSENESS CENTRALITY */

/**
 * @brief Closeness centrality of all nodes in a graph.
 *
 * The centrality of a node \f$v_i\f$ is defined as:
 *
 * \f$C_i = \left( \frac{1}{n - 1} \sum_{j=1}^n \frac{1}{d_{ij}} \right)^{-1}\f$
 *
 * Computes the distance between each pair of nodes in the graph.
 * @param G The weighted graph to be evaluated.
 * @param u The node to be evaluated.
 * @return Returns the closeness centrality of a node.
 */
template<class T>
double closeness(const wxgraph<T> *G, node u);

/**
 * @brief Closeness centrality of all nodes in a graph.
 *
 * See closeness(const wxgraph<T>*, node) for the details on this centrality's
 * definition.
 *
 * Uses the parameter @e atad to avoit computing the all-to-all distances
 * (the distance between each pair of nodes).
 * @param[in] G The weighted graph to be evaluated.
 * @param[out] cc The @e i-th position contains the
 * closeness centrality of the @e i-th node.
 */
template<class T>
void closeness(const wxgraph<T> *G, std::vector<double>& cc);

/**
 * @brief Closeness centrality of all nodes in a graph.
 *
 * Uses the parameter @e atad to avoit computing the all-to-all distances
 * (the distance between each pair of nodes).
 *
 * @param[in] G The weighted graph to be evaluated.
 * @param[in] atad The matrix with the distance between each pair of nodes.
 * @param[out] cc The @e i-th position contains the
 * closeness centrality of the @e i-th node.
 */
template<class T> void closeness(
	const wxgraph<T> *G,
	const std::vector<std::vector<T> >& atad,
	std::vector<double>& cc
);

/**
 * @brief Mean closeness centrality of a graph.
 *
 * Computes the closeness centrality of each node.
 *
 * @param G The weighted graph to be evaluated.
 * @return Returns the average of the closeness centralities.
 */
template<class T>
double mcc(const wxgraph<T> *G);
/**
 * @brief Mean closeness centrality of a graph.
 *
 * Uses the parameter @e cc to avoid computing the closeness centrality
 * of each node.
 *
 * @param G The weighted graph to be evaluated.
 * @param cc @e cc[u] contains the closeness centrality of node @e u.
 * @return Returns the average of the closeness centralities.
 */
template<class T>
double mcc(const wxgraph<T> *G, const std::vector<double>& cc);

/* BETWEENNESS CENTRALITY */

/**
 * @brief Betweenness centrality of a node.
 *
 * This centrality measure is implemented following the recommendations
 * given in [Newman, 2010]:
 *	- Any path from vertex 's' to vertex 't' is considered to include both
 *		endpoints.
 *	- The equation to calculate the centrality also considers paths from any
 *		vertex to itself.
 *
 * Furthermore, only the pairs of vertices (s,t) with \f$s \le t\f$ are considered.
 * Finally, this metric is also normalised.
 *
 * The expression for this centrality \f$B_i^*\f$ is as follows:
 *
 * \f$ B_i = \sum_{j < k} \frac{g_{jk}(i)}{g_{jk}} \f$,
 * \f$B_i^* = B_i \cdot {n - 1 \choose 2}^{-1}\f$
 *
 * where \f$n\f$ is the number of nodes, \f$g_{jk}(i)\f$ is the number of
 * shortest paths from \f$j\f$ to \f$k\f$ through \f$i\f$, and \f$g_{jk}\f$ is
 * the number of shortest paths from \f$j\f$ to \f$k\f$.
 *
 * [Newman, 2010] Newman, M. E. J. (2010). Networks. An introduction. Oxford
 * University Press, Oxford.
 *
 * This function computes all shortest paths between each pair of nodes.
 * @param G The weighted graph to be evaluated.
 * @param u The node to be evaluated.
 * @return Returns the betweenness centrality of a node, considering
 * that a path between @e u and @e v contains both @e u and @e v.
 */
template<class T>
double betweenness(const wxgraph<T> *G, node u);

/**
 * @brief Betweenness centrality of a node.
 *
 * See @ref betweenness(const wxgraph<T>*, node) for the details on this centrality's
 * definition.
 *
 * This uses the parameter @e paths to avoid computing all the shortest paths between
 * all pair of nodes.
 *
 * @param G The weighted graph to be evaluated.
 * @param paths @e paths[u][v] contains all shortest paths between @e u and @e v
 * for 0 <= @e u , @e v < @e G.n_nodes().
 * @param u The node to be evaluated.
 * @return Returns the betweenness centrality of a node, considering
 * that a path between @e u and @e v contains both @e u and @e v.
 */
template<class T> double betweenness(
	const wxgraph<T> *G,
	const std::vector<std::vector<boolean_path_set<T> > >& paths,
	node u
);

/**
 * @brief Betweenness centrality of a node.
 *
 * See @ref betweenness(const wxgraph<T>*, node) for the details on this centrality's
 * definition.
 *
 * This uses the parameter @e paths to avoid computing all the shortest paths between
 * all pair of nodes.
 *
 * @param G The weighted graph to be evaluated.
 * @param paths @e paths[u][v] contains all shortest paths between @e u and @e v
 * for 0 <= @e u , @e v < @e G.n_nodes().
 * @param u The node to be evaluated.
 * @return Returns the betweenness centrality of a node, considering
 * that a path between @e u and @e v contains both @e u and @e v.
 */
template<class T> double betweenness(
	const wxgraph<T> *G,
	const std::vector<std::vector<boolean_path_set<T> > >& paths,
	node u
);

/**
 * @brief Betweenness centrality of all nodes in a graph.
 *
 * See @ref betweenness(const wxgraph<T>*, node) for the details on this centrality's
 * definition.
 *
 * This function computes all shortest paths between each pair of nodes.
 *
 * @param[in] G The weighted graph to be evaluated.
 * @param[out] bc @e bc[i] contains the betweenness centrality of the @e i-th node.
 */
template<class T>
void betweenness(const wxgraph<T> *G, std::vector<double>& bc);

/**
 * @brief Betweenness centrality of all nodes in a graph
 *
 * See @ref betweenness(const wxgraph<T>*, node) for the details on this centrality's
 * definition.
 *
 * This uses the parameter @e paths to avoid computing all the shortest paths between
 * all pair of nodes.
 *
 * @param[in] G The weighted graph to be evaluated.
 * @param[in] paths @e paths[u][v] contains all shortest paths between @e u and @e v
 * for 0 <= @e u , @e v < @e G.n_nodes().
 * @param[out] bc @e bc[i] contains the betweenness centrality of the @e i-th node.
 */
template<class T> void betweenness(
	const wxgraph<T> *G,
	const std::vector<std::vector<boolean_path_set<T> > >& paths,
	std::vector<double>& bc
);

} // -- namespace centralities
} // -- namespace metrics
} // -- namespace networks
} // -- namespace lgraph

#include <lgraph/metrics/centralities_wx.cpp>
