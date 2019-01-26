// C++ inlcudes
#include <iostream>
#include <vector>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/wugraph.hpp>
#include <lgraph/data_structures/wdgraph.hpp>
#include <lgraph/metrics/distance_wx.hpp>
#include <lgraph/io/io.hpp>
using namespace lgraph;

// custom includes
#include "src/definitions.hpp"
#include "src/io_wrapper.hpp"
#include "src/test_utils.hpp"
using namespace test_utils;

namespace exe_tests {

void wx_metric_distance_max(const wxgraph<float> *G) {
	float d = networks::metrics::distance::max_distance(G);
	cout << d << endl;
}

void wx_metric_distance_mean(const wxgraph<float> *G) {
	double d = networks::metrics::distance::max_distance(G);
	cout << floatpointout(d) << endl;
}

void wx_metric_distance_mcc(const wxgraph<float> *G) {
	double d = networks::metrics::distance::mcc(G);
	cout << floatpointout(d) << endl;
}

err_type wx_metric_distance
(const string& graph_type, const string& c, ifstream& fin)
{
	string input_graph, format;
	size_t n;

	// parse input field
	string field;
	fin >> field;
	if (field != "INPUT") {
		cerr << ERROR("wx_metric_distance.cpp", "wx_metric_distance") << endl;
		cerr << "    Expected field 'INPUT'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}
	fin >> n;
	if (n != 1) {
		cerr << ERROR("wx_metric_distance.cpp", "wx_metric_distance") << endl;
		cerr << "    Only one input file is allowed in this test." << endl;
		cerr << "    Instead, " << n << " were specified." << endl;
		return err_type::test_format_error;
	}
	fin >> input_graph >> format;

	// parse body field
	fin >> field;
	if (field != "BODY") {
		cerr << ERROR("wx_metric_distance.cpp", "wx_metric_distance") << endl;
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
		cerr << ERROR("wx_metric_distance.cpp", "wx_metric_distance") << endl;
		cerr << "    Wrong value for parameter 'graph_type'." << endl;
		cerr << "    Received '" << graph_type << "'." << endl;
		return err_type::invalid_param;
	}

	err_type r = io_wrapper::read_graph(input_graph, format, G);
	if (r != err_type::no_error) {
		if (r == err_type::io_error) {
			cerr << ERROR("wx_metric_distance.cpp", "wx_metric_distance") << endl;
			cerr << "    Could not open file '" << input_graph << "'" << endl;
		}
		else if (r == err_type::graph_format_error) {
			cerr << ERROR("wx_metric_distance.cpp", "wx_metric_distance") << endl;
			cerr << "    Input file format '" << format << "' not supported." << endl;
		}
		return r;
	}

	if (c == "max") {
		wx_metric_distance_max(G);
	}
	else if (c == "mean") {
		wx_metric_distance_mean(G);
	}
	else if (c == "mcc") {
		wx_metric_distance_mcc(G);
	}
	else {
		cerr << ERROR("wx_metric_distance.cpp", "wx_metric_distance") << endl;
		cerr << "    Wrong value for parameter 'c'." << endl;
		cerr << "    Received '" << c << "'." << endl;
		return err_type::invalid_param;
	}

	delete G;
	G = nullptr;

	return err_type::no_error;
}

} // -- namespace exe_tests
