#include "debug.hpp"

namespace debug {

	void deb_distances(const xxgraph<_new_> *G, node source, node target) {
		const _new_ N = G->n_nodes();
		logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

		LOG.log() << "DISTANCES:" << endl;

		// vertex-vertex
		size_t n_paths;
		_new_ d1 = traversal::xudistance(G, source, target);
		_new_ d2 = traversal::xudistance(G, source, target, n_paths);
		LOG.log() << "- node to node" << endl;
		LOG.log() << "    Distance from " << source << " to " << target << ": ";
		if (d1 == utils::inf_t<_new_>() or d2 == utils::inf_t<_new_>()) LOG.log() << "inf";
		else {
			LOG.log() << d1 << " -- " << d2;
			if (d1 != d2) {
				cout << " distances disagree! " << endl;
			}
		}
		LOG.log() << " (" << n_paths << ")" << endl;

		// vertex-all
		vector<_new_> ds;
		vector<size_t> va_n_paths;
		traversal::xudistance(G, source, ds, va_n_paths);
		LOG.log() << "- node to all" << endl;
		for (size_t i = 0; i < N; ++i) {
			LOG.log() << "    Distance from " << source << " to " << i << ": ";
			if (ds[i] == utils::inf_t<_new_>()) LOG.log() << "inf";
			else LOG.log() << ds[i] << " (" << va_n_paths[i] << ")";
			LOG.log() << endl;
		}

		// all-all
		vector<vector<_new_> > all_ds;
		vector<vector<size_t> > all_n_paths;
		traversal::xudistances(G, all_ds, all_n_paths);
		LOG.log() << "- all to all" << endl;
		print_distance_matrix(all_ds, all_n_paths);
	}

	void deb_paths(const xxgraph<_new_> *G, node source, node target) {
		logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

		LOG.log() << "SINGLE NODE PATHS:" << endl;

		// vertex-vertex
		node_path<_new_> p;
		traversal::xupath(G, source, target, p);
		LOG.log() << "- node to node" << endl;
		LOG.log() << "    Path from " << source << " to " << target << ": ";
		if (p.size() > 0) LOG.log() << p;
		else LOG.log() << "No path!";
		LOG.log() << endl;

		// vertex-all
		vector<node_path<_new_> > ps;
		traversal::xupath(G, source, ps);
		LOG.log() << "- node to all" << endl;
		for (node target = 0; target < G->n_nodes(); ++target) {
			LOG.log() << "    Path from " << source << " to " << target << ": ";
			if (ps[target].size() > 0) LOG.log() << ps[target];
			else LOG.log() << "No path!";
			LOG.log() << endl;
		}

		// all-all
		vector<vector<node_path<_new_> > > all_ps;
		traversal::xupaths(G, all_ps);
		LOG.log() << "- all to all" << endl;
		for (node source = 0; source < G->n_nodes(); ++source) {
			for (node target = 0; target < G->n_nodes(); ++target) {
				LOG.log() << "    Path from " << source << " to " << target << ": ";
				if (all_ps[source][target].size() > 0) LOG.log() << all_ps[source][target];
				else LOG.log() << "No path!";
				LOG.log() << endl;
			}
		}
	}

	void deb_all_paths(const xxgraph<_new_> *G, node source, node target) {
		logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

		LOG.log() << "ALL NODE SHORTEST PATHS:" << endl;

		// vertex-vertex
		node_path_set<_new_> node_node_ps;
		traversal::xupath(G, source, target, node_node_ps);
		LOG.log() << "- node to node" << endl;
		LOG.log() << "    paths from " << source << " to " << target << ": ";
		if (node_node_ps.size() == 0) {
			LOG.log() << "No paths" << endl;
		}
		else {
			LOG.log() << endl;
			for (const node_path<_new_>& path : node_node_ps) {
				LOG.log() << "        " << path << endl;
			}
		}

		// vertex-all
		vector<node_path_set<_new_> > node_all_ps;
		traversal::xupath(G, source, node_all_ps);
		LOG.log() << "- node to all" << endl;
		for (node target = 0; target < G->n_nodes(); ++target) {
			LOG.log() << "    Paths from " << source << " to " << target << ": ";
			const node_path_set<_new_>& paths_to_target = node_all_ps[target];
			if (paths_to_target.size() == 0) {
				LOG.log() << "No paths" << endl;
			}
			else {
				LOG.log() << endl;
				for (const node_path<_new_>& path : paths_to_target) {
					LOG.log() << string(8, ' ') << path << endl;
				}
			}
		}

		// all-all
		vector<vector<node_path_set<_new_> > > all_all_paths;
		traversal::xupaths(G, all_all_paths);
		LOG.log() << "- all to all" << endl;
		for (node source = 0; source < G->n_nodes(); ++source) {
			for (node target = 0; target < G->n_nodes(); ++target) {

				LOG.log() << "    Paths from " << source << " to " << target << ": ";
				const node_path_set<_new_>& paths_to_target = all_all_paths[source][target];
				if (paths_to_target.size() == 0) {
					LOG.log() << "No paths" << endl;
				}
				else {
					LOG.log() << endl;
					for (const node_path<_new_>& path : paths_to_target) {
						LOG.log() << string(8, ' ') << path << endl;
					}
				}
			}
		}
	}

