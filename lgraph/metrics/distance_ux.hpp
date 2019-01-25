#pragma once

// C++ incldues
#include <functional>
#include <numeric>
#include <vector>

// lgraph includes
#include <lgraph/data_structures/uxgraph.hpp>

namespace lgraph {
namespace networks {
namespace metrics {
namespace distance {

/* ------------------------------- */
/* DISTANCES FOR UNWEIGHTED GRAPHS */

/**
 * @brief Diameter of a graph.
 *
 * Computes the distance between all pairs of nodes.
 *
 * @param G The graph to be evaluated.
 * @return Returns the largest distance between all pairs of nodes.
 */
_new_ max_distance(const uxgraph *G);
/**
 * @brief Diameter of a graph.
 *
 * Uses the parameter @e ds to avoid computing the distance between
 * all pairs of nodes.
 *
 * @param G The graph to be evaluated.
 * @param ds @e ds[u][v] contains the distance between nodes @e u and @e v.
 * @return Returns the largest distance between all pairs of nodes.
 */
_new_ max_distance(const uxgraph *G, const std::vector<std::vector<_new_> >& ds);

/**
 * @brief Mean distance between all pairs of nodes.
 *
 * Computes the distance between all pairs of nodes.
 *
 * @param G The graph to be evaluated.
 * @return Returns the average of the distance between all pairs of nodes.
 */
double mean_distance(const uxgraph *G);
/**
 * @brief Mean distance between all pairs of nodes.
 *
 * Uses the parameter @e ds to avoid computing the distance between
 * all pairs of nodes.
 *
 * @param G The graph to be evaluated.
 * @param ds @e ds[u][v] contains the distance between nodes @e u and @e v.
 * @return Returns the average of the distance between all pairs of nodes.
 */
double mean_distance(const uxgraph *G, const std::vector<std::vector<_new_> >& ds);

/**
 * @brief Mean closeness centrality of a graph.
 *
 * Computes the closeness centrality of each node.
 *
 * @param G The graph to be evaluated.
 * @return Returns the average of the closeness centralities.
 */
double mcc(const uxgraph *G);
/**
 * @brief Mean closeness centrality of a graph.
 *
 * Uses the parameter @e cc to avoid computing the closeness centrality
 * of each node.
 *
 * @param G The graph to be evaluated.
 * @param cc @e cc[u] contains the closeness centrality of node @e u.
 * @return Returns the average of the closeness centralities.
 */
double mcc(const uxgraph *G, const std::vector<double>& cc);

} // -- namespace distance
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace lgraph

#include <lgraph/metrics/distance_wx.cpp>
