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

void read_graph(graph& G) {
	size_t n_nodes;
	cin >> n_nodes;

	G.init(n_nodes);

	size_t n_edges;
	cin >> n_edges;
	for (size_t i = 0; i < n_edges; ++i) {
		node u, v;
		cin >> u >> v;
		G.add_edge(u, v);
	}
}

void deb_distances(const graph& G, size_t source, size_t target) {
	const size_t N = G.n_nodes();
	logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

	LOG.log() << "DISTANCES:" << endl;

	// vertex-vertex
	size_t d = distance(G, source, target);
	LOG.log() << "- node to node" << endl;
	LOG.log() << "    Distance from " << source << " to " << target << ": ";
	if (d == utils::inf) LOG.log() << "-1";
	else LOG.log() << d;
	LOG.log() << endl;

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

void deb_paths(const graph& G, size_t source, size_t target) {
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

int main(int argc, char *argv[]) {
	graph G;
	read_graph(G);
	cout << G << endl;

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
	}

	deb_distances(G, S, T);
	//deb_paths(G, S, T);
}

