#include "functions.hpp"

#include <lgraph/graph_traversal/traversal_wx.hpp>
#include <lgraph/data_structures/node_path.hpp>

namespace functions {

	template<class T>
	void deb_distances_t(const wxgraph<T> *G, node source, node target) {
		const T N = G->n_nodes();
		cout << "DISTANCES:" << endl;

		// node-node
		cout << "- node to node" << endl;
		size_t n_paths;
		T d1 = traversal::wxdistance(G, source, target);
		T d2 = traversal::wxdistance(G, source, target, n_paths);
		cout << "    Distance from " << source << " to " << target << ": ";
		if (d1 == inf_t<T>() or d2 == inf_t<T>()) {
			cout << "inf";
		}
		else {
			cout << d1 << " -- " << d2;
			if (d1 != d2) {
				cout << " distances disagree! " << endl;
			}
		}
		cout << " (" << n_paths << ")" << endl;

		// node-all
		cout << "- node to all" << endl;
		vector<T> ds;
		vector<size_t> va_n_paths;
		traversal::wxdistance<T>(G, source, ds, va_n_paths);
		if (va_n_paths.size() > 0) {
			for (size_t i = 0; i < N; ++i) {
				cout << "    Distance from " << source << " to " << i << ": ";
				if (ds[i] == inf_t<T>()) {
					cout << "inf";
				}
				else {
					cout << ds[i] << " (" << va_n_paths[i] << ")";
				}
				cout << endl;
			}
		}
		else {
			cout << "EMPTY!" << endl;
		}

		// all-all
		vector<vector<T> > all_ds;
		vector<vector<size_t> > all_n_paths;
		traversal::wxdistances(G, all_ds, all_n_paths);
		cout << "- all to all" << endl;
		print_distance_matrix(all_ds, all_n_paths);
	}

	template<class T>
	void deb_paths_t(const wxgraph<T> *G, node source, node target) {
		cout << "SINGLE NODE PATHS:" << endl;

		// node-node
		cout << "- node to node" << endl;
		node_path<T> p;
		traversal::wxpath(G, source, target, p);
		cout << "    Path from " << source << " to " << target << ": ";
		if (p.size() > 0) {
			cout << p;
		}
		else {
			cout << "No path!";
		}
		cout << endl;

		// node-all
		cout << "- node to all" << endl;
		vector<node_path<T> > ps;
		traversal::wxpath(G, source, ps);
		if (ps.size() > 0) {
			for (node target = 0; target < G->n_nodes(); ++target) {
				cout << "    Path from " << source << " to " << target << ": ";
				if (ps[target].size() > 0) {
					cout << ps[target];
				}
				else {
					cout << "No path!";
				}
				cout << endl;
			}
		}
		else {
			cout << "EMPTY!" << endl;
		}

		// all-all
		cout << "- all to all" << endl;
		vector<node_path_set<T> > all_ps;
		traversal::wxpath(G, all_ps);
		if (all_ps.size() > 0) {
			for (node source = 0; source < G->n_nodes(); ++source) {
				for (node target = 0; target < G->n_nodes(); ++target) {
					cout << "    Path from " << source << " to " << target << ": ";
					if (all_ps[source][target].size() > 0) {
						cout << all_ps[source][target];
					}
					else {
						cout << "No path!";
					}
					cout << endl;
				}
			}
		}
		else {
			cout << "    EMPTY!" << endl;
		}
	}

	template<class T>
	void deb_all_paths_t(const wxgraph<T> *G, node source, node target) {
		cout << "ALL NODE SHORTEST PATHS:" << endl;

		// node-node
		cout << "- node to node" << endl;
		node_path_set<T> node_node_ps;
		traversal::wxpaths(G, source, target, node_node_ps);
		cout << "    paths from " << source << " to " << target << ": ";
		if (node_node_ps.size() == 0) {
			cout << "No paths" << endl;
		}
		else {
			cout << endl;
			for (const node_path<T>& path : node_node_ps) {
				cout << "        " << path << endl;
			}
		}

		// node-all
		cout << "- node to all" << endl;
		vector<node_path_set<T> > node_all_ps;
		traversal::wxpaths(G, source, node_all_ps);
		for (node target = 0; target < G->n_nodes(); ++target) {
			cout << "    Paths from " << source << " to " << target << ": ";
			const node_path_set<T>& paths_to_target = node_all_ps[target];
			if (paths_to_target.size() == 0) {
				cout << "No paths" << endl;
			}
			else {
				cout << endl;
				for (const node_path<T>& path : paths_to_target) {
					cout << string(8, ' ') << path << endl;
				}
			}
		}

		// all-all
		cout << "- all to all" << endl;
		vector<vector<node_path_set<T> > > all_all_paths;
		traversal::wxpaths(G, all_all_paths);
		for (node source = 0; source < G->n_nodes(); ++source) {
			for (node target = 0; target < G->n_nodes(); ++target) {

				cout << "    Paths from " << source << " to " << target << ": ";
				const node_path_set<T>& paths_to_target = all_all_paths[source][target];
				if (paths_to_target.size() == 0) {
					cout << "No paths" << endl;
				}
				else {
					cout << endl;
					for (const node_path<T>& path : paths_to_target) {
						cout << string(8, ' ') << path << endl;
					}
				}
			}
		}
	}

