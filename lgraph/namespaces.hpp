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
	 * - binary formats (see @ref io::graph6, io::sparse6, io::digraph6)
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
	namespace io {
		
		/**
		 * @brief Read/write graphs in \a edge \a list format.
		 *
		 * For both undirected and directed graphs, the edge list
		 * format consists of the list of edges represented as
		 * pairs of indices:
		 \verbatim
		 u v
		 \endverbatim
		 *
		 * where \a u and \a v represent two vertices of the graph.
		 *
		 * If the graph has @e n vertices, these two indices are
		 * positive integer values such that: \f$0 \le u,v < n\f$.
		 *
		 * When an undirected graph the pair (@e u, @e v) represents
		 * the two directed egdes (u -> v) and (v -> u). When reading
		 * a directed graph the same pair represents the edge (u -> v).
		 *
		 * Reading/Writing a directed/undirected from/to a file graph
		 * can be done with methods @ref read(const std::string&, uxgraph *)
		 * and @ref write(const std::string&, const uxgraph *).
		 *
		 * This format can be enriched with more information about
		 * the edges such as their weight. In this case, if an edge
		 * (u -> v) has weight @e w, then the format is as follows:
		 \verbatim
		 u v w
		 \endverbatim
		 *
		 * For any type of graph ( {directed,undirected}x{weighted,unweighted} )
		 * all nodes with index higher than the las vertex's index involved in an
		 * edge are lost when writing them to a file. For example, a graph
		 * with 1000 nodes, but only one edge between the 13-th and 14-th
		 * vertices, the contents of the file when writing the graph are:
		 \verbatim
		 13 14
		 \endverbatim
		 *
		 * Therefore, after reading that file the resulting graph
		 * will have only 15 vertices, labelled with the indices in [0,14].
		 */
		namespace edge_list {}
	}
	
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
