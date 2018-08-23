#pragma once

/*
 * This is used for documentation purposes only
 *
 */

/// Library's main namespace
namespace lgraph {

	/**
	 * @brief Collection of path-finding algorithms
	 *
	 * Includes generic algorithms for graph traversal (see @ref bfs,
	 * @ref dfs, @ref dijkstra) and their application to graphs for
	 * path-finding (shortest path from a node to another node, from
	 * a node to all other nodes of the same graph, ...)
	 */
	namespace traversal {
		/// Definition of a generic BFS traversal of an unweighted graph
		namespace bfs {}
		/// Definition of a generic BFS traversal of an unweighted graph
		namespace dfs {}
		/// Definition of a generic BFS traversal of an weighted graph
		namespace dijkstra {}
	}

	/// Methods to be applied to networks
	namespace networks {
		
		/// Algorithms to generate social networks
		namespace social {
			/// Algorithms to generate random social networks
			namespace random {}
		}
		
		/// Algorithms to generate classic networks
		namespace classic {
			/// Algorithms to generate random classic networks
			namespace random {}
		}
		
		/// Algorithms for modifying already existing networks
		namespace modify {}
		
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
	 *	* graphs (see @ref xxgraph, @ref uxgraph, @ref uugraph, @ref udgraph,
	 *		@ref wxgraph, @ref wugraph, @ref wdgraph)
	 *	* paths in graphs (see @ref node_path, @ref boolean_path)
	 *	* bitsets (see @ref static_bitset)
	 *	* wrappers for random number generators (see @ref random_generator)
	 *
	 * plus definitions for the types to represent a @ref node, the
	 * @ref neighbourhood of a node in a graph, an @ref edge, ...
	 */
	namespace utils {}

} // -- namespace lgraph
