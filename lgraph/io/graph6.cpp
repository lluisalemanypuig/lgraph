/*********************************************************************
 * lgraph
 * Copyright (C) 2018-2019 Lluís Alemany Puig
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Contact: Lluís Alemany Puig (lluis.alemany.puig@gmail.com)
 * 
 ********************************************************************/

#include <lgraph/io/gsd6.hpp>

// C++ includes
#include <iostream>
#include <limits>
using namespace std;

// lgraph includes
#include <lgraph/utils/static_bitset.hpp>

namespace lgraph {
using namespace utils;

namespace io {
namespace graph6 {

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
#define SIZE_T_TO_BIN6(b,p)									\
	((b & (size_t(0x01) << size_t(p))) >> size_t(p))	|	\
	((b & (size_t(0x02) << size_t(p))) >> size_t(p))	|	\
	((b & (size_t(0x04) << size_t(p))) >> size_t(p))	|	\
	((b & (size_t(0x08) << size_t(p))) >> size_t(p))	|	\
	((b & (size_t(0x10) << size_t(p))) >> size_t(p))	|	\
	((b & (size_t(0x20) << size_t(p))) >> size_t(p))

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

bool from_g6_string(const std::string& data, uugraph& g) {
	// error control: if the format of the string is not
	// for graph6, stop

	gsd6_format format;
	string header;
	char del;
	size_t k = 0; // first character of 'actual' data

	bool r = gsd6_string_format(data, format, header, del, k);
	if (not r) {
		return false;
	}

	if (format != gsd6_format::Graph6) {
		cerr << "lgraph::io::graph6::from_g6_string - Error:" << endl;
		cerr << "    string passed as parameter is not in graph6 format." << endl;
		cerr << "    Format is: ";
		if (format == gsd6_format::Sparse6) {
			cerr << "sparse6" << endl;
		}
		if (format == gsd6_format::Incremental_Sparse6) {
			cerr << "incremental sparse6" << endl;
		}
		if (format == gsd6_format::DiGraph6) {
			cerr << "digraph6" << endl;
		}
		return false;
	}

	// retrieve number of vertices
	size_t n;
	if (data[k] != 0x7e) {
		// 0 <= n <= 62
		n = size_t(data[k] - 63);
		++k;
	}
	else {
		++k;
		if (data[k] != 0x7e) {
			// 63 <= n <= 258047
			n = THREE_BIN6_TO_SIZE_T(data[k],data[k+1],data[k+2]);
			k += 3;
		}
		else {
			// 258048 <= n <= 68,719,476,735

			if (uint64_t(numeric_limits<size_t>::max()) <= uint64_t(68719476735)) {
				cerr << "lgraph::io::graph6::from_g6_string - Warning:" << endl;
				cerr << "    The amount of nodes will be read into a 'size_t' type" << endl;
				cerr << "    which, in your system, may not be large enough to fit" << endl;
				cerr << "    the value equal to the amount of vertices of the graph." << endl;
				cerr << "    The maximum amount of vertices allowed in graph6 is:" << endl;
				cerr << "        68719476735" << endl;
				cerr << "    Your 'size_t' can hold up to:" << endl;
				cerr << "        " << numeric_limits<size_t>::max() << endl;
			}

			++k;
			n = SIX_BIN6_TO_SIZE_T(data[k],data[k+1],data[k+2],
								data[k+3],data[k+4],data[k+5]);
			k += 6;
		}
	}

	// clear and initialise graph
	g.clear();
	g.init(n);

	char byte = data[k] - 63;
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
				if (k < data.length()) {
					byte = data[k] - 63;
				}
				mask = 0x20;
			}
		}
	}

	return true;
}

void to_g6_string(const uugraph& g, std::string& s) {
	size_t N = g.n_nodes();

	// put header into the string
	s = graph6_header();

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

	/* Convert the upper triangular matrix of the adjacency matrix
	 * into a string of bits.
	 */

	// size of the upper triangular submatrix
	size_t n_cells = (N%2 == 0 ? (N/2)*(N - 1) : ((N - 1)/2)*N);
	/* Note to self: this computation of 'n_cells' is clearly unnecessary.
	 * The result could be calculated using (N*(N-1))/2, without worrying
	 * about the result of the division since N*(N - 1) is always an even
	 * number. However, since N may be really large, the product N*(N - 1)
	 * may overflow hence giving wrong results. The computation above is
	 * an attempt to obtain a safer computation.
	 */

	// bits needed for the adjacency matrix
	size_t n_bits = n_cells + (n_cells/6)*2;

	static_bitset bs;
	bs.init_unset(n_bits);

	for (node u = 0; u < N; ++u) {
		const neighbourhood& Nu = g.get_neighbours(u);
		for (node v : Nu) {
			if (u < v) {
				size_t base_idx = (v%2 == 0 ? (v/2)*(v - 1) : ((v - 1)/2)*v);
				/* Note to self: the computation of 'base_idx' is similar to
				 * that of 'n_cells'. If this computation looks weird read
				 * the comments below 'n_cells' for an explanation.
				 */

				size_t idx = base_idx + u;
				size_t bit = idx + (idx/6 + 1)*2;
				bs.set_bit(bit);
			}
		}
	}

	// make characters printable
	bs += 63;

	// 'Store' the edges of the graph.
	bs.append_bytes(s);
}

// -- READING --

bool read(const std::string& filename, uugraph& g) {
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

	// skip empty lines
	string data = "";
	do {
		getline(fin, data);
	}
	while (data == "");

	// ignore the other lines
	fin.close();

	// parse the graph
	return from_g6_string(data, g);
}

bool read(const std::string& filename, std::vector<uugraph>& gs) {
	return read(filename.c_str(), gs);
}

bool read(const char *filename, std::vector<uugraph>& gs) {
	ifstream fin;
	fin.open(filename);
	if (not fin.is_open()) {
		return false;
	}

	// skip empty lines
	size_t lineno = 0;
	string data = "";
	do {
		getline(fin, data);
		++lineno;
	}
	while (data == "");

	// read all graphs and store them in the vector
	do {
		uugraph g;
		if (not from_g6_string(data, g)) {
			cerr << "    In line " << lineno << " of file '"
				 << string(filename) << endl;
			return false;
		}
		gs.push_back(g);
		++lineno;
	}
	while (getline(fin, data));

	fin.close();
	return true;
}

// -- WRITING --

bool write(const std::string& filename, const uugraph& g) {
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
