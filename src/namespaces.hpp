#pragma once

/*
 * This is used for documentation purposes only
 *
 */

/// Library main namespace
namespace lgraph {

	/**
	 * @brief Collection of path-finding algorithms
	 *
	 * Includes generic algorithms for graph traversal (see @ref BFS,
	 * @ref DFS, @ref Dijkstra) and their application to graphs for
	 * path-finding (shortest path from a node to another node, from
	 * a node to all other nodes of the same graph, ...)
	 */
	namespace traversal {}

	/// Methods to be applied to networks
	namespace networks {

		/// Epidemic algorithms
		namespace epidemics {}

		/// Methods dedicated to measuring metrics on networks
		namespace metrics {
			/// Distance metrics
			namespace distance {}
			/// Clustering metrics
			namespace clustering {}
			/// Centrality metrics
			namespace centralities {}
		} // -- namespace metrics

		/// Algorithms to generate random networks
		namespace random {
			// Switching model algorithm
			namespace switching {}
			// Barabasi-Albert model variants
			namespace Barabasi_Albert {}
		} // -- namespace random

	} // -- namespace networks

	/**
	 * @brief Collection of utilities
	 *
	 * Includes the data structures for:
	 *	* graphs (see @ref xxgraph, @ref uxgraph, @ref uugraph, @ref uwgraph)
	 *	* paths in graphs (see @ref node_path, @ref boolean_path)
	 *	* bitsets (see @ref static_bitset)
	 *	* wrappers for random number generators (see @ref random_generator)
	 *
	 * plus definitions for the types to represent a @ref node, the
	 * @ref neighbourhood of a node in a graph, an @ref edge, ...
	 */
	namespace utils {}

} // -- namespace lgraph
