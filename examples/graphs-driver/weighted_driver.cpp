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
		cout << "---------------------------------------" << endl;
		cout << "MAKING A GRAPH" << endl;
		cout << "    * init N: initialise the graph with N nodes. It is needed" << endl;
		cout << "        before being able to safely add edges." << endl;
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
		cout << "    * get-edge-weight U V: outputs the weight of the edge (U,V)" << endl;
		cout << endl;
		cout << "    * get-edges: prints the list of edges." << endl;
		cout << endl;
		cout << "---------------------------------------" << endl;
		cout << "PATHS IN A GRAPH" << endl;
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
		cout << "---------------------------------------" << endl;
		cout << "MISCELLANEA" << endl;
		cout << "    * clear: clear the graph." << endl;
		cout << endl;
		cout << "    * print: for each node, print its neighbourhood into standard output." << endl;
		cout << endl;
		cout << "    * store-file FILE: store the graph into FILE in edge list format." << endl;
		cout << endl;
		cout << "    * read-file FILE: read an unweighted graph in edge list format from FILE." << endl;
		cout << endl;
		cout << "    * quit: exit the driver" << endl;
		cout << endl;
		cout << "+++++++++++++++++++++++++++++++++++++++" << endl;
	}

	void driver_weighted(bool directed) {
		wxgraph<float>* G = nullptr;

		if (directed) {
			// do nothing
			cout << "Execute driver for directed graphs" << endl;
			return;
		}
		else {
			cout << "Execute driver for undirected graphs" << endl;
			G = new wugraph<float>();
		}

		string option;
		while (cin >> option and option != "quit") {
			if (option == "help") {
				print_weighted_options();
			}
			else if (option == "init") {
				size_t n;
				cin >> n;
				G->init(n);
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
			else if (option == "get-weights-node") {
				vector<float> weights;
				node u;
				cin >> u;
				G->get_weights(u, weights);
				for (float& w : weights) {
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
			else if (option == "clear") {
				G->clear();
			}
			else if (option == "print") {
				cout << *G << endl;
			}
			else if (option == "store-file") {
				string filename;
				cin >> filename;
				G->store_in_file(filename);
			}
			else if (option == "read-file") {
				string filename;
				cin >> filename;
				G->read_from_file(filename);
			}
			else if (option == "---") {
				cout << "-----------------------------------" << endl;
			}
		}

		delete G;
	}
}
