#pragma once

// C++ incldues
#include <vector>
using namespace std;

// Custom includes
#include <lgraph/data_structures/uxgraph.hpp>
#include <lgraph/data_structures/wxgraph.hpp>

namespace lgraph {
using namespace utils;

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

	/* ------------------------------ */
	/* CLUSTERING FOR WEIGHTED GRAPHS */

	/**
	 * @brief Global Clustering Coefficient of an undirected unweighted graph.
	 * @param G The weighted graph to be evaluated.
	 * @return Returns the global clustering coefficient of G as defined in
	 \verbatim
	 Newman, M. E. J. (2010). Networks. An introduction. Oxford
	 University Press, Oxford.
	 \endverbatim
	 */
	template<class T>
	double gcc(const wxgraph<T> *G);

	/**
	 * @brief Mean Local Clustering Coefficient of an undirected unweighted graph.
	 * @param G The weighted graph to be evaluated.
	 * @return Returns the global clustering coefficient of G as defined in
	 \verbatim
	 Watts, D. J. and Strogatz, S. H. (1998). Collective
	 dynamics of ’small-world’ networks. Nature, 393:440–442.
	 \endverbatim
	 */
	template<class T>
	double mlcc(const wxgraph<T> *G);

} // -- namespace clustering
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace lgraph

#include <lgraph/metrics/wclustering.cpp>
