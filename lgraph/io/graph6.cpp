#include <lgraph/io/gsd6.hpp>
#include <lgraph/utils/logger.hpp>

#include <limits>
#include <bitset>

namespace lgraph {
namespace io {
namespace graph6 {

using namespace std;
using namespace utils;

	// Convert the first 6 bits of 'k' into
	// a decimal number considering that the
	// first bit starts at power p.
	// d is in big endian.
	#define BIN6_TO_SIZE_T(d,p)				\
		(size_t(d & 0x01) << size_t(p)) +	\
		(size_t(d & 0x02) << size_t(p)) +	\
		(size_t(d & 0x04) << size_t(p)) +	\
		(size_t(d & 0x08) << size_t(p)) +	\
		(size_t(d & 0x10) << size_t(p)) +	\
		(size_t(d & 0x20) << size_t(p))

	// Converts the lower 6 bits starting at p
	// of a decimal number b (unsigned integer).
	// The last 'and' is there to prevent leading 1's
	// b is an integer
	#define SIZE_T_TO_BIN6(b,p)								\
		((b & size_t(0x01) << size_t(p)) >> size_t(p))	|	\
		((b & size_t(0x02) << size_t(p)) >> size_t(p))	|	\
		((b & size_t(0x04) << size_t(p)) >> size_t(p))	|	\
		((b & size_t(0x08) << size_t(p)) >> size_t(p))	|	\
		((b & size_t(0x10) << size_t(p)) >> size_t(p))	|	\
		((b & size_t(0x20) << size_t(p)) >> size_t(p))

	#define THREE_BIN6_TO_SIZE_T(a,b,c)		\
		BIN6_TO_SIZE_T((a - 63),12) +		\
		BIN6_TO_SIZE_T((b - 63), 6) +		\
		BIN6_TO_SIZE_T((c - 63), 0)
	#define SIX_BIN6_TO_SIZE_T(a,b,c,d,e,f)	\
		BIN6_TO_SIZE_T((a - 63),30) +		\
		BIN6_TO_SIZE_T((b - 63),24) +		\
		BIN6_TO_SIZE_T((c - 63),18) +		\
		BIN6_TO_SIZE_T((d - 63),12) +		\
		BIN6_TO_SIZE_T((e - 63), 6) +		\
		BIN6_TO_SIZE_T((f - 63), 0)

	void from_g6_string(const string& s, uugraph& g) {
		size_t k = 0;

		// ignore first optional character
		if (s[0] == ':' or s[0] == ';' or s[0] == '&') {
			++k;
		}

		// retrieve number of vertices
		size_t n;
		if (s[k] != 0x7e) {
			// 0 <= n <= 62
			n = size_t(s[k] - 63);
			++k;
		}
		else {
			++k;
			if (s[k] != 0x7e) {
				// 63 <= n <= 258047
				n = THREE_BIN6_TO_SIZE_T(s[k],s[k+1],s[k+2]);
				k += 3;
			}
			else {
				// 258048 <= n <= 68,719,476,735

				if (uint64_t(numeric_limits<size_t>::max()) <= uint64_t(68719476735)) {
					logger<cerr_stream>& LOG = logger<cerr_stream>::get_logger();
					LOG.log() << "Warning: when parsing graph in graph6 format." << std::endl;
					LOG.log() << "    The amount of nodes will be read into a 'size_t' type" << std::endl;
					LOG.log() << "    which, in your system, may not have enough precision" << std::endl;
					LOG.log() << "    to fit the maximum amount of vertices of your graph." << std::endl;
					LOG.log() << "    The maximum amount of vertices allowed in graph6 is:" << std::endl;
					LOG.log() << "        68719476735" << std::endl;
					LOG.log() << "    Your 'size_t' can hold up to:" << std::endl;
					LOG.log() << "        " << numeric_limits<size_t>::max() << std::endl;
				}

				++k;
				n = SIX_BIN6_TO_SIZE_T(s[k],s[k+1],s[k+2],
									s[k+3],s[k+4],s[k+5]);
				k += 6;
			}
		}

		// initialise graph
		g.init(n);

		char byte = s[k] - 63;
		char mask = 0x20;
		char bit_idx = 6;	// skip the first two bits

		// O(n^2) algorithm. Not efficient,
		// but can't avoid it.
		for (size_t j = 1; j < n; ++j) {
			for (size_t i = 0; i < j; ++i) {
				if ((byte & mask) != 0) {
					g.add_edge(i, j);
				}

				--bit_idx;
				mask >>= 1;

				if (bit_idx == 0) {
					bit_idx = 6;	// skip the first two bits
					++k;
					// avoid segmentation faults, please
					if (k < s.length()) {
						byte = s[k] - 63;
					}
					mask = 0x20;
				}
			}
		}
	}

