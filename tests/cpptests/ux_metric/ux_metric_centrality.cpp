// C++ inlcudes
#include <iostream>
#include <vector>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>
#include <lgraph/metrics/centralities_ux.hpp>
#include <lgraph/io/io.hpp>
using namespace lgraph;

// custom includes
#include "definitions.hpp"
#include "io_wrapper.hpp"
#include "test_utils.hpp"
using namespace test_utils;

namespace exe_tests {

void ux_metric_centrality_degree__single(const uxgraph *G, ifstream& fin) {
	node u;
	while (fin >> u) {
		double d = networks::metrics::centralities::degree(G, u);
		cout << floatpointout_metric(d) << endl;
	}
}

void ux_metric_centrality_degree__all(const uxgraph *G) {
	vector<double> dc;

	networks::metrics::centralities::degree(G, dc);
	for (node u = 0; u < G->n_nodes(); ++u) {
		cout << u << ": " << floatpointout_metric(dc[u]) << endl;
	}
}

void ux_metric_centrality_closeness__single(const uxgraph *G, ifstream& fin) {
	node u;
	while (fin >> u) {
		double c = networks::metrics::centralities::closeness(G, u);
		cout << floatpointout_metric(c) << endl;
	}
}

void ux_metric_centrality_closeness__all(const uxgraph *G) {
	vector<double> cc;

	networks::metrics::centralities::closeness(G, cc);
	for (node u = 0; u < G->n_nodes(); ++u) {
		cout << u << ": " << floatpointout_metric(cc[u]) << endl;
	}
}

void ux_metric_centrality_betweenness__single(const uxgraph *G, ifstream& fin) {
	node u;
	while (fin >> u) {
		double b = networks::metrics::centralities::betweenness(G, u);
		cout << floatpointout_metric(b) << endl;
	}
}

void ux_metric_centrality_betweenness__all(const uxgraph *G) {
	vector<double> bc;

	networks::metrics::centralities::betweenness(G, bc);
	for (node u = 0; u < G->n_nodes(); ++u) {
		cout << u << ": " << floatpointout_metric(bc[u]) << endl;
	}
}

void ux_metric_centrality_mcc(const uxgraph* G) {
	double d = networks::metrics::centralities::mcc(G);
	cout << floatpointout_metric(d) << endl;
}

err_type ux_metric_centrality
(const string& graph_type, const string& c, const string& many, ifstream& fin)
{
	string input_graph, format;
	size_t n;

	// parse input field
	string field;
	fin >> field;
	if (field != "INPUT") {
		cerr << ERROR("ux_metric_centrality.cpp", "ux_metric_centrality") << endl;
		cerr << "    Expected field 'INPUT'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}
	fin >> n;
	if (n != 1) {
		cerr << ERROR("ux_metric_centrality.cpp", "ux_metric_centrality") << endl;
		cerr << "    Only one input file is allowed in this test." << endl;
		cerr << "    Instead, " << n << " were specified." << endl;
		return err_type::test_format_error;
	}
	fin >> input_graph >> format;

	// parse body field
	fin >> field;
	if (field != "BODY") {
		cerr << ERROR("ux_metric_centrality.cpp", "ux_metric_centrality") << endl;
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
		cerr << ERROR("ux_metric_centrality.cpp", "ux_metric_centrality") << endl;
		cerr << "    Wrong value for parameter 'graph_type'." << endl;
		cerr << "    Received '" << graph_type << "'." << endl;
		return err_type::invalid_param;
	}

	err_type r = io_wrapper::read_graph(input_graph, format, G);
	if (r != err_type::no_error) {
		if (r == err_type::io_error) {
			cerr << ERROR("ux_metric_centrality.cpp", "ux_metric_centrality") << endl;
			cerr << "    Could not open file '" << input_graph << "'" << endl;
		}
		else if (r == err_type::graph_format_error) {
			cerr << ERROR("ux_metric_centrality.cpp", "ux_metric_centrality") << endl;
			cerr << "    Input file format '" << format << "' not supported." << endl;
		}
		return r;
	}

	if (c == "degree" or c == "closeness" or c == "betweenness") {
		if (many != "single" and many != "all") {
			cerr << ERROR("ux_metric_centrality.cpp", "ux_metric_centrality") << endl;
			cerr << "    Wrong value for parameter 'many'." << endl;
			cerr << "    Received '" << many << "'." << endl;
			return err_type::invalid_param;
		}
	}

	if (c == "degree") {
		if (many == "single") {
			ux_metric_centrality_degree__single(G, fin);
		}
		else if (many == "all") {
			ux_metric_centrality_degree__all(G);
		}
	}
	else if (c == "closeness") {
		if (many == "single") {
			ux_metric_centrality_closeness__single(G, fin);
		}
		else if (many == "all") {
			ux_metric_centrality_closeness__all(G);
		}
	}
	else if (c == "betweenness") {
		if (many == "single") {
			ux_metric_centrality_betweenness__single(G, fin);
		}
		else if (many == "all") {
			ux_metric_centrality_betweenness__all(G);
		}
	}
	else if (c == "mcc") {
		ux_metric_centrality_mcc(G);
	}
	else {
		cerr << ERROR("ux_metric_centrality.cpp", "ux_metric_centrality") << endl;
		cerr << "    Wrong value for parameter 'c'." << endl;
		cerr << "    Received '" << c << "'." << endl;
		return err_type::invalid_param;
	}

	delete G;
	G = nullptr;

	return err_type::no_error;
}

} // -- namespace exe_tests
