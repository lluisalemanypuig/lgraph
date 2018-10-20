#include <lgraph/io/gsd6.hpp>

namespace lgraph {
namespace io {
namespace sparse6 {

	// -- READING --

	bool read(const string& filename, uugraph& g) {
		return read(filename.c_str(), g);
	}

	bool read(const char *filename, uugraph& g) {

	}

	// -- WRITING --

	bool write(const string& filename, const uugraph& g) {
		return write(filename.c_str(), g);
	}

	bool write(const char *filename, const uugraph& g) {

	}

} // -- namespace sparse6
} // -- namespace io
} // -- namespace lgraph
