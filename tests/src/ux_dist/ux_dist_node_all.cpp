// C++ inlcudes
#include <iostream>
#include <vector>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>
#include <lgraph/graph_traversal/traversal_ux.hpp>
#include <lgraph/io/io.hpp>
using namespace lgraph;

// custom includes
#include "src/definitions.hpp"
#include "src/io_wrapper.hpp"
#include "src/test_utils.hpp"
using namespace test_utils;

namespace exe_tests {

void ux_distance_node_all__single(const uxgraph *G, ifstream& fin) {
	node u;
	// read list of nodes
	while (fin >> u) {
		vector<_new_> dists;
		traversal::uxdistance(G, u, dists);

		for (node v = 0; v < G->n_nodes(); ++v) {
			cout << v << ": " << floatpointout_dist(dists[v]) << endl;
		}
	}
}

void ux_distance_node_all__all(const uxgraph *G, ifstream& fin) {
	node u;
	// read list of nodes
	while (fin >> u) {
		vector<_new_> dists;
		vector<size_t> n_paths;
		traversal::uxdistance(G, u, dists, n_paths);

		for (node v = 0; v < G->n_nodes(); ++v) {
			cout << v << ": " << floatpointout_dist(dists[v])
				 << " (" << n_paths[v] << ")" << endl;
		}
	}
}

err_type ux_distance_node_all
(const string& graph_type, const string& many, ifstream& fin)
{
	string input_graph, format;
	size_t n;

	// parse input field
	string field;
	fin >> field;
	if (field != "INPUT") {
		cerr << ERROR("ux_distance_node_all.cpp", "ux_distance_node_all") << endl;
		cerr << "    Expected field 'INPUT'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}
	fin >> n;
	if (n != 1) {
		cerr << ERROR("ux_distance_node_all.cpp", "ux_distance_node_all") << endl;
		cerr << "    Only one input file is allowed in this test." << endl;
		cerr << "    Instead, " << n << " were specified." << endl;
		return err_type::test_format_error;
	}
	fin >> input_graph >> format;

	// parse body field
	fin >> field;
	if (field != "BODY") {
		cerr << ERROR("ux_distance_node_all.cpp", "ux_distance_node_all") << endl;
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
		cerr << ERROR("ux_distance_node_all.cpp", "ux_distance_node_all") << endl;
		cerr << "    Wrong value for parameter 'graph_type'." << endl;
		cerr << "    Received '" << graph_type << "'." << endl;
		return err_type::invalid_param;
	}

	err_type r = io_wrapper::read_graph(input_graph, format, G);
	if (r != err_type::no_error) {
		if (r == err_type::io_error) {
			cerr << ERROR("ux_distance_node_all.cpp", "ux_distance_node_all") << endl;
			cerr << "    Could not open file '" << input_graph << "'" << endl;
		}
		else if (r == err_type::graph_format_error) {
			cerr << ERROR("ux_distance_node_all.cpp", "ux_distance_node_all") << endl;
			cerr << "    Input file format '" << format << "' not supported." << endl;
		}
		return r;
	}

	if (many == "single") {
		ux_distance_node_all__single(G, fin);
	}
	else if (many == "all") {
		ux_distance_node_all__all(G, fin);
	}
	else {
		cerr << ERROR("ux_distance_node_all.cpp", "ux_distance_node_all") << endl;
		cerr << "    Value of parameter 'many' is not valid." << endl;
		cerr << "    Received: '" << many << "'." << endl;
		return err_type::invalid_param;
	}

	delete G;
	G = nullptr;

	return err_type::no_error;
}

} // -- namespace exe_tests
