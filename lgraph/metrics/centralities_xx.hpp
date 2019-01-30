#pragma once

// C++ includes
#include <vector>

// lgraph includes
#include <lgraph/data_structures/xxgraph.hpp>

namespace lgraph {
namespace networks {
namespace metrics {
namespace centralities {

/* DEGREE CENTRALITY */

/**
 * @brief Normalised degree centrality of a single node.
 * @param G The unweighted graph to be evaluated.
 * @param u The node to be evaluated.
 * @return Returns the degree of node @e u divided by the
 * number of nodes (minus 1).
 */
double degree(const xxgraph *G, node u);

/**
 * @brief Normalised degree centrality of all nodes in a graph.
 * @param[in] G The unweighted graph to be evaluated.
 * @param[out] dc The i-th position contains the normalised degree
 * centrality of the i-th node.
 */
void degree(const xxgraph *G, std::vector<double>& dc);

} // -- namespace centralities
} // -- namespace metrics
} // -- namespace networks
} // -- namespace lgraph
