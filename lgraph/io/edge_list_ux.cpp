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

#include <lgraph/io/edge_list_ux.hpp>

// C++ includes
#include <fstream>
using namespace std;

namespace lgraph {
namespace io {
namespace edge_list {

// -- READING --

bool read(const std::string& filename, uxgraph *g) {
	return read(filename.c_str(), g);
}

bool read(const char *filename, uxgraph *g) {
	ifstream fin;
	fin.open(filename);

	// file could not be opened. return "error"
	if (not fin.is_open()) {
		return false;
	}

	size_t max_vert_idx = 0;
	vector<edge> edge_list;
	size_t u, v;
	while (fin >> u >> v) {
		edge_list.push_back(edge(u, v));
		max_vert_idx = max(max_vert_idx, u);
		max_vert_idx = max(max_vert_idx, v);
	}
	fin.close();

	g->init(max_vert_idx + 1);
	g->add_edges(edge_list);
	return true;
}

// -- WRITING --

bool write(const std::string& filename, const uxgraph *g) {
	return write(filename.c_str(), g);
}

bool write(const char *filename, const uxgraph *g) {
	ofstream fout;
	fout.open(filename);

	// file could not be opened. return "error"
	if (not fout.is_open()) {
		return false;
	}

	// obtain list of unique edges and
	// store them in a file
	vector<edge> unique_edges;
	g->edges(unique_edges);
	for (const edge& e : unique_edges) {
		fout << e.first << " " << e.second << endl;
	}

	fout.close();
	return true;
}

} // -- namespace edge_list
} // -- namespace io
} // -- namespace lgraph
