#include "driver.hpp"

namespace graph_driver {

	void print_unweighted_options() {
		cout << "+++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "Options for the unweighted graph driver" << endl;
		cout << "---------------------------------------" << endl;
		cout << endl;
		cout << "    For the case of undirected graphs, an edge between two nodes U and V" << endl;
		cout << "    can be denoted indistinctintly as (U,V) or (V,U). For directed graphs," << endl;
		cout << "    however, this cannot be done and the order matters. Give edges accordingly." << endl;
		cout << endl;
		cout << "    * help: show the options of this driver" << endl;
		cout << endl;
		cout << "    * init N: initialise the graph with N nodes. It is needed" << endl;
		cout << "        before being able to safely add edges." << endl;
		cout << endl;
		cout << "    * add-edge U V: add an edge (U,V)." << endl;
		cout << endl;
		cout << "    * add-edges N u1 v1 u2 v2 ... uN vN: add N edges. Each edge" << endl;
		cout << "        is a pair of nodes (ui,vi)." << endl;
		cout << endl;
		cout << "    * remove-edge U V: remove the edge (U,V)." << endl;
		cout << endl;
		cout << "    * remove-edges N u1 v1 u2 v2 ... uN vN: remove N edges. Each edge" << endl;
		cout << "        is a pair of nodes (ui,vi)." << endl;
		cout << endl;
		cout << "    * get-edges: prints the list of edges." << endl;
		cout << endl;
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

	void driver_unweighted(bool directed) {
		uxgraph* G = nullptr;

		if (directed) {
			// do nothing
			cout << "Execute driver for directed graphs" << endl;
			return;
		}
		else {
			cout << "Execute driver for undirected graphs" << endl;
			G = new uugraph();
		}

		string option;
		while (cin >> option and option != "quit") {
			if (option == "help") {
				print_unweighted_options();
			}
			else if (option == "init") {
				size_t n;
				cin >> n;
				G->init(n);
			}
			else if (option == "add-edge") {
				node u,v;
				cin >> u >> v;

				G->add_edge(u, v);
			}
			else if (option == "add-edges") {
				size_t n;
				cin >> n;

				node u,v;
				for (size_t i = 0; i < n; ++i) {
					cin >> u >> v;
					G->add_edge(u, v);
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
			else if (option == "get-edges") {
				vector<edge> all_edges;
				G->edges(all_edges);
				for (const edge& e : all_edges) {
					cout << "(" << e.first << "," << e.second << ")" << endl;
				}
				cout << endl;
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
