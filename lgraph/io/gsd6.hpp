#pragma once

// C++ includes
#include <fstream>

// lgraph includes
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>

namespace lgraph {
namespace io {

	/**
	 * @brief Three different types of binary formats for storing graphs.
	 *
	 * See details in @ref gsd6_format::Graph6, @ref gsd6_format::Graph6,
	 * @ref gsd6_format::Sparse6, @ref gsd6_format::Incremental_Sparse6
	 * and @ref gsd6_format::DiGraph6.
	 */
	enum class gsd6_format : int8_t {
		/// @ref sparse6 format. String starts with ':'. See namespace sparse6 for
		/// details.
		Sparse6,
		/// Incremental @ref sparse6 format. String starts with ';'. See namespace
		/// sparse6 for details.
		Incremental_Sparse6,
		/// @ref digraph6 format. String starts with '&'. See namespace digraph6
		/// for details.
		DiGraph6,
		/// @ref graph6 format. String starts with none of the above. See namespace
		/// graph6 for details.
		Graph6,
	};

	/**
	 * @brief Returns the format of the binary encoding of a graph in @e s.
	 *
	 * If a format mismatch occurs an error message will be output.
	 * @param[in] s A graph codified in a string.
	 * @param[out] format Enumeration value representing the format of the string.
	 * @param[out] h Header (optional) in the string.
	 * @param[out] f First (and optional) character in the string after the
	 * header (if any) that defines the format. Comes before the bytes encoding
	 * the number of vertices of the graph and takes the values:
	 * - ' ', for graph6,
	 * - ':', for sparse6,
	 * - ';', for incremental sparse 6,
	 * - '&', for digraph6.
	 * @param[out] k Index of the first character with data.
	 * @return Returns true on success.
	 */
	bool gsd6_string_format
	(const std::string& s, gsd6_format& format, std::string& h, char& f, size_t& k);

	/// Returns the first character of a sparse6-formatted string.
	inline char sparse6_first() { return ':'; }
	/// Returns the first character of a incremental sparse6-formatted string.
	inline char incremental_sparse6_first() { return ';'; }
	/// Returns the first character of a digraph6-formatted string.
	inline char digraph6_first() { return '&'; }

	/// Returns the optional header of a file containing graph6-formatted strings.
	inline std::string graph6_header() { return ">>graph6<<"; }
	/// Returns the optional header of a file containing sparse6-formatted strings.
	inline std::string sparse6_header() { return ">>sparse6<<"; }
	/// Returns the optional header of a file containing incremental
	/// sparse6-formatted strings.
	inline std::string incremental_sparse6_header() { return ">>sparse6<<"; }
	/// Returns the optional header of a file containing digraph6-formatted
	/// strings.
	inline std::string digraph6_header() { return ">>digraph6<<"; }

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

	// --------------------------
	// -- GRAPH FROM/TO STRING --

	/**
	 * @brief Obtains a graph given its representation in @e graph6 format.
	 * @param s The list of characters that encode the graph.
	 * @param[out] g The graph resulting from decoding @e s.
	 * @return Returns true on success.
	 * @pre The output graph need not be passed empty (it is cleared
	 * in this function).
	 */
	bool from_g6_string(const std::string& s, uugraph& g);

	/**
	 * @brief Obtains a graph given its representation in @e graph6 format.
	 * @param g The graph to be encoded.
	 * @param[out] s The graph decoded in graph6 format.
	 * @pre The output string need not be passed empty (it is cleared
	 * in this function)
	 */
	void to_g6_string(const uugraph& g, std::string& s);

	// ----------
	// -- READ --

	/**
	 * @brief Reads an unweighted, undirected graph in \e graph6 format.
	 *
	 * The file may contain more than one graph. However, if there is
	 * more than one, only the first will be read.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const std::string& filename, uugraph& g);
	/**
	 * @brief Reads an unweighted, undirected graph in \e graph6 format.
	 *
	 * The file can only contain one single graph. If there is more
	 * than one, only the first will be read.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const char *filename, uugraph& g);

	/**
	 * @brief Reads a list of unweighted, undirected graphs in \e graph6 format.
	 * @param filename The name of the file to be read.
	 * @param[out] gs The graphs built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const std::string& filename, std::vector<uugraph>& gs);
	/**
	 * @brief Reads a list of unweighted, undirected graphs in \e graph6 format.
	 * @param filename The name of the file to be read.
	 * @param[out] gs The graphs built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const char *filename, std::vector<uugraph>& gs);

	// -----------
	// -- WRITE --

	/**
	 * @brief Writes an unweighted, undirected graph in \e graph6 format.
	 *
	 * The graph will be appended at the end of the file.
	 * @param filename The name of the file where the graph will be
	 * written to.
	 * @param g The graph to store.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool write(const std::string& filename, const uugraph& g);
	/**
	 * @brief Writes an unweighted, undirected graph in \e graph6 format.
	 *
	 * The graph will be appended at the end of the file.
	 * @param filename The name of the file where the graph will be
	 * written to.
	 * @param g The graph to store.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool write(const char *filename, const uugraph& g);

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
	 * @brief Reads an unweighted, undirected graph in \e sparse6 format.
	 *
	 * The file can only contain one single graph. If there is more
	 * than one, only the first will be read.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const std::string& filename, uugraph& g);
	/**
	 * @brief Reads an unweighted, undirected graph in \e sparse6 format.
	 *
	 * The file can only contain one single graph. If there is more
	 * than one, only the first will be read.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const char *filename, uugraph& g);

	/**
	 * @brief Writes an unweighted, undirected graph in \e sparse6 format.
	 *
	 * The graph will be appended at the end of the file.
	 * @param filename The name of the file where the graph will be
	 * written to.
	 * @param g The graph to store.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool write(const std::string& filename, const uugraph& g);
	/**
	 * @brief Writes an unweighted, undirected graph in \e sparse6 format.
	 *
	 * The graph will be appended at the end of the file.
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
	 * @brief Reads an unweighted, directed graph in \e digraph6 format.
	 *
	 * The file can only contain one single graph. If there is more
	 * than one, only the first will be read.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const std::string& filename, udgraph& g);
	/**
	 * @brief Reads an unweighted, directed graph in \e digraph6 format.
	 *
	 * The file can only contain one single graph. If there is more
	 * than one, only the first will be read.
	 * @param filename The name of the file to be read.
	 * @param[out] g The graph built with the contents in the file.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool read(const char *filename, udgraph& g);

	/**
	 * @brief Writes an unweighted, directed graph in \e digraph6 format.
	 *
	 * The graph will be appended at the end of the file.
	 * @param filename The name of the file where the graph will be
	 * written to.
	 * @param g The graph to store.
	 * @return Returns false if the file coule not be opened.
	 * Returns true otherwise.
	 */
	bool write(const std::string& filename, const udgraph& g);
	/**
	 * @brief Writes an unweighted, directed graph in \e digraph6 format.
	 *
	 * The graph will be appended at the end of the file.
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
