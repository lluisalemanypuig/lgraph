#include <lgraph/io/edge_list.hpp>

namespace lgraph {
namespace io {
namespace edge_list {

	// -- READING --

	bool read(const string& filename, uxgraph *g) {
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

	bool write(const string& filename, const uxgraph *g) {
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

}
}
}