	void deb_bpaths(const xxgraph<_new_> *G, node source, node target) {
		logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

		LOG.log() << "SINGLE BOOLEAN PATHS:" << endl;

		// vertex-vertex
		boolean_path<_new_> p;
		traversal::xupath(G, source, target, p);
		LOG.log() << "- node to node" << endl;
		LOG.log() << "    Path from " << source << " to " << target << ": ";
		if (p.size() > 0) LOG.log() << p.to_node_path(G, source);
		else LOG.log() << "No path!";
		LOG.log() << endl;

		// vertex-all
		vector<boolean_path<_new_> > ps;
		traversal::xupath(G, source, ps);
		LOG.log() << "- node to all" << endl;
		for (node TARGET = 0; TARGET < G->n_nodes(); ++TARGET) {
			LOG.log() << "    Path from " << source << " to " << TARGET << ": ";
			if (ps[TARGET].size() > 0) LOG.log() << ps[TARGET].to_node_path(G, source);
			else LOG.log() << "No path!";
			LOG.log() << endl;
		}

		// all-all
		vector<vector<boolean_path<_new_> > > all_ps;
		traversal::xupaths(G, all_ps);
		LOG.log() << "- all to all" << endl;
		for (node SOURCE = 0; SOURCE < G->n_nodes(); ++SOURCE) {
			for (node TARGET = 0; TARGET < G->n_nodes(); ++TARGET) {
				LOG.log() << "    Path from " << SOURCE << " to " << TARGET << ": ";
				if (all_ps[SOURCE][TARGET].size() > 0) LOG.log() << all_ps[SOURCE][TARGET].to_node_path(G, SOURCE);
				else LOG.log() << "No path!";
				LOG.log() << endl;
			}
		}
	}

	void deb_all_bpaths(const xxgraph<_new_> *G, node source, node target) {
		logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

		LOG.log() << "ALL BOOLEAN SHORTEST PATHS:" << endl;

		// vertex-vertex
		boolean_path_set<_new_> node_node_paths;
		traversal::xupath(G, source, target, node_node_paths);
		LOG.log() << "- node to node" << endl;
		LOG.log() << "    paths from " << source << " to " << target << ": ";
		if (node_node_paths.size() == 0) {
			LOG.log() << "No paths" << endl;
		}
		else {
			LOG.log() << endl;
			for (const boolean_path<_new_>& path : node_node_paths) {
				LOG.log() << "        " << path.to_node_path(G, source) << endl;
			}
		}

		// vertex-all
		vector<boolean_path_set<_new_> > node_all_paths;
		traversal::xupath(G, source, node_all_paths);
		LOG.log() << "- node to all" << endl;
		for (node TARGET = 0; TARGET < G->n_nodes(); ++TARGET) {
			LOG.log() << "    Paths from " << source << " to " << TARGET << ": ";
			const boolean_path_set<_new_>& paths_to_target = node_all_paths[TARGET];
			if (paths_to_target.size() == 0) {
				LOG.log() << "No paths" << endl;
			}
			else {
				LOG.log() << endl;
				for (const boolean_path<_new_>& path : paths_to_target) {
					LOG.log() << string(8, ' ') << path.to_node_path(G, source) << endl;
				}
			}
		}

		// all-all
		vector<vector<boolean_path_set<_new_> > > all_all_paths;
		traversal::xupaths(G, all_all_paths);
		LOG.log() << "- all to all" << endl;
		for (node SOURCE = 0; SOURCE < G->n_nodes(); ++SOURCE) {
			for (node TARGET = 0; TARGET < G->n_nodes(); ++TARGET) {

				LOG.log() << "    Paths from " << SOURCE << " to " << TARGET << ": ";
				const boolean_path_set<_new_>& paths_to_target = all_all_paths[SOURCE][TARGET];
				if (paths_to_target.size() == 0) {
					LOG.log() << "No paths" << endl;
				}
				else {
					LOG.log() << endl;
					for (const boolean_path<_new_>& path : paths_to_target) {
						LOG.log() << string(8, ' ') << path.to_node_path(G, SOURCE) << endl;
					}
				}
			}
		}
	}

}
