#include <lgraph/io/gsd6.hpp>

namespace lgraph {
namespace io {
namespace sparse6 {

	// -- READING --

	bool read(const std::string& filename, uugraph& g) {
		return read(filename.c_str(), g);
	}

	bool read(const char *filename, uugraph& g) {
		return true;
	}

	// -- WRITING --

	bool write(const std::string& filename, const uugraph& g) {
		return write(filename.c_str(), g);
	}

	bool write(const char *filename, const uugraph& g) {
		return true;
	}

} // -- namespace sparse6
} // -- namespace io
} // -- namespace lgraph
