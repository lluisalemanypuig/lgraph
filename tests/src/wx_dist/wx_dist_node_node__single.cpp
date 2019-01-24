// C++ inlcudes
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/wxgraph.hpp>
#include <lgraph/graph_traversal/traversal_wx.hpp>
#include <lgraph/io/io.hpp>
using namespace lgraph;

// custom includes
#include "src/definitions.hpp"
#include "src/io_wrapper.hpp"
#include "src/test_utils.hpp"
using namespace test_utils;

namespace exe_tests {

err_type wx_distance_node_node__single(const string& graph_type, ifstream& fin) {
	string input_graph, format;
	size_t n;

	// parse input field
	string field;
	fin >> field;
	if (field != "INPUT") {
		cerr << ERROR("wx_distance_node_node__single.cpp", "wx_distance_node_node__single") << endl;
		cerr << "    Expected field 'INPUT'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}
	fin >> n;
	if (n != 1) {
		cerr << ERROR("wx_distance_node_node__single.cpp", "wx_distance_node_node__single") << endl;
		cerr << "    Only one input file is allowed in this test." << endl;
		cerr << "    Instead, " << n << " were specified." << endl;
		return err_type::test_format_error;
	}
	fin >> input_graph >> format;

	// parse body field
	fin >> field;
	if (field != "BODY") {
		cerr << ERROR("wx_distance_node_node__single.cpp", "wx_distance_node_node__single") << endl;
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
		cerr << ERROR("wx_distance_node_node__single.cpp", "wx_distance_node_node__single") << endl;
		cerr << "    Wrong value for parameter 'garph_type'." << endl;
		cerr << "    Received '" << graph_type << "'." << endl;
		return err_type::invalid_param;
	}

	err_type r = io_wrapper::read_graph(input_graph, format, G);
	if (r != err_type::no_error) {
		if (r == err_type::io_error) {
			cerr << ERROR("wx_distance_node_node__single.cpp", "wx_distance_node_node__single") << endl;
			cerr << "    Could not open file '" << input_graph << "'" << endl;
		}
		else if (r == err_type::graph_format_error) {
			cerr << ERROR("wx_distance_node_node__single.cpp", "wx_distance_node_node__single") << endl;
			cerr << "    Input file format '" << format << "' not supported." << endl;
		}
		return r;
	}

	node u, v;
	// read pairs of nodes
	while (fin >> u >> v) {
		float dist = traversal::wxdistance(G, u, v);
		cout << distout(dist) << endl;
	}

	return err_type::no_error;
}

} // -- namespace exe_tests
