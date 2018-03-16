/// C includes
#include <string.h>

/// C++ includes
#include <iostream>
using namespace std;

/// Custom includes
#include "data_structures/graph.hpp"
#include "data_structures/graph_path.hpp"
#include "graph_traversal/traversal.hpp"

using namespace dsa;
using namespace traversal;

void print_distance_matrix(const vector<vector<size_t> >& dist, const vector<vector<size_t> >& n_paths) {
	logger<cout_stream>& LOG = logger<cout_stream>::get_logger();
	const size_t N = dist.size();

	const size_t max_node_length = std::to_string(N - 1).length();
	vector<size_t> max_column(N, 0);
	size_t row_width = 1;
	for (size_t u = 0; u < N; ++u) {
		for (size_t v = 0; v < N; ++v) {
			size_t length_dist = std::to_string(dist[v][u]).length();
			if (dist[v][u] == utils::inf) {
				length_dist = 2; // use '-1'
			}

			size_t n_paths_length = std::to_string(n_paths[v][u]).length();

			// '|' + ' ' + dist_length + ' ' + '(' + length_n_paths + ')'
			size_t cell_length = 1 + 1 + length_dist + 1 + 1 + n_paths_length + 1;

			max_column[u] = max(max_column[u], cell_length);
		}
		max_column[u] = max(max_column[u], 2 + std::to_string(u).length());
		row_width += max_column[u] + 1;
	}

	LOG.log() << setw(max_node_length) << " " << " ";
	for (size_t u = 0; u < N; ++u) {
		LOG.log() << left << setw(max_column[u]) << "| " + std::to_string(u) << " ";
	}
	LOG.log() << endl;

	LOG.log() << string(row_width, '-') << endl;

	setiosflags(ios::left);
	for (size_t u = 0; u < N; ++u) {
		LOG.log() << setw(max_node_length) << u << " ";
		for (size_t v = 0; v < N; ++v) {
			LOG.log() << setw(max_column[v]);

			if (dist[u][v] == utils::inf) {
				LOG.log() << "| -1 (" + std::to_string(n_paths[u][v]) + ")";
			}
			else {
				LOG.log() << "| " + std::to_string(dist[u][v]) + " (" + std::to_string(n_paths[u][v]) + ")";
			}
			LOG.log() << " ";
		}
		LOG.log() << endl;
	}
	LOG.log() << endl;
}

void deb_distances(const uugraph& G, size_t source, size_t target) {
	const size_t N = G.n_nodes();
	logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

	LOG.log() << "DISTANCES:" << endl;

	// vertex-vertex
	size_t n_paths;
	size_t d = distance(G, source, target, n_paths);
	LOG.log() << "- node to node" << endl;
	LOG.log() << "    Distance from " << source << " to " << target << ": ";
	if (d == utils::inf) LOG.log() << "-1";
	else LOG.log() << d;
	LOG.log() << " (" << n_paths << ")" << endl;

	// vertex-all
	vector<size_t> ds, va_n_paths;
	distance(G, source, ds, va_n_paths);
	LOG.log() << "- node to all" << endl;
	for (size_t i = 0; i < N; ++i) {
		LOG.log() << "    Distance from " << source << " to " << i << ": ";
		if (ds[i] == utils::inf) LOG.log() << "-1";
		else LOG.log() << ds[i] << " (" << va_n_paths[i] << ")";
		LOG.log() << endl;
	}

	// all-all
	vector<vector<size_t> > all_ds, all_n_paths;
	distances(G, all_ds, all_n_paths);
	LOG.log() << "- all to all" << endl;
	print_distance_matrix(all_ds, all_n_paths);
}

void deb_paths(const uugraph& G, size_t source, size_t target) {
	logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

	LOG.log() << "PATHS:" << endl;

	// vertex-vertex
	node_path p;
	path(G, source, target, p);
	LOG.log() << "- node to node" << endl;
	LOG.log() << "    Path from " << source << " to " << target << ": ";
	if (p.size() > 0) LOG.log() << p;
	else LOG.log() << "No path!";
	LOG.log() << endl;

	// vertex-all
	vector<node_path> ps;
	path(G, source, ps);
	LOG.log() << "- node to all" << endl;
	for (node target = 0; target < G.n_nodes(); ++target) {
		LOG.log() << "    Path from " << source << " to " << target << ": ";
		if (ps[target].size() > 0) LOG.log() << ps[target];
		else LOG.log() << "No path!";
		LOG.log() << endl;
	}

	// all-all
	vector<vector<node_path> > all_ps;
	paths(G, all_ps);
	LOG.log() << "- all to all" << endl;
	for (node source = 0; source < G.n_nodes(); ++source) {
		for (node target = 0; target < G.n_nodes(); ++target) {
			LOG.log() << "    Path from " << source << " to " << target << ": ";
			if (all_ps[source][target].size() > 0) LOG.log() << all_ps[source][target];
			else LOG.log() << "No path!";
			LOG.log() << endl;
		}
	}
}

