#include "traversal.hpp"

namespace lgraph {
namespace traversal {

	/// VERTEX-VERTEX

	// one path
	void xupath(const xxgraph<_new_> *G, node source, node target, boolean_path<_new_>& p) {
		node_path<_new_> path;
		xupath(G, source, target, path);
		p.init(G->n_nodes(), path);
	}

	// all paths
	void xupaths(const xxgraph<_new_> *G, node source, node target, boolean_path_set<_new_>& ps) {
		node_path_set<_new_> node_all_paths;
		xupaths(G, source, target, node_all_paths);
		from_nps_to_bps(node_all_paths, G->n_nodes(), ps);
	}

	/// VERTEX-ALL

	// one path
	void xupath(const xxgraph<_new_> *G, node source, vector<boolean_path<_new_> >& ps) {
		vector<node_path<_new_> > nps;
		xupath(G, source, nps);
		for (const node_path<_new_>& p : nps) {
			ps.push_back(boolean_path<_new_>());
			ps.back().init(G->n_nodes(), p);
		}
	}

	// all paths
	void xupaths(const xxgraph<_new_> *G, node source, vector<boolean_path_set<_new_> >& ps) {
		const size_t N = G->n_nodes();

		vector<node_path_set<_new_> > node_ps;
		xupaths(G, source, node_ps);

		ps = vector<boolean_path_set<_new_> >(N);
		for (size_t i = 0; i < N; ++i) {
			from_nps_to_bps(node_ps[i], N, ps[i]);
		}
	}

	/// ALL-ALL

	// one path
	void xupath(const xxgraph<_new_> *G, vector<boolean_path_set<_new_> >& all_all_paths) {
		const size_t N = G->n_nodes();

		vector<node_path_set<_new_> > node_ps;
		xupath(G, node_ps);

		all_all_paths = vector<boolean_path_set<_new_> >(N);
		for (size_t i = 0; i < N; ++i) {
			from_nps_to_bps(node_ps[i], N, all_all_paths[i]);
		}
	}

	// all paths
	void xupaths(const xxgraph<_new_> *G, vector<vector<boolean_path_set<_new_> > >& all_all_paths) {
		const size_t N = G->n_nodes();

		vector<vector<node_path_set<_new_> > > all_all_node_paths;
		xupaths(G, all_all_node_paths);

		all_all_paths = vector<vector<boolean_path_set<_new_> > >(N, vector<boolean_path_set<_new_> >(N));

		for (size_t i = 0; i < N; ++i) {
			for (size_t j = 0; j < N; ++j) {
				from_nps_to_bps(all_all_node_paths[i][j], N, all_all_paths[i][j]);
			}
		}
	}

} // -- namespace traversal
} // -- namespace dsa
