// C++ inlcudes
#include <iostream>
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
#include "src/io_wrapper.hpp"
#include "src/test_utils.hpp"

namespace exe_tests {

err_type uu_path_node_all__all(ifstream& fin) {
	string input_graph, format;
	size_t n;

	// parse input field
	string field;
	fin >> field;
	if (field != "INPUT") {
		cerr << ERROR("uu_path_node_all__all.cpp", "uu_path_node_all__all") << endl;
		cerr << "    Expected field 'INPUT'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}
	fin >> n;
	if (n != 1) {
		cerr << ERROR("uu_path_node_all__all.cpp", "uu_path_node_all__all") << endl;
		cerr << "    Only one input file is allowed in this test." << endl;
		cerr << "    Instead, " << n << " were specified." << endl;
		return err_type::test_format_error;
	}
	fin >> input_graph >> format;

	// parse body field
	fin >> field;
	if (field != "BODY") {
		cerr << ERROR("uu_path_node_all__all.cpp", "uu_path_node_all__all") << endl;
		cerr << "    Expected field 'BODY'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}

	uugraph G;
	err_type r = io_wrapper::read_graph(input_graph, format, &G);
	if (r != err_type::no_error) {
		if (r == err_type::io_error) {
			cerr << ERROR("uu_path_node_all__all.cpp", "uu_path_node_all__all") << endl;
			cerr << "    Could not open file '" << input_graph << "'" << endl;
		}
		else if (r == err_type::graph_format_error) {
			cerr << ERROR("uu_path_node_all__all.cpp", "uu_path_node_all__all") << endl;
			cerr << "    Format '" << format << "' not supported." << endl;
		}
		return r;
	}

	node u;
	// read list of nodes
	while (fin >> u) {
		vector<node_path_set<_new_> > pss;
		traversal::uxpaths(&G, u, pss);

		for (node v = 0; v < G.n_nodes(); ++v) {
			sort(pss[v].begin(), pss[v].end(), test_utils::comp_ux_paths);
		}

		for (node v = 0; v < G.n_nodes(); ++v) {
			const node_path_set<_new_>& ps = pss[v];
			cout << v << ": ";

			if (ps.size() > 0) {
				cout << ps[v].to_string() << "; " << ps[v].get_length() << endl;
			}
			else {
				cout << "No paths" << endl;
			}
		}
	}

	return err_type::no_error;
}

}

