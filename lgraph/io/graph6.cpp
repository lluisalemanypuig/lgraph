#include <lgraph/io/gsd6.hpp>

#include <limits>

namespace lgraph {
namespace io {
namespace graph6 {

	// k is in big endian.
	// Convert the first 6 bits of 'k' into
	// a decimal number considering that the
	// first bit starts at power p
	#define BIN6_TO_DEC(k,p)				\
		(size_t(k & 0x01) << size_t(p)) +	\
		(size_t(k & 0x02) << size_t(p)) +	\
		(size_t(k & 0x04) << size_t(p)) +	\
		(size_t(k & 0x08) << size_t(p)) +	\
		(size_t(k & 0x10) << size_t(p)) +	\
		(size_t(k & 0x20) << size_t(p))

	#define THREE_BIN6_TO_DEC(a,b,c)	\
		BIN6_TO_DEC((a - 63),12) +		\
		BIN6_TO_DEC((b - 63), 6) +		\
		BIN6_TO_DEC((c - 63), 0)
	#define SIX_BIN6_TO_DEC(a,b,c,d,e,f)\
		BIN6_TO_DEC((a - 63),30) +		\
		BIN6_TO_DEC((b - 63),24) +		\
		BIN6_TO_DEC((c - 63),18) +		\
		BIN6_TO_DEC((d - 63),12) +		\
		BIN6_TO_DEC((e - 63), 6) +		\
		BIN6_TO_DEC((f - 63), 0)

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
				n = THREE_BIN6_TO_DEC(s[k],s[k+1],s[k+2]);
				k += 3;
			}
			else {
				if (uint64_t(numeric_limits<size_t>::max()) <= uint64_t(68719476735)) {
					cerr << "Warning: when parsing graph in graph6 format." << endl;
					cerr << "    The amount of nodes will be read into a 'size_t' type" << endl;
					cerr << "    which, in your system, may not have enough precision" << endl;
					cerr << "    to fit the maximum amount of vertices of your graph." << endl;
					cerr << "    The maximum amount of vertices allowed in graph6 is:" << endl;
					cerr << "        68719476735" << endl;
					cerr << "    Your 'size_t' can hold up to:" << endl;
					cerr << "        " << numeric_limits<size_t>::max() << endl;
				}

				++k;
				// 258048 <= n <= 68,719,476,735
				n = SIX_BIN6_TO_DEC(s[k],s[k+1],s[k+2],
									s[k+3],s[k+4],s[k+5]);
				k += 6;
			}
		}

		// initialise graph
		g.init(n);

		char byte = s[k] - 63;
		char mask = 0x20;
		char bit_idx = 5;	// skip the first two bits

		for (size_t j = 1; j < n; ++j) {
			for (size_t i = 0; i < j; ++i) {
				if ((byte & mask) != 0) {
					g.add_edge(i, j);
				}

				--bit_idx;
				mask >>= 1;

				// skip the first two bits of each byte
				if (bit_idx == 0) {
					bit_idx = 5;
					byte = s[++k] - 63;
					mask = 0x20;
				}
			}
		}
	}

	void to_g6_string(const uugraph& g, string& s) {

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
		fout << data << endl;
		fout.close();

		return true;
	}

} // -- namespace graph6
} // -- namespace io
} // -- namespace lgraph
