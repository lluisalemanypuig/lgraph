// C++ inlcudes
#include <iostream>
#include <vector>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/wugraph.hpp>
#include <lgraph/data_structures/wdgraph.hpp>
#include <lgraph/metrics/centralities_wx.hpp>
#include <lgraph/io/io.hpp>
using namespace lgraph;

// custom includes
#include "src/definitions.hpp"
#include "src/io_wrapper.hpp"
#include "src/test_utils.hpp"
using namespace test_utils;

namespace exe_tests {

void wx_metric_centrality_degree__single(const wxgraph<float> *G, ifstream& fin) {
	node u;
	fin >> u;

	double d = networks::metrics::centralities::degree(G, u);
	cout << floatpointout(d) << endl;
}

void wx_metric_centrality_degree__all(const wxgraph<float> *G) {
	vector<double> dc;

	networks::metrics::centralities::degree(G, dc);
	for (node u = 0; u < G->n_nodes(); ++u) {
		cout << u << ": " << floatpointout(dc[u]) << endl;
	}
}

void wx_metric_centrality_closeness__single(const wxgraph<float> *G, ifstream& fin) {
	node u;
	fin >> u;

	double c = networks::metrics::centralities::closeness(G, u);
	cout << floatpointout(c) << endl;
}

void wx_metric_centrality_closeness__all(const wxgraph<float> *G) {
	vector<double> cc;

	networks::metrics::centralities::closeness(G, cc);
	for (node u = 0; u < G->n_nodes(); ++u) {
		cout << u << ": " << floatpointout(cc[u]) << endl;
	}
}

void wx_metric_centrality_betweenness__single(const wxgraph<float> *G, ifstream& fin) {
	node u;
	fin >> u;

	double b = networks::metrics::centralities::betweenness(G, u);
	cout << floatpointout(b) << endl;
}

void wx_metric_centrality_betweenness__all(const wxgraph<float> *G) {
	vector<double> bc;

	networks::metrics::centralities::betweenness(G, bc);
	for (node u = 0; u < G->n_nodes(); ++u) {
		cout << u << ": " << floatpointout(bc[u]) << endl;
	}
}

void wx_metric_centrality_mcc(const wxgraph<float> *G) {
	double d = networks::metrics::centralities::mcc(G);
	cout << floatpointout(d) << endl;
}

err_type wx_metric_centrality
(const string& graph_type, const string& c, const string& many, ifstream& fin)
{
	string input_graph, format;
	size_t n;

	// parse input field
	string field;
	fin >> field;
	if (field != "INPUT") {
		cerr << ERROR("wx_metric_centrality.cpp", "wx_metric_centrality") << endl;
		cerr << "    Expected field 'INPUT'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}
	fin >> n;
	if (n != 1) {
		cerr << ERROR("wx_metric_centrality.cpp", "wx_metric_centrality") << endl;
		cerr << "    Only one input file is allowed in this test." << endl;
		cerr << "    Instead, " << n << " were specified." << endl;
		return err_type::test_format_error;
	}
	fin >> input_graph >> format;

	// parse body field
	fin >> field;
	if (field != "BODY") {
		cerr << ERROR("wx_metric_centrality.cpp", "wx_metric_centrality") << endl;
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
		cerr << ERROR("wx_metric_centrality.cpp", "wx_metric_centrality") << endl;
		cerr << "    Wrong value for parameter 'graph_type'." << endl;
		cerr << "    Received '" << graph_type << "'." << endl;
		return err_type::invalid_param;
	}

	err_type r = io_wrapper::read_graph(input_graph, format, G);
	if (r != err_type::no_error) {
		if (r == err_type::io_error) {
			cerr << ERROR("wx_metric_centrality.cpp", "wx_metric_centrality") << endl;
			cerr << "    Could not open file '" << input_graph << "'" << endl;
		}
		else if (r == err_type::graph_format_error) {
			cerr << ERROR("wx_metric_centrality.cpp", "wx_metric_centrality") << endl;
			cerr << "    Input file format '" << format << "' not supported." << endl;
		}
		return r;
	}

	if (c == "degree") {
		if (many == "single") {
			wx_metric_centrality_degree__single(G, fin);
		}
		else if (many == "all") {
			wx_metric_centrality_degree__all(G);
		}
	}
	else if (c == "closeness") {
		if (many == "single") {
			wx_metric_centrality_closeness__single(G, fin);
		}
		else if (many == "all") {
			wx_metric_centrality_closeness__all(G);
		}
	}
	else if (c == "betweenness") {
		if (many == "single") {
			wx_metric_centrality_betweenness__single(G, fin);
		}
		else if (many == "all") {
			wx_metric_centrality_betweenness__all(G);
		}
	}
	else if (c == "mcc") {
		wx_metric_centrality_mcc(G);
	}
	else {
		cerr << ERROR("wx_metric_centrality.cpp", "wx_metric_centrality") << endl;
		cerr << "    Wrong value for parameter 'c'." << endl;
		cerr << "    Received '" << c << "'." << endl;
		return err_type::invalid_param;
	}

	delete G;
	G = nullptr;

	return err_type::no_error;
}

} // -- namespace exe_tests
