#include "debug.hpp"

namespace debug {

	template<class T>
	void deb_distances_t(const xxgraph<T> *G, node source, node target) {
		const T N = G->n_nodes();
		logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

		LOG.log() << "DISTANCES:" << endl;

		// vertex-vertex
		size_t n_paths;
		T d1 = traversal::xwdistance(G, source, target);
		T d2 = traversal::xwdistance(G, source, target, n_paths);
		LOG.log() << "- node to node" << endl;
		LOG.log() << "    Distance from " << source << " to " << target << ": ";
		if (d1 == utils::inf_t<T>() or d2 == utils::inf_t<T>()) LOG.log() << "inf";
		else {
			LOG.log() << d1 << " -- " << d2;
			if (d1 != d2) {
				cout << " distances disagree! " << endl;
			}
		}
		LOG.log() << " (" << n_paths << ")" << endl;

		// vertex-all
		vector<T> ds;
		vector<size_t> va_n_paths;
		traversal::xwdistance<T>(G, source, ds, va_n_paths);
		LOG.log() << "- node to all" << endl;
		for (size_t i = 0; i < N; ++i) {
			LOG.log() << "    Distance from " << source << " to " << i << ": ";
			if (ds[i] == utils::inf_t<T>()) LOG.log() << "inf";
			else LOG.log() << ds[i] << " (" << va_n_paths[i] << ")";
			LOG.log() << endl;
		}

		// all-all
		vector<vector<T> > all_ds;
		vector<vector<size_t> > all_n_paths;
		traversal::xwdistances(G, all_ds, all_n_paths);
		LOG.log() << "- all to all" << endl;
		print_distance_matrix(all_ds, all_n_paths);
	}

	template<class T>
	void deb_paths_t(const xxgraph<T> *G, node source, node target) {
		logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

		LOG.log() << "PATHS:" << endl;

		// vertex-vertex
		node_path<T> p;
		traversal::xwpath(G, source, target, p);
		LOG.log() << "- node to node" << endl;
		LOG.log() << "    Path from " << source << " to " << target << ": ";
		if (p.size() > 0) LOG.log() << p;
		else LOG.log() << "No path!";
		LOG.log() << endl;

		/*
		// all vertex-vertex paths
		node_path_set<T> vv_path;
		path(G, source, target, vv_path);
		LOG.log() << "- node to node" << endl;
		LOG.log() << "    All paths from " << source << " to " << target << ": ";
		if (vv_path.size() > 0) {
			for (const node_path<T>& np : vv_path) {
				LOG.log() << np << endl;
			}
		}
		else LOG.log() << "No path!";
		LOG.log() << endl;
		*/

		// vertex-all
		vector<node_path<T> > ps;
		traversal::xwpath(G, source, ps);
		LOG.log() << "- node to all" << endl;
		for (node target = 0; target < G->n_nodes(); ++target) {
			LOG.log() << "    Path from " << source << " to " << target << ": ";
			if (ps[target].size() > 0) LOG.log() << ps[target];
			else LOG.log() << "No path!";
			LOG.log() << endl;
		}

		/*
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
		*/
	}

	template<class T>
	void deb_all_paths_t(const xxgraph<T> *G, node source, node target) {
		/*
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
		*/
	}

	template<class T>
	void deb_bpaths_t(const xxgraph<T> *G, node source, node target) {
		/*
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
		*/
	}

	template<class T>
	void deb_all_bpaths_t(const xxgraph<T> *G, node source, node target) {
		/*
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
		*/
	}

}
