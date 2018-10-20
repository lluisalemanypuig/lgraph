#pragma once

/*
 * This file is used for documentation purposes only.
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
		/// Definition of a generic DFS traversal of an unweighted graph
		namespace dfs {}
		/// Definition of a generic Dijkstra traversal of a weighted graph
		namespace dijkstra {}
	} // -- namespace traversal
	
	/// Methods to be applied to networks
	namespace networks {
		
		/// Algorithms to generate random networks
		namespace random {}
		/// Algorithms to generate classic networks
		namespace classic {}
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
		
		/// Algorithms for community-finding
		namespace communities {}
		
	} // -- namespace networks
	
	/**
	 * @brief Collection of functions for reading and writing graphs.
	 * 
	 * This namespace is devoted to reading/writing graphs from/to a
	 * file in several formats. The formats supported are:
	 * 
	 * - edge list (see @ref io::edge_list)
	 * - graph6 (see @ref io::graph6, io::sparse6, io::digraph6)
	 * 
	 * Each format is detailed in the corresponding function.
	 * 
	 * Some formats allow the reading and writing of edge weights.
	 * When it is the case, the type the weights are represented with
	 * must provide an implementation of the '<<' and '>>' operators.
	 * 
	 * For example, when weights are not represented with the usual
	 * numeric types (int,float,double,...), but, say, with integers
	 * with arbitrary precision, the user must provide the
	 * implementation of the '<<' and '>>' operators for this type
	 * of integers. A possibility for doing this is by defining a
	 * class suitable for this type where these two operators are
	 * overloaded.
	 */
	namespace io {}
	
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
