#pragma once

// C++ includes
#include <fstream>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>

namespace lgraph {
using namespace utils;

namespace io {

/**
 * @brief Read/write graphs in \e graph6 format.
 *
 * This format is detailed (as of 20th October 2018)
 * in the webpage:
 *
 * http://users.cecs.anu.edu.au/~bdm/data/formats.html
 *
 * by Brendan McKay (http://users.cecs.anu.edu.au/~bdm/)
 */
namespace graph6 {

	// UNWEIGHTED

	/**
	 * @brief Reads an unweighted, undirected graph in graph6 format.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const string& filename, uugraph& g);
	/**
	 * @brief Reads an unweighted, undirected graph in graph6 format.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const char *filename, uugraph& g);

	/**
	 * @brief Writes an unweighted, undirected graph in graph6 format.
	 * @param filename The name of the file where the graph will be
	 * written to.
	 * @param g The graph to store.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool write(const string& filename, const uugraph& g);
	/**
	 * @brief Writes an unweighted, undirected graph in graph6 format.
	 * @param filename The name of the file where the graph will be
	 * written to.
	 * @param g The graph to store.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool write(const char *filename, const uugraph& g);

	/*
	 * This format is intended for undirected graphs only.
	 */

} // -- namespace graph6

/**
 * @brief Read/write graphs in \e sparse6 format.
 *
 * This format is detailed (as of 20th October 2018)
 * in the webpage:
 *
 * http://users.cecs.anu.edu.au/~bdm/data/formats.html
 *
 * by Brendan McKay (http://users.cecs.anu.edu.au/~bdm/)
 */
namespace sparse6 {

	// UNWEIGHTED

	/**
	 * @brief Reads an unweighted, undirected graph in graph6 format.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const string& filename, uugraph& g);
	/**
	 * @brief Reads an unweighted, undirected graph in graph6 format.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const char *filename, uugraph& g);

	/**
	 * @brief Writes an unweighted, undirected graph in graph6 format.
	 * @param filename The name of the file where the graph will be
	 * written to.
	 * @param g The graph to store.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool write(const string& filename, const uugraph& g);
	/**
	 * @brief Writes an unweighted, undirected graph in graph6 format.
	 * @param filename The name of the file where the graph will be
	 * written to.
	 * @param g The graph to store.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool write(const char *filename, const uugraph& g);

	/*
	 * This format is intended for undirected graphs only.
	 */

} // -- namespace sparse6

/**
 * @brief Read/write graphs in \e digraph6 format.
 *
 * This format is detailed (as of 20th October 2018)
 * in the webpage:
 *
 * http://users.cecs.anu.edu.au/~bdm/data/formats.html
 *
 * by Brendan McKay (http://users.cecs.anu.edu.au/~bdm/)
 */
namespace digraph6 {

	// UNWEIGHTED

	/*
	 * This format is intended for directed graphs only.
	 */

	/**
	 * @brief Reads an unweighted, directed graph in graph6 format.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const string& filename, udgraph& g);
	/**
	 * @brief Reads an unweighted, directed graph in graph6 format.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const char *filename, udgraph& g);

	/**
	 * @brief Writes an unweighted, directed graph in graph6 format.
	 * @param filename The name of the file where the graph will be
	 * written to.
	 * @param g The graph to store.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool write(const string& filename, const udgraph& g);
	/**
	 * @brief Writes an unweighted, directed graph in graph6 format.
	 * @param filename The name of the file where the graph will be
	 * written to.
	 * @param g The graph to store.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool write(const char *filename, const udgraph& g);

	// WEIGHTED

	/*
	 * This format is intended for directed graphs only.
	 */

} // -- namespace digraph6

} // -- namespace io
} // -- namespace lgraph
