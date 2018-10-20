#include "driver.hpp"

namespace graph_driver {

	void print_weighted_options() {
		cout << "+++++++++++++++++++++++++++++++++++++" << endl;
		cout << "Options for the weighted graph driver" << endl;
		cout << "-------------------------------------" << endl;
		cout << endl;
		cout << "    For the case of undirected graphs, an edge between two nodes U and V" << endl;
		cout << "    can be denoted indistinctintly as (U,V) or (V,U). For directed graphs," << endl;
		cout << "    however, this cannot be done and the order matters. Give edges accordingly." << endl;
		cout << endl;
		cout << "    * help: show the options of this driver" << endl;
		cout << endl;
		cout << "-------------------------------------" << endl;
		cout << "MAKING A GRAPH" << endl;
		cout << endl;
		cout << "    * init N: initialise the graph with N nodes. It is needed" << endl;
		cout << "        before being able to safely add edges." << endl;
		cout << endl;
		cout << "    * add-node: add a single to the graph" << endl;
		cout << endl;
		cout << "    * add-nodes N: adds N nodes to the graph" << endl;
		cout << endl;
		cout << "    * add-edge U V W: add an edge (U,V) with weight W." << endl;
		cout << endl;
		cout << "    * add-edges N u1 v1 w1 u2 v2 w2 ... uN vN wN: add N edges. Each edge" << endl;
		cout << "        is a pair of nodes (ui,vi) and a weight wi." << endl;
		cout << endl;
		cout << "    * remove-edge U V: remove the edge (U,V)." << endl;
		cout << endl;
		cout << "    * remove-edges N u1 v1 u2 v2 ... uN vN: remove N edges. Each edge" << endl;
		cout << "        is a pair of nodes ui vi." << endl;
		cout << endl;
		cout << "    * remove-node U: remove node U from the graph." << endl;
		cout << endl;
		cout << "    * get-edge-weight U V: outputs the weight of the edge (U,V)" << endl;
		cout << endl;
		cout << "    * get-edges: prints the list of edges." << endl;
		cout << endl;
		cout << "    * set-edge-weight U V W: sets the weight of edge (U,V)" << endl;
		cout << endl;
		cout << "-------------------------------------" << endl;
		cout << "PATHS IN A GRAPH" << endl;
		cout << endl;
		cout << "    * find-one-st-path U V: finds one shortest path from node U to node V" << endl;
		cout << endl;
		cout << "    * find-all-st-path U V: finds all the shortest paths from node U to node V" << endl;
		cout << endl;
		cout << "    * find-one-s-path U: finds one shortest path between node U and all the other" << endl;
		cout << "        nodes in the graph." << endl;
		cout << endl;
		cout << "    * find-all-s-path U: finds all shortest paths between node U and all the other" << endl;
		cout << "        nodes in the graph." << endl;
		cout << endl;
		cout << "    * find-one-path: finds one shortest path between any pair of nodes in the graph" << endl;
		cout << endl;
		cout << "    * find-all-path: finds all shortest paths between any pair of nodes in the graph" << endl;
		cout << endl;
		cout << "-------------------------------------" << endl;
		cout << "MISCELLANEA" << endl;
		cout << endl;
		cout << "    * has-edge U V: outputs YES or NO depending on whether the graph" << endl;
		cout << "        has edge (U,V) or not" << endl;
		cout << endl;
		cout << "    * is-weighted: outputs YES if the graph is weighted. Outputs NO if otherwise" << endl;
		cout << endl;
		cout << "    * is-directed: outputs YES if the graph is directed. Outputs NO if otherwise" << endl;
		cout << endl;
		cout << "    * to-unweighted: converts the graph into an unweighted graph. Prints the result." << endl;
		cout << endl;
		cout << "    * clear: clear the graph." << endl;
		cout << endl;
		cout << "    * print: for each node, print its neighbourhood into standard output." << endl;
		cout << endl;
		cout << "    * store-file FORMAT FILE: store the graph into FILE using format FORMAT." << endl;
		cout << "        Allowed values for FORMAT:" << endl;
		cout << "        edge-list" << endl;
		cout << endl;
		cout << "    * read-file FORMAT FILE: read an unweighted graph format from FILE using format FORMAT." << endl;
		cout << "        Allowed values for FORMAT:" << endl;
		cout << "        edge-list" << endl;
		cout << endl;
		cout << "    * quit: exit the driver" << endl;
		cout << endl;
		cout << "+++++++++++++++++++++++++++++++++++++++" << endl;
	}

