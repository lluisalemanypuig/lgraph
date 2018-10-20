#include <lgraph/io/gsd6.hpp>

namespace lgraph {
namespace io {
namespace digraph6 {

	// -- READING --

	bool read(const string& filename, udgraph& g) {
		return read(filename.c_str(), g);
	}

	bool read(const char *filename, udgraph& g) {

	}

	// -- WRITING --

	bool write(const string& filename, const udgraph& g) {
		return write(filename.c_str(), g);
	}

	bool write(const char *filename, const udgraph& g) {

	}

} // -- namespace digraph6
} // -- namespace io
} // -- namespace lgraph

