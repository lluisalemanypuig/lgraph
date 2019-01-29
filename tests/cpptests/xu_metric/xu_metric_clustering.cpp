// C++ inlcudes
#include <iostream>
#include <vector>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>
#include <lgraph/metrics/clustering_xu.hpp>
#include <lgraph/io/io.hpp>
using namespace lgraph;

// custom includes
#include "definitions.hpp"
#include "io_wrapper.hpp"
#include "test_utils.hpp"
using namespace test_utils;

namespace exe_tests {

void xu_metric_clustering_gcc(const xxgraph *G) {
	double c = networks::metrics::clustering::gcc(G);
	cout << floatpointout_metric(c) << endl;
}

void xu_metric_clustering_mlcc(const xxgraph *G) {
	double c = networks::metrics::clustering::mlcc(G);
	cout << floatpointout_metric(c) << endl;
}

err_type xu_metric_clustering(const string& c, ifstream& fin)
{
	string input_graph, format;
	size_t n;

	// parse input field
	string field;
	fin >> field;
	if (field != "INPUT") {
		cerr << ERROR("xu_metric_clustering.cpp", "xu_metric_clustering") << endl;
		cerr << "    Expected field 'INPUT'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}
	fin >> n;
	if (n != 1) {
		cerr << ERROR("xu_metric_clustering.cpp", "xu_metric_clustering") << endl;
		cerr << "    Only one input file is allowed in this test." << endl;
		cerr << "    Instead, " << n << " were specified." << endl;
		return err_type::test_format_error;
	}
	fin >> input_graph >> format;

	// parse body field
	fin >> field;
	if (field != "BODY") {
		cerr << ERROR("xu_metric_clustering.cpp", "xu_metric_clustering") << endl;
		cerr << "    Expected field 'BODY'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}

	string graph_type;
	fin >> graph_type;

	xxgraph *G = nullptr;
	if (graph_type == "weighted") {
		G = new wugraph<float>();
	}
	else if (graph_type == "unweighted") {
		G = new uugraph();
	}
	else {
		cerr << ERROR("xu_metric_clustering.cpp", "xu_metric_clustering") << endl;
		cerr << "    Wrong value for parameter 'graph_type'." << endl;
		cerr << "    Received '" << graph_type << "'." << endl;
		return err_type::invalid_param;
	}

	err_type r;

	if (G->is_weighted()) {
		r = io_wrapper::read_graph(
			input_graph,
			format,
			static_cast<wxgraph<float> *>(G)
		);
	}
	else {
		r = io_wrapper::read_graph(
			input_graph,
			format,
			static_cast<uxgraph *>(G)
		);
	}

	if (r != err_type::no_error) {
		if (r == err_type::io_error) {
			cerr << ERROR("xu_metric_clustering.cpp", "xu_metric_clustering") << endl;
			cerr << "    Could not open file '" << input_graph << "'" << endl;
		}
		else if (r == err_type::graph_format_error) {
			cerr << ERROR("xu_metric_clustering.cpp", "xu_metric_clustering") << endl;
			cerr << "    Input file format '" << format << "' not supported." << endl;
		}
		return r;
	}

	if (c == "gcc") {
		xu_metric_clustering_gcc(G);
	}
	else if (c == "mlcc") {
		xu_metric_clustering_mlcc(G);
	}
	else {
		cerr << ERROR("xu_metric_clustering.cpp", "xu_metric_clustering") << endl;
		cerr << "    Wrong value for parameter 'c'." << endl;
		cerr << "    Received '" << c << "'." << endl;
		return err_type::invalid_param;
	}

	delete G;
	G = nullptr;

	return err_type::no_error;
}

} // -- namespace exe_tests