	void driver_weighted(bool directed) {
		wxgraph<float> *G = nullptr;

		if (directed) {
			// do nothing
			cout << "Execute driver for directed graphs" << endl;
			G = new wdgraph<float>();
		}
		else {
			cout << "Execute driver for undirected graphs" << endl;
			G = new wugraph<float>();
		}

		string option;
		cout << "> ";
		while (cin >> option and option != "quit") {
			timing::time_point begin = timing::now();

			if (option == "help") {
				print_weighted_options();
			}
			else if (option == "init") {
				size_t n;
				cin >> n;
				G->init(n);
			}
			else if (option == "add-node") {
				G->add_node();
			}
			else if (option == "add-nodes") {
				size_t n;
				cin >> n;
				G->add_n_nodes(n);
			}
			else if (option == "add-edge") {
				node u,v;
				cin >> u >> v;
				float w;
				cin >> w;

				G->add_edge(u, v, w);
			}
			else if (option == "add-edges") {
				size_t n;
				cin >> n;

				node u,v;
				float w;
				for (size_t i = 0; i < n; ++i) {
					cin >> u >> v;
					cin >> w;
					G->add_edge(u, v, w);
				}
			}
			else if (option == "has-edge") {
				node u,v;
				cin >> u >> v;
				cout << "Does graph has edge (" << u << "," << v << ")? "
					 << (G->has_edge(u,v) ? "Yes" : "No") << endl;
			}
			else if (option == "remove-edge") {
				node u,v;
				cin >> u >> v;

				G->remove_edge(u, v);
			}
			else if (option == "remove-edges") {
				size_t n;
				cin >> n;

				node u,v;
				for (size_t i = 0; i < n; ++i) {
					cin >> u >> v;
					G->remove_edge(u, v);
				}
			}
			else if (option == "remove-node") {
				node u;
				cin >> u;

				G->remove_node(u);
			}
			else if (option == "get-edge-weight") {
				node u, v;
				cin >> u >> v;
				cout << "Weight of edge (" << u << "," << v << "): "
					 << G->edge_weight(u,v) << endl;
			}
			else if (option == "get-edges") {
				vector<pair<edge, float> > all_edges;
				G->edges(all_edges);
				for (const auto& p : all_edges) {
					const edge& e = p.first;
					cout << "(" << e.first << "," << e.second
						 << " : " << p.second << ")" << endl;
				}
				cout << endl;
			}
			else if (option == "set-edge-weight") {
				node u, v;
				float w;
				cin >> u >> v >> w;
				G->set_edge_weight(u,v,w);
			}
			else if (option == "get-weights-node") {
				node u;
				cin >> u;
				const weight_list<float>& weights = G->get_weights(u);
				for (float w : weights) {
					cout << w << ", ";
				}
				cout << endl;
			}
			else if (option == "find-one-st-path") {
				node u,v;
				cin >> u >> v;
				node_path<float> p;
				wxpath(G, u, v, p);
				cout << p << endl;
			}
			else if (option == "find-all-st-path") {
				node u,v;
				cin >> u >> v;
				node_path_set<float> ps;
				wxpaths(G, u, v, ps);
				for (const node_path<float>& p : ps) {
					cout << "    " << p << endl;
				}
			}
			else if (option == "find-one-s-path") {
				node u;
				cin >> u;
				vector<node_path<float> > p;
				wxpath(G, u, p);
				for (node v = 0; v < G->n_nodes(); ++v) {
					cout << u << " -> " << v << ": " << p[v] << endl;
				}
			}
			else if (option == "find-all-s-path") {
				node u;
				cin >> u;
				vector<node_path_set<float> > ps;
				wxpaths(G, u, ps);
				for (node v = 0; v < G->n_nodes(); ++v) {
					cout << u << " -> " << v << ":" << endl;
					const node_path_set<float>& Puv = ps[v];
					for (const node_path<float>& p : Puv) {
						cout << "    " << p << endl;
					}
				}
			}
			else if (option == "find-one-path") {
				vector<vector<node_path<float> > > ps;
				wxpath(G, ps);
				for (node u = 0; u < G->n_nodes(); ++u) {
					for (node v = 0; v < G->n_nodes(); ++v) {
						cout << u << " -> " << v << ": " << ps[u][v] << endl;
					}
				}
			}
			else if (option == "find-all-path") {
				vector<vector<node_path_set<float> > > ps;
				wxpaths(G, ps);
				for (node u = 0; u < G->n_nodes(); ++u) {
					for (node v = 0; v < G->n_nodes(); ++v) {
						cout << u << " -> " << v << ":" << endl;
						const node_path_set<float>& Puv = ps[u][v];
						for (const node_path<float>& p : Puv) {
							cout << "    " << p << endl;
						}
					}
				}
			}
			else if (option == "is-weighted") {
				cout << "Is the graph weighted? "
					 << (G->is_weighted() ? "Yes" : "No") << endl;
			}
			else if (option == "is-directed") {
				cout << "Is the graph directed? "
					 << (G->is_directed() ? "Yes" : "No") << endl;
			}
			else if (option == "to-unweighted") {
				uxgraph *g = G->to_unweighted();
				cout << "Number of edges: " << g->n_edges() << endl;
				cout << *g << endl;
				delete g;
			}
			else if (option == "clear") {
				G->clear();
			}
			else if (option == "print") {
				cout << *G << endl;
			}
			else if (option == "store-file") {
				string format, filename;
				cin >> format >> filename;
				if (format == "edge-list") {
					edge_list::write(filename, G);
				}
			}
			else if (option == "read-file") {
				string format, filename;
				cin >> format >> filename;
				if (format == "edge-list") {
					edge_list::read(filename, G);
				}
			}
			else if (option == "---") {
				cout << "-----------------------------------" << endl;
			}
			else {
				cout << "    Unknown option '" << option << "'" << endl;
			}

			timing::time_point end = timing::now();
			cout << "    In " << timing::elapsed_seconds(begin, end) << " seconds" << endl;

			cout << "> ";
		}

		delete G;
	}
}
