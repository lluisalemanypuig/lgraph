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
