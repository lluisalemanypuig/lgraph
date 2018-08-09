#include "traversal.hpp"

namespace lgraph {
namespace traversal {

	/* VERTEX-VERTEX */

	// one path
	template<class T>
	void wxpath(const wxgraph<T> *G, node source, node target, boolean_path<T>& p) {
		node_path<T> path;
		wxpath(G, source, target, path);
		p.init(G->n_nodes(), path);
	}

	// all paths
	template<class T>
	void wxpaths(const wxgraph<T> *G, node source, node target, boolean_path_set<T>& ps) {
		node_path_set<T> node_all_paths;
		wxpaths(G, source, target, node_all_paths);
		from_nps_to_bps(node_all_paths, G->n_nodes(), ps);
	}

	/* VERTEX-ALL */

	// one path
	template<class T>
	void wxpath(const wxgraph<T> *G, node source, vector<boolean_path<T> >& ps) {
		vector<node_path<T> > nps;
		wxpath(G, source, nps);
		for (const node_path<T>& p : nps) {
			ps.push_back(boolean_path<T>());
			ps.back().init(G->n_nodes(), p);
		}
	}

	// all paths
	template<class T>
	void wxpaths(const wxgraph<T> *G, node source, vector<boolean_path_set<T> >& ps) {
		const size_t N = G->n_nodes();

		vector<node_path_set<T> > node_ps;
		wxpaths(G, source, node_ps);

		ps = vector<boolean_path_set<T> >(N);
		for (size_t i = 0; i < N; ++i) {
			from_nps_to_bps(node_ps[i], N, ps[i]);
		}
	}

	/* ALL-ALL */

	// one path
	template<class T>
	void wxpath(const wxgraph<T> *G, vector<vector<boolean_path<T> > >& all_all_paths) {
		const size_t N = G->n_nodes();

		vector<node_path_set<T> > node_ps;
		wxpath(G, node_ps);

		all_all_paths = vector<boolean_path_set<T> >(N);
		for (size_t i = 0; i < N; ++i) {
			from_nps_to_bps(node_ps[i], N, all_all_paths[i]);
		}
	}

	// all paths
	template<class T>
	void wxpaths(const wxgraph<T> *G, vector<vector<boolean_path_set<T> > >& all_all_paths) {
		const size_t N = G->n_nodes();

		vector<vector<node_path_set<T> > > all_all_node_paths;
		wxpaths(G, all_all_node_paths);

		all_all_paths = vector<vector<boolean_path_set<T> > >(N, vector<boolean_path_set<T> >(N));

		for (size_t i = 0; i < N; ++i) {
			for (size_t j = 0; j < N; ++j) {
				from_nps_to_bps(all_all_node_paths[i][j], N, all_all_paths[i][j]);
			}
		}
	}

} // -- namespace traversal
} // -- namespace lgraph
