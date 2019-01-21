// C includes

// C++ inlcudes
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/node_path.hpp>
#include <lgraph/graph_traversal/traversal.hpp>
#include <lgraph/io/io.hpp>
using namespace lgraph;

// custom includes
#include "src/definitions.hpp"
#include "src/test_utils.hpp"
#include "src/io_wrapper.hpp"

namespace exe_tests {

err_type ux_path_node_node__all(const string& graph_type, ifstream& fin) {
	string input_graph, format;
	size_t n;

	// parse input field
	string field;
	fin >> field;
	if (field != "INPUT") {
		cerr << ERROR("ux_path_node_node__all.cpp", "ux_path_node_node__all") << endl;
		cerr << "    Expected field 'INPUT'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}
	fin >> n;
	if (n != 1) {
		cerr << ERROR("ux_path_node_node__all.cpp", "ux_path_node_node__all") << endl;
		cerr << "    Only one input file is allowed in this test." << endl;
		cerr << "    Instead, " << n << " were specified." << endl;
		return err_type::test_format_error;
	}
	fin >> input_graph >> format;

	// parse body field
	fin >> field;
	if (field != "BODY") {
		cerr << ERROR("ux_path_node_node__all.cpp", "ux_path_node_node__all") << endl;
		cerr << "    Expected field 'BODY'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}

	uxgraph *G = nullptr;
	if (graph_type == "directed") {
		G = new udgraph();
	}
	else if (graph_type == "undirected") {
		G = new uugraph();
	}
	else {
		cerr << ERROR("ux_path_node_node__all.cpp", "ux_path_node_node__all") << endl;
		cerr << "    Wrong value for parameter 'garph_type'." << endl;
		cerr << "    Received '" << graph_type << "'." << endl;
		return err_type::invalid_param;
	}

	err_type r = io_wrapper::read_graph(input_graph, format, G);
	if (r != err_type::no_error) {
		if (r == err_type::io_error) {
			cerr << ERROR("ux_path_node_node__all.cpp", "ux_path_node_node__all") << endl;
			cerr << "    Could not open file '" << input_graph << "'" << endl;
		}
		else if (r == err_type::graph_format_error) {
			cerr << ERROR("ux_path_node_node__all.cpp", "ux_path_node_node__all") << endl;
			cerr << "    Input file format '" << format << "' not supported." << endl;
		}
		return r;
	}

	node u, v;
	// read pairs of nodes
	while (fin >> u >> v) {

		node_path_set<_new_> ps;
		traversal::uxpaths(G, u, v, ps);
		sort(ps.begin(), ps.end(), test_utils::comp_ux_paths);

		if (ps.size() > 0) {
			for (const node_path<_new_>& p : ps) {
				cout << p.to_string() << "; " << p.get_length() << endl;
			}
		}
		else {
			cout << "No paths" << endl;
		}
	}

	return err_type::no_error;
}

}

