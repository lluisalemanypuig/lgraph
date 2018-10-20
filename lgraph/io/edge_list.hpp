#pragma once

// C++ includes
#include <fstream>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/uxgraph.hpp>
#include <lgraph/data_structures/wxgraph.hpp>

namespace lgraph {
using namespace utils;

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
 * can be done with methods @ref read(const string&, uxgraph *)
 * and @ref write(const string&, uxgraph *).
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
namespace edge_list {

	// ----------------
	// -- UNWEIGHTED --

	/**
	 * @brief Reads an unweighted graph in edge list format.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const string& filename, uxgraph *g);
	/**
	 * @brief Reads an unweighted graph in edge list format.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const char *filename, uxgraph *g);

	/**
	 * @brief Writes an unweighted graph in edge list format.
	 * @param filename The name of the file where the graph will be
	 * written to.
	 * @param g The graph to store.
	 * @return Returns false if the file could not be opened.
	 * Returns true otherwise.
	 */
	bool write(const string& filename, const uxgraph *g);
	/**
	 * @brief Writes an unweighted graph in edge list format.
	 * @param filename The name of the file where the graph will be
	 * written to.
	 * @param g The graph to store.
	 * @return Returns false if the file could not be opened.
	 * Returns true otherwise.
	 */
	bool write(const char *filename, const uxgraph *g);

	// --------------
	// -- WEIGHTED --

	/**
	 * @brief Reads a weighted graph in edge list format.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	template<class T>
	bool read(const string& filename, wxgraph<T> *g);
	/**
	 * @brief Reads a weighted graph in edge list format.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	template<class T>
	bool read(const char *filename, wxgraph<T> *g);

	/**
	 * @brief Writes a weighted graph in edge list format.
	 * @param filename The name of the file where the graph will be
	 * written to.
	 * @param g The graph to store.
	 * @return Returns false if the file could not be opened.
	 * Returns true otherwise.
	 */
	template<class T>
	bool write(const string& filename, const wxgraph<T> *g);
	/**
	 * @brief Writes a weighted graph in edge list format.
	 * @param filename The name of the file where the graph will be
	 * written to.
	 * @param g The graph to store.
	 * @return Returns false if the file could not be opened.
	 * Returns true otherwise.
	 */
	template<class T>
	bool write(const char *filename, const wxgraph<T> *g);

} // -- namespace edge_list
} // -- namespace io
} // -- namespace lgraph

#include <lgraph/io/edge_list_temp.cpp>
