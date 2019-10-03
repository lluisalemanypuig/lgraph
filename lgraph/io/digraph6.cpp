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

namespace lgraph {
namespace io {
namespace digraph6 {

// -- READING --

bool read(const std::string& filename, udgraph& g) {
	return read(filename.c_str(), g);
}

bool read(const char *filename, udgraph& g) {
	return true;
}

// -- WRITING --

bool write(const std::string& filename, const udgraph& g) {
	return write(filename.c_str(), g);
}

bool write(const char *filename, const udgraph& g) {
	return true;
}

} // -- namespace digraph6
} // -- namespace io
} // -- namespace lgraph

