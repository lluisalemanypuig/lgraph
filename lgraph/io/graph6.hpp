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
 * @brief Read/write graphs in \a graph6 format.
 *
 * Detailed description of the format....
 *
 * Reference!
 */
namespace graph6 {

	// UNWEIGHTED

	void read(const string& filename, uugraph& g);
	void read(const char *filename, uugraph& g);

	void write(const string& filename, const uugraph& g);
	void write(const char *filename, const uugraph& g);

	/*
	 * This format does not support directed graphs (as of 19/10/2018).
	 */

	// WEIGHTED

	/*
	 * This format does not support weighted graphs (as of 19/10/2018).
	 */

} // -- namespace graph6

/**
 * @brief Read/write graphs in \a sparse6 format.
 *
 * Detailed description of the format....
 *
 * Reference!
 */
namespace sparse6 {

	// UNWEIGHTED

	void read(const string& filename, uugraph& g);
	void read(const char *filename, uugraph& g);

	void write(const string& filename, const uugraph& g);
	void write(const char *filename, const uugraph& g);

	/*
	 * This format does not support directed graphs (as of 19/10/2018).
	 */

	// WEIGHTED

	/*
	 * This format does not support weighted graphs (as of 19/10/2018).
	 */

} // -- namespace sparse6

/**
 * @brief Read/write graphs in \a digraph6 format.
 *
 * Detailed description of the format....
 *
 * Reference!
 */
namespace digraph6 {

	// UNWEIGHTED

	/*
	 * This format does not support undirected graphs (as of 19/10/2018).
	 */

	void read(const string& filename, udgraph& g);
	void read(const char *filename, udgraph& g);

	void write(const string& filename, const udgraph& g);
	void write(const char *filename, const udgraph& g);

	// WEIGHTED

	/*
	 * This format does not support weighted graphs (as of 19/10/2018).
	 */

} // -- namespace digraph6

} // -- namespace io
} // -- namespace lgraph