	void to_g6_string(const uugraph& g, string& s) {
		size_t N = g.n_nodes();

		/* Obtain N(x) for x=N, the number of vertices
		 * in the graph.
		 */
		if (N <= 62) {
			// convert to binary
			char n = static_cast<char>(N) + 63;
			s += n;
		}
		else if (N <= 258047) {
			// 63 <= n <= 258047
			s += char(0x7e);

			s += static_cast<char>(63 + (0x03f & (SIZE_T_TO_BIN6(N, 0))));
			s += static_cast<char>(63 + (0x03f & (SIZE_T_TO_BIN6(N, 8))));
			s += static_cast<char>(63 + (0x03f & (SIZE_T_TO_BIN6(N,16))));
		}
		else {
			// 258048 <= n <= 68,719,476,735
			s += char(0x7e);
			s += char(0x7e);

			s += static_cast<char>(63 + (0x03f & (SIZE_T_TO_BIN6(N, 0))));
			s += static_cast<char>(63 + (0x03f & (SIZE_T_TO_BIN6(N, 8))));
			s += static_cast<char>(63 + (0x03f & (SIZE_T_TO_BIN6(N,16))));
			s += static_cast<char>(63 + (0x03f & (SIZE_T_TO_BIN6(N,24))));
			s += static_cast<char>(63 + (0x03f & (SIZE_T_TO_BIN6(N,32))));
			s += static_cast<char>(63 + (0x03f & (SIZE_T_TO_BIN6(N,40))));
		}

		/* 'Store' the edges of the graph.
		 */

		char byte = 0;
		char mask = 0x20;
		char bit_idx = 6;	// skip the first two bits

		for (node j = 1; j < N; ++j) {
			for (node i = 0; i < j; ++i) {
				// output edge (i,j) iff i < j

				if (g.has_edge(i,j)) {
					byte |= (0xff & mask);
				}

				--bit_idx;
				mask >>= 1;

				// skip the first two bits of each byte
				if (bit_idx == 0) {
					s += static_cast<char>(byte + 63);

					bit_idx = 6;
					byte = 0;
					mask = 0x20;
				}
			}
		}

		if (bit_idx != 0) {
			// the last byte surely hasn't been added
			// do it now
			s += static_cast<char>(byte + 63);
		}
	}

	// -- READING --

	bool read(const string& filename, uugraph& g) {
		return read(filename.c_str(), g);
	}

	bool read(const char *filename, uugraph& g) {
		ifstream fin;
		fin.open(filename);
		if (not fin.is_open()) {
			return false;
		}

		// Bear in mind that the file may contain
		// several lines, but only one will be read.

		// ignore heather and empty lines
		string data = "";
		while (data == "" or data == ">>graph6<<") {
			fin >> data;
		}

		// ignore the other lines
		fin.close();

		// parse the graph
		from_g6_string(data, g);
		return true;
	}

	bool read(const string& filename, vector<uugraph>& gs) {
		return read(filename.c_str(), gs);
	}

	bool read(const char *filename, vector<uugraph>& gs) {
		ifstream fin;
		fin.open(filename);
		if (not fin.is_open()) {
			return false;
		}

		// Bear in mind that the file may contain
		// several lines, but only one will be read.

		string data = "";
		while (data == "" or data == ">>graph6<<") {
			fin >> data;
		}

		do {
			uugraph g;
			from_g6_string(data, g);
			gs.push_back(g);
		}
		while (fin >> data);

		fin.close();
		return true;
	}

	// -- WRITING --

	bool write(const string& filename, const uugraph& g) {
		return write(filename.c_str(), g);
	}

	bool write(const char *filename, const uugraph& g) {
		// open file in append mode (ios_base::app)
		ofstream fout;
		fout.open(filename, ios_base::app);
		if (not fout.is_open()) {
			return false;
		}

		// convert
		string data;
		to_g6_string(g, data);

		// write
		fout << data << std::endl;
		fout.close();

		return true;
	}

} // -- namespace graph6
} // -- namespace io
} // -- namespace lgraph
