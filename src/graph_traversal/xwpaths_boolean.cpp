#include "traversal.hpp"

namespace dsa {
namespace traversal {

	/// VERTEX-VERTEX

	template<class T>
	void path(const xxgraph<T> *G, node source, node target, boolean_path<T>& p) {
		node_path<T> path;
		xwpath(G, source, target, path);
		p.init(G->n_nodes(), path);
	}

	template<class T>
	void path(const xxgraph<T> *G, node source, node target, boolean_path_set<T>& ps) {
		vector<boolean_path_set<T> > boolean_all_paths;
		xupaths(G, source, boolean_all_paths);
		ps = boolean_all_paths[target];
	}

	/// VERTEX-ALL

	template<class T>
	void path(const xxgraph<T> *G, node source, vector<boolean_path<T> >& ps) {
		vector<node_path<T> > nps;
		xupath(G, source, nps);
		for (const node_path<T>& p : nps) {
			ps.push_back(boolean_path<T>());
			ps.back().init(G->n_nodes(), p);
		}
	}

	template<class T>
	void path(const xxgraph<T> *G, node source, vector<boolean_path_set<T> >& ps) {
		const size_t N = G->n_nodes();

		vector<node_path_set<T> > node_ps;
		xupaths(G, source, node_ps);

		ps = vector<boolean_path_set<T> >(N);
		for (size_t i = 0; i < N; ++i) {
			from_nps_to_bps(node_ps[i], N, ps[i]);
		}
	}

	/// ALL-ALL

	template<class T>
	void paths(const xxgraph<T> *G, vector<boolean_path_set<T> >& all_all_paths) {
		const size_t N = G->n_nodes();

		vector<node_path_set<T> > node_ps;
		xupath(G, node_ps);

		all_all_paths = vector<boolean_path_set<T> >(N);
		for (size_t i = 0; i < N; ++i) {
			from_nps_to_bps(node_ps[i], N, all_all_paths[i]);
		}
	}

	template<class T>
	void paths(const xxgraph<T> *G, vector<vector<boolean_path_set<T> > >& all_all_paths) {
		const size_t N = G->n_nodes();

		vector<vector<node_path_set<T> > > all_all_node_paths;
		xupaths(G, all_all_node_paths);

		all_all_paths = vector<vector<boolean_path_set<T> > >(N, vector<boolean_path_set<T> >(N));

		for (size_t i = 0; i < N; ++i) {
			for (size_t j = 0; j < N; ++j) {
				from_nps_to_bps(all_all_node_paths[i][j], N, all_all_paths[i][j]);
			}
		}
	}

} // -- namespace traversal
} // -- namespace dsa
