// C++ inlcudes
#include <iostream>
#include <vector>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>
#include <lgraph/metrics/centralities_xx.hpp>
#include <lgraph/io/io.hpp>
using namespace lgraph;

// custom includes
#include "definitions.hpp"
#include "io_wrapper.hpp"
#include "test_utils.hpp"
using namespace test_utils;

namespace exe_tests {

void xx_metric_centrality_degree__single(const xxgraph *G, ifstream& fin) {
	node u;
	while (fin >> u) {
		double c = networks::metrics::centralities::degree(G, u);
		cout << floatpointout_metric(c) << endl;
	}
}

void xx_metric_centrality_degree__all(const xxgraph *G) {
	vector<double> cc;

	networks::metrics::centralities::degree(G, cc);
	for (node u = 0; u < G->n_nodes(); ++u) {
		cout << u << ": " << floatpointout_metric(cc[u]) << endl;
	}
}

err_type xx_metric_centrality
(const string& c, const string& many, ifstream& fin)
{
	string input_graph, format;
	size_t n;

	// parse input field
	string field;
	fin >> field;
	if (field != "INPUT") {
		cerr << ERROR("xx_metric_centrality.cpp", "xx_metric_centrality") << endl;
		cerr << "    Expected field 'INPUT'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}
	fin >> n;
	if (n != 1) {
		cerr << ERROR("xx_metric_centrality.cpp", "xx_metric_centrality") << endl;
		cerr << "    Only one input file is allowed in this test." << endl;
		cerr << "    Instead, " << n << " were specified." << endl;
		return err_type::test_format_error;
	}
	fin >> input_graph >> format;

	// parse body field
	fin >> field;
	if (field != "BODY") {
		cerr << ERROR("xx_metric_centrality.cpp", "xx_metric_centrality") << endl;
		cerr << "    Expected field 'BODY'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}

	string weighted, directed;
	fin >> weighted >> directed;
	if (weighted != "unweighted" and weighted != "weighted") {
		cerr << ERROR("xx_metric_centrality.cpp", "xx_metric_centrality") << endl;
		cerr << "    Wrong value for type of graph." << endl;
		cerr << "    Expected unweighted / weighted." << endl;
		cerr << "    Instead, '" << weighted << "' was found." << endl;
		return err_type::test_format_error;
	}
	if (directed != "undirected" and directed != "directed") {
		cerr << ERROR("xx_metric_centrality.cpp", "xx_metric_centrality") << endl;
		cerr << "    Wrong value for type of graph." << endl;
		cerr << "    Expected undirected / directed." << endl;
		cerr << "    Instead, '" << directed << "' was found." << endl;
		return err_type::test_format_error;
	}

	err_type r;
	xxgraph *G = nullptr;

	if (weighted == "weighted" and directed == "directed") {
		G = new wdgraph<float>();
		r = io_wrapper::read_graph(
			input_graph,
			format,
			static_cast<wdgraph<float> *>(G)
		);
	}
	else if (weighted == "weighted" and directed == "undirected") {
		G = new wugraph<float>();
		r = io_wrapper::read_graph(
			input_graph,
			format,
			static_cast<wdgraph<float> *>(G)
		);
	}
	else if (weighted == "unweighted" and directed == "directed") {
		G = new udgraph();
		r = io_wrapper::read_graph(
			input_graph,
			format,
			static_cast<udgraph *>(G)
		);
	}
	else if (weighted == "unweighted" and directed == "undirected") {
		G = new uugraph();
		r = io_wrapper::read_graph(
			input_graph,
			format,
			static_cast<uugraph *>(G)
		);
	}

	if (r != err_type::no_error) {
		if (r == err_type::io_error) {
			cerr << ERROR("xx_metric_centrality.cpp", "xx_metric_centrality") << endl;
			cerr << "    Could not open file '" << input_graph << "'" << endl;
		}
		else if (r == err_type::graph_format_error) {
			cerr << ERROR("xx_metric_centrality.cpp", "xx_metric_centrality") << endl;
			cerr << "    Input file format '" << format << "' not supported." << endl;
		}
		return r;
	}

	bool wrong_c = false;
	bool wrong_many = false;

	if (c == "degree") {
		if (many == "single") {
			xx_metric_centrality_degree__single(G, fin);
		}
		else if (many == "all") {
			xx_metric_centrality_degree__all(G);
		}
		else {
			wrong_many = true;
		}
	}

	if (wrong_c) {
		cerr << ERROR("xx_metric_centrality.cpp", "xx_metric_centrality") << endl;
		cerr << "    Wrong value for parameter 'c'." << endl;
		cerr << "    Received '" << c << "'." << endl;
		return err_type::invalid_param;
	}

	if (wrong_many) {
		cerr << ERROR("xx_metric_centrality.cpp", "xx_metric_centrality") << endl;
		cerr << "    Wrong value for parameter 'many'." << endl;
		cerr << "    Received '" << many << "'." << endl;
		return err_type::invalid_param;
	}

	delete G;
	G = nullptr;

	return err_type::no_error;
}

} // -- namespace exe_tests
