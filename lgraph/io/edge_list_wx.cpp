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

namespace lgraph {
namespace io {
namespace edge_list {

// -- READING --

template<class T>
bool read(const std::string& filename, wxgraph<T> *g) {
	return read(filename.c_str(), g);
}

template<class T>
bool read(const char *filename, wxgraph<T> *g) {
	std::ifstream fin;
	fin.open(filename);
	if (not fin.is_open()) {
		return false;
	}

	size_t max_vert_idx = 0;
	std::vector<edge> edge_list;
	std::vector<T> weights;
	size_t u, v;
	T w;
	while (fin >> u >> v) {
		fin >> w;
		edge_list.push_back(edge(u, v));
		weights.push_back(w);
		max_vert_idx = std::max(max_vert_idx, u);
		max_vert_idx = std::max(max_vert_idx, v);
	}
	fin.close();

	g->init(max_vert_idx + 1);
	g->add_edges(edge_list, weights);
	return true;
}

// -- READING --

template<class T>
bool write(const std::string& filename, const wxgraph<T> *g) {
	return write(filename.c_str(), g);
}

template<class T>
bool write(const char *filename, const wxgraph<T> *g) {
	std::ofstream fout;
	fout.open(filename);
	if (not fout.is_open()) {
		return false;
	}

	std::vector<std::pair<edge, T> > all_edges;
	g->edges(all_edges);

	for (auto& p : all_edges) {
		fout << p.first.first << " "
			 << p.first.second << " "
			 << p.second
			 << std::endl;
	}

	fout.close();
	return true;
}

} // -- namespace edge_list
} // -- namespace io
} // -- namespace lgraph
