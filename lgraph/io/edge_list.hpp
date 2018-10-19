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
 * @brief Read/write graphs in \a edge list format.
 *
 * Detailed description of the format....
 *
 * Reference!
 */
namespace edge_list {

	// UNWEIGHTED

	void read(const string& filename, uxgraph *g);
	void read(const char *filename, uxgraph *g);

	void write(const string& filename, const uxgraph *g);
	void write(const char *filename, const uxgraph *g);

	// WEIGHTED

	template<class T>
	void read(const string& filename, wxgraph<T> *g);
	template<class T>
	void read(const char *filename, wxgraph<T> *g);

	template<class T>
	void write(const string& filename, const wxgraph<T> *g);
	template<class T>
	void write(const char *filename, const wxgraph<T> *g);

} // -- namespace edge_list
} // -- namespace io
} // -- namespace lgraph
