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
using namespace std;

// lgraph includes
#include <lgraph/utils/static_bitset.hpp>
#include <lgraph/utils/logger.hpp>

namespace lgraph {
namespace io {

bool gsd6_string_format
(const std::string& s, gsd6_format& f, std::string& header, char& c, size_t& k)
{
	// extract the optional header and the first optional character
	header = "";
	k = 0;
	if (s.substr(0,2) == ">>") {
		k = s.find("<<");
		header = s.substr(0,k + 2);
		k = k + 2;
	}

	c = s[k];
	if (
		s[k] == sparse6_first() or
		s[k] == incremental_sparse6_first() or
		s[k] == digraph6_first()
	)
	{
		++k;
	}
	else {
		c = ' ';
	}

	if (header == graph6_header()) {
		if (c == ' ') {
			f = gsd6_format::Graph6;
		}
		else {
			cerr << "lgraph::io::gsd6_string_format - Error:" << endl;
			cerr << "    Format mismatch in input string:" << endl;
			cerr << "    Starting character `" << c << "´ not valid for "
				 << "the graph6 format" << endl;
			return false;
		}
	}
	else if (header == sparse6_header()) {
		if (c == sparse6_first()) {
			f = gsd6_format::Sparse6;
		}
		else if (c == incremental_sparse6_first()) {
			f = gsd6_format::Incremental_Sparse6;
		}
		else {
			cerr << "lgraph::io::gsd6_string_format - Error:" << endl;
			cerr << "    Format mismatch in input string:" << endl;
			cerr << "    Starting character `" << c << "´ not valid for "
				 << "the sparse6 format" << endl;
			return false;
		}
	}
	else if (header == digraph6_header()) {
		if (c == digraph6_first()) {
			f = gsd6_format::DiGraph6;
		}
		else {
			cerr << "lgraph::io::gsd6_string_format - Error:" << endl;
			cerr << "    Format mismatch in input string:" << endl;
			cerr << "    Starting character `" << c << "´ not valid for "
				 << "the graph6 format" << endl;
			return false;
		}
	}
	else {
		cerr << "lgraph::io::gsd6_string_format - Error:" << endl;
		cerr << "    Header '" << header << "' not recognised as any of the" << endl;
		cerr << "    binary formats graph6, sparse6, digraph6" << endl;
		return false;
	}

	return true;
}

} // -- namespace io
} // -- namespace lgraph