	template<class T>
	void deb_bpaths_t(const wxgraph<T> *G, node source, node target) {
		cout << "SINGLE BOOLEAN PATHS:" << endl;

		// node-node
		cout << "- node to node" << endl;
		boolean_path<T> p;
		traversal::wxpath(G, source, target, p);
		cout << "    Path from " << source << " to " << target << ": ";
		if (p.size() > 0) {
			cout << p.to_node_path(G, source);
		}
		else {
			cout << "No path!";
		}
		cout << endl;

		// node-all
		cout << "- node to all" << endl;
		vector<boolean_path<T> > ps;
		traversal::wxpath(G, source, ps);
		for (node TARGET = 0; TARGET < G->n_nodes(); ++TARGET) {
			cout << "    Path from " << source << " to " << TARGET << ": ";
			if (ps[TARGET].size() > 0) {
				cout << ps[TARGET].to_node_path(G, source);
			}
			else {
				cout << "No path!";
			}
			cout << endl;
		}

		// all-all
		cout << "- all to all" << endl;
		vector<vector<boolean_path<T> > > all_ps;
		traversal::wxpath(G, all_ps);
		for (node SOURCE = 0; SOURCE < G->n_nodes(); ++SOURCE) {
			for (node TARGET = 0; TARGET < G->n_nodes(); ++TARGET) {
				cout << "    Path from " << SOURCE << " to " << TARGET << ": ";
				if (all_ps[SOURCE][TARGET].size() > 0) {
					cout << all_ps[SOURCE][TARGET].to_node_path(G, SOURCE);
				}
				else {
					cout << "No path!";
				}
				cout << endl;
			}
		}
	}

	template<class T>
	void deb_all_bpaths_t(const wxgraph<T> *G, node source, node target) {
		cout << "ALL BOOLEAN SHORTEST PATHS:" << endl;

		// node-node
		cout << "- node to node" << endl;
		boolean_path_set<T> node_node_paths;
		traversal::wxpaths(G, source, target, node_node_paths);
		cout << "    paths from " << source << " to " << target << ": ";
		if (node_node_paths.size() == 0) {
			cout << "No paths" << endl;
		}
		else {
			cout << endl;
			for (const boolean_path<T>& path : node_node_paths) {
				cout << "        " << path.to_node_path(G, source) << endl;
			}
		}

		// node-all
		cout << "- node to all" << endl;
		vector<boolean_path_set<T> > node_all_paths;
		traversal::wxpaths(G, source, node_all_paths);
		for (node TARGET = 0; TARGET < G->n_nodes(); ++TARGET) {
			cout << "    Paths from " << source << " to " << TARGET << ": ";
			const boolean_path_set<T>& paths_to_target = node_all_paths[TARGET];
			if (paths_to_target.size() == 0) {
				cout << "No paths" << endl;
			}
			else {
				cout << endl;
				for (const boolean_path<T>& path : paths_to_target) {
					cout << string(8, ' ') << path.to_node_path(G, source) << endl;
				}
			}
		}

		// all-all
		cout << "- all to all" << endl;
		vector<vector<boolean_path_set<T> > > all_all_paths;
		traversal::wxpaths(G, all_all_paths);
		for (node SOURCE = 0; SOURCE < G->n_nodes(); ++SOURCE) {
			for (node TARGET = 0; TARGET < G->n_nodes(); ++TARGET) {

				cout << "    Paths from " << SOURCE << " to " << TARGET << ": ";
				const boolean_path_set<T>& paths_to_target = all_all_paths[SOURCE][TARGET];
				if (paths_to_target.size() == 0) {
					cout << "No paths" << endl;
				}
				else {
					cout << endl;
					for (const boolean_path<T>& path : paths_to_target) {
						cout << string(8, ' ') << path.to_node_path(G, SOURCE) << endl;
					}
				}
			}
		}
	}

}