void deb_all_paths(const uugraph& G, size_t source, size_t target) {
	logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

	LOG.log() << "ALL SHORTEST PATHS:" << endl;

	// vertex-vertex
	node_path_set node_node_ps;
	path(G, source, target, node_node_ps);
	LOG.log() << "- node to node" << endl;
	LOG.log() << "    paths from " << source << " to " << target << ": ";
	if (node_node_ps.size() == 0) {
		LOG.log() << "No paths" << endl;
	}
	else {
		LOG.log() << endl;
		for (const node_path& path : node_node_ps) {
			LOG.log() << "        " << path << endl;
		}
	}

	// vertex-all
	vector<node_path_set> node_all_ps;
	path(G, source, node_all_ps);
	LOG.log() << "- node to all" << endl;
	for (node target = 0; target < G.n_nodes(); ++target) {
		LOG.log() << "    Paths from " << source << " to " << target << ": ";
		const node_path_set& paths_to_target = node_all_ps[target];
		if (paths_to_target.size() == 0) {
			LOG.log() << "No paths" << endl;
		}
		else {
			LOG.log() << endl;
			for (const node_path& path : paths_to_target) {
				LOG.log() << string(8, ' ') << path << endl;
			}
		}
	}

	// all-all
	vector<vector<node_path_set> > all_all_paths;
	paths(G, all_all_paths);
	LOG.log() << "- all to all" << endl;
	for (node source = 0; source < G.n_nodes(); ++source) {
		for (node target = 0; target < G.n_nodes(); ++target) {

			LOG.log() << "    Paths from " << source << " to " << target << ": ";
			const node_path_set& paths_to_target = all_all_paths[source][target];
			if (paths_to_target.size() == 0) {
				LOG.log() << "No paths" << endl;
			}
			else {
				LOG.log() << endl;
				for (const node_path& path : paths_to_target) {
					LOG.log() << string(8, ' ') << path << endl;
				}
			}
		}
	}
}

void deb_bpaths(const uugraph& G, size_t source, size_t target) {
	logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

	LOG.log() << "PATHS:" << endl;

	// vertex-vertex
	boolean_path p;
	path(G, source, target, p);
	LOG.log() << "- node to node" << endl;
	LOG.log() << "    Path from " << source << " to " << target << ": ";
	if (p.size() > 0) LOG.log() << p.to_node_path(G, source);
	else LOG.log() << "No path!";
	LOG.log() << endl;

	// vertex-all
	vector<boolean_path> ps;
	path(G, source, ps);
	LOG.log() << "- node to all" << endl;
	for (node TARGET = 0; TARGET < G.n_nodes(); ++TARGET) {
		LOG.log() << "    Path from " << source << " to " << TARGET << ": ";
		if (ps[TARGET].size() > 0) LOG.log() << ps[TARGET].to_node_path(G, source);
		else LOG.log() << "No path!";
		LOG.log() << endl;
	}

	// all-all
	vector<vector<boolean_path> > all_ps;
	paths(G, all_ps);
	LOG.log() << "- all to all" << endl;
	for (node SOURCE = 0; SOURCE < G.n_nodes(); ++SOURCE) {
		for (node TARGET = 0; TARGET < G.n_nodes(); ++TARGET) {
			LOG.log() << "    Path from " << SOURCE << " to " << TARGET << ": ";
			if (all_ps[SOURCE][TARGET].size() > 0) LOG.log() << all_ps[SOURCE][TARGET].to_node_path(G, SOURCE);
			else LOG.log() << "No path!";
			LOG.log() << endl;
		}
	}
}

void deb_all_bpaths(const uugraph& G, size_t source, size_t target) {
	logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

	LOG.log() << "ALL SHORTEST PATHS:" << endl;

	// vertex-vertex
	boolean_path_set node_node_paths;
	path(G, source, target, node_node_paths);
	LOG.log() << "- node to node" << endl;
	LOG.log() << "    paths from " << source << " to " << target << ": ";
	if (node_node_paths.size() == 0) {
		LOG.log() << "No paths" << endl;
	}
	else {
		LOG.log() << endl;
		for (const boolean_path& path : node_node_paths) {
			LOG.log() << "        " << path.to_node_path(G, source) << endl;
		}
	}

	// vertex-all
	vector<boolean_path_set> node_all_paths;
	path(G, source, node_all_paths);
	LOG.log() << "- node to all" << endl;
	for (node TARGET = 0; TARGET < G.n_nodes(); ++TARGET) {
		LOG.log() << "    Paths from " << source << " to " << TARGET << ": ";
		const boolean_path_set& paths_to_target = node_all_paths[TARGET];
		if (paths_to_target.size() == 0) {
			LOG.log() << "No paths" << endl;
		}
		else {
			LOG.log() << endl;
			for (const boolean_path& path : paths_to_target) {
				LOG.log() << string(8, ' ') << path.to_node_path(G, source) << endl;
			}
		}
	}

	// all-all
	vector<vector<boolean_path_set> > all_all_paths;
	paths(G, all_all_paths);
	LOG.log() << "- all to all" << endl;
	for (node SOURCE = 0; SOURCE < G.n_nodes(); ++SOURCE) {
		for (node TARGET = 0; TARGET < G.n_nodes(); ++TARGET) {

			LOG.log() << "    Paths from " << SOURCE << " to " << TARGET << ": ";
			const boolean_path_set& paths_to_target = all_all_paths[SOURCE][TARGET];
			if (paths_to_target.size() == 0) {
				LOG.log() << "No paths" << endl;
			}
			else {
				LOG.log() << endl;
				for (const boolean_path& path : paths_to_target) {
					LOG.log() << string(8, ' ') << path.to_node_path(G, SOURCE) << endl;
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	string file = "none";

	size_t S, T;
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "--source") == 0) {
			S = atoi(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "--target") == 0) {
			T = atoi(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "-i") == 0 or strcmp(argv[i], "--input") == 0) {
			file = string(argv[i + 1]);
			++i;
		}
	}

	if (file == "none") {
		cerr << "No file specified!" << endl;
		return 1;
	}

	uugraph G;
	G.read_from_file(file);
	cout << G << endl;

	deb_distances(G, S, T);
	//deb_paths(G, S, T);
	//deb_all_paths(G, S, T);

	deb_bpaths(G, S, T);
	deb_all_bpaths(G, S, T);
}

