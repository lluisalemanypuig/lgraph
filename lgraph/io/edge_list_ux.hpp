#pragma once

// lgraph includes
#include <lgraph/data_structures/uxgraph.hpp>
#include <lgraph/data_structures/wxgraph.hpp>

namespace lgraph {
namespace io {

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
bool read(const std::string& filename, uxgraph *g);
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
bool write(const std::string& filename, const uxgraph *g);
/**
 * @brief Writes an unweighted graph in edge list format.
 * @param filename The name of the file where the graph will be
 * written to.
 * @param g The graph to store.
 * @return Returns false if the file could not be opened.
 * Returns true otherwise.
 */
bool write(const char *filename, const uxgraph *g);

} // -- namespace edge_list
} // -- namespace io
} // -- namespace lgraph
