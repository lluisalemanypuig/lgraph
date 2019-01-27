// C++ inlcudes
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/wugraph.hpp>
#include <lgraph/data_structures/wdgraph.hpp>
#include <lgraph/graph_traversal/traversal_wx.hpp>
#include <lgraph/io/io.hpp>
using namespace lgraph;

// custom includes
#include "src/definitions.hpp"
#include "src/io_wrapper.hpp"
#include "src/test_utils.hpp"
using namespace test_utils;

namespace exe_tests {

void wx_distance_node_node__single(const wxgraph<float> *G, ifstream& fin) {
	node u, v;
	// read pairs of nodes
	while (fin >> u >> v) {
		float dist = traversal::wxdistance(G, u, v);
		cout << floatpointout_dist(dist) << endl;
	}
}

void wx_distance_node_node__all(const wxgraph<float> *G, ifstream& fin) {
	node u, v;
	// read pairs of nodes
	while (fin >> u >> v) {
		size_t n_paths;
		float dist = traversal::wxdistance(G, u, v, n_paths);
		cout << floatpointout_dist(dist) << " (" << n_paths << ")" << endl;
	}
}

err_type wx_distance_node_node
(const string& graph_type, const string& many, ifstream& fin)
{
	string input_graph, format;
	size_t n;

	// parse input field
	string field;
	fin >> field;
	if (field != "INPUT") {
		cerr << ERROR("wx_distance_node_node.cpp", "wx_distance_node_node") << endl;
		cerr << "    Expected field 'INPUT'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}
	fin >> n;
	if (n != 1) {
		cerr << ERROR("wx_distance_node_node.cpp", "wx_distance_node_node") << endl;
		cerr << "    Only one input file is allowed in this test." << endl;
		cerr << "    Instead, " << n << " were specified." << endl;
		return err_type::test_format_error;
	}
	fin >> input_graph >> format;

	// parse body field
	fin >> field;
	if (field != "BODY") {
		cerr << ERROR("wx_distance_node_node.cpp", "wx_distance_node_node") << endl;
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
		cerr << ERROR("wx_distance_node_node.cpp", "wx_distance_node_node") << endl;
		cerr << "    Wrong value for parameter 'graph_type'." << endl;
		cerr << "    Received '" << graph_type << "'." << endl;
		return err_type::invalid_param;
	}

	err_type r = io_wrapper::read_graph(input_graph, format, G);
	if (r != err_type::no_error) {
		if (r == err_type::io_error) {
			cerr << ERROR("wx_distance_node_node.cpp", "wx_distance_node_node") << endl;
			cerr << "    Could not open file '" << input_graph << "'" << endl;
		}
		else if (r == err_type::graph_format_error) {
			cerr << ERROR("wx_distance_node_node.cpp", "wx_distance_node_node") << endl;
			cerr << "    Input file format '" << format << "' not supported." << endl;
		}
		return r;
	}

	if (many == "single") {
		wx_distance_node_node__single(G, fin);
	}
	else if (many == "all") {
		wx_distance_node_node__all(G, fin);
	}
	else {
		cerr << ERROR("wx_distance_node_node.cpp", "wx_distance_node_node") << endl;
		cerr << "    Value of parameter 'many' is not valid." << endl;
		cerr << "    Received: '" << many << "'." << endl;
		return err_type::invalid_param;
	}

	delete G;
	G = nullptr;

	return err_type::no_error;
}

} // -- namespace exe_tests
