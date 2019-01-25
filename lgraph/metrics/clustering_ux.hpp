#pragma once

// lgraph includes
#include <lgraph/data_structures/uxgraph.hpp>

namespace lgraph {
namespace networks {
namespace metrics {
namespace clustering {

/* -------------------------------- */
/* CLUSTERING FOR UNWEIGHTED GRAPHS */

/**
 * @brief Global Clustering Coefficient of an undirected unweighted graph.
 * @param G The unweighted graph to be evaluated.
 * @return Returns the global clustering coefficient of G as defined in
 \verbatim
 Newman, M. E. J. (2010). Networks. An introduction. Oxford
 University Press, Oxford.
 \endverbatim
 */
double gcc(const uxgraph *G);

/**
 * @brief Mean Local Clustering Coefficient of an undirected unweighted graph.
 * @param G The unweighted graph to be evaluated.
 * @return Returns the global clustering coefficient of G as defined in
 \verbatim
 Watts, D. J. and Strogatz, S. H. (1998). Collective
 dynamics of ’small-world’ networks. Nature, 393:440–442.
 \endverbatim
 */
double mlcc(const uxgraph *G);

} // -- namespace clustering
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace lgraph
