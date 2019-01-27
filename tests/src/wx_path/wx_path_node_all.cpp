// C++ inlcudes
#include <iostream>
#include <vector>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/wugraph.hpp>
#include <lgraph/data_structures/wdgraph.hpp>
#include <lgraph/data_structures/node_path.hpp>
#include <lgraph/graph_traversal/traversal_wx.hpp>
#include <lgraph/io/io.hpp>
using namespace lgraph;

// custom includes
#include "src/definitions.hpp"
#include "src/io_wrapper.hpp"
#include "src/test_utils.hpp"
using namespace test_utils;

namespace exe_tests {

void wx_path_node_all__single(const wxgraph<float> *G, ifstream& fin) {
	node u;
	// read list of nodes
	while (fin >> u) {
		vector<node_path<float> > ps;
		traversal::wxpath(G, u, ps);

		if (ps.size() > 0) {
			for (node v = 0; v < G->n_nodes(); ++v) {
				if (ps[v].size() == 0) {
					cout << v << ": No path" << endl;
				}
				else {
					cout << v << ": " << ps[v].to_string() << "; "
						 << floatpointout_dist(ps[v].get_length()) << endl;
				}
			}
		}
		else {
			cout << "No paths" << endl;
		}
	}
}

void wx_path_node_all__all(const wxgraph<float> *G, ifstream& fin) {
	node u;
	// read list of nodes
	while (fin >> u) {
		vector<node_path_set<float> > pss;
		traversal::wxpaths(G, u, pss);

		for (node v = 0; v < G->n_nodes(); ++v) {
			sort(pss[v].begin(), pss[v].end(), test_utils::comp_wx_paths);

			const node_path_set<float>& ps = pss[v];
			if (ps.size() > 0) {
				for (const node_path<float>& p : ps) {
					cout << v << ": "
						 << p.to_string() << "; "
						 << floatpointout_dist(p.get_length()) << endl;
				}
			}
			else {
				cout << v << ": No paths" << endl;
			}
		}
	}
}

err_type wx_path_node_all
(const string& graph_type, const string& many, ifstream& fin)
{
	string input_graph, format;
	size_t n;

	// parse input field
	string field;
	fin >> field;
	if (field != "INPUT") {
		cerr << ERROR("wx_path_node_all.cpp", "wx_path_node_all") << endl;
		cerr << "    Expected field 'INPUT'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}
	fin >> n;
	if (n != 1) {
		cerr << ERROR("wx_path_node_all.cpp", "wx_path_node_all") << endl;
		cerr << "    Only one input file is allowed in this test." << endl;
		cerr << "    Instead, " << n << " were specified." << endl;
		return err_type::test_format_error;
	}
	fin >> input_graph >> format;

	// parse body field
	fin >> field;
	if (field != "BODY") {
		cerr << ERROR("wx_path_node_all.cpp", "wx_path_node_all") << endl;
		cerr << "    Expected field 'BODY'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}

	wxgraph<float> *G = nullptr;
	if (graph_type == "directed") {
		G = new wdgraph<float>();
	}
	else if (graph_type == "undirected") {
		G = new wugraph<float>();
	}
	else {
		cerr << ERROR("wx_path_node_all.cpp", "wx_path_node_all") << endl;
		cerr << "    Wrong value for parameter 'graph_type'." << endl;
		cerr << "    Received '" << graph_type << "'." << endl;
		return err_type::invalid_param;
	}

	err_type r = io_wrapper::read_graph(input_graph, format, G);
	if (r != err_type::no_error) {
		if (r == err_type::io_error) {
			cerr << ERROR("wx_path_node_all.cpp", "wx_path_node_all") << endl;
			cerr << "    Could not open file '" << input_graph << "'" << endl;
		}
		else if (r == err_type::graph_format_error) {
			cerr << ERROR("wx_path_node_all.cpp", "wx_path_node_all") << endl;
			cerr << "    Input file format '" << format << "' not supported." << endl;
		}
		return r;
	}

	if (many == "single") {
		wx_path_node_all__single(G, fin);
	}
	else if (many == "all") {
		wx_path_node_all__all(G, fin);
	}
	else {
		cerr << ERROR("wx_path_node_all.cpp", "wx_path_node_all") << endl;
		cerr << "    Value of parameter 'many' is not valid." << endl;
		cerr << "    Received: '" << many << "'." << endl;
		return err_type::invalid_param;
	}

	delete G;
	G = nullptr;

	return err_type::no_error;
}

} // -- namespace exe_tests
